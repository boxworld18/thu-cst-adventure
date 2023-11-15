#include <chrono>
#include <iostream>
#include <mpi.h>
#include <time.h>
#include <cstring>
#include <cmath>
#include <algorithm>

#define EPS 1e-8

namespace ch = std::chrono;

void Ring_Allreduce(void* sendbuf, void* recvbuf, int n, MPI_Comm comm, int comm_sz, int my_rank)
{
    int len = n / comm_sz;
    int len_lst = n - len * (comm_sz - 1);

    // Phase 1: Reduce-scatter
    for (int rnd = 0; rnd < comm_sz - 1; rnd++) {
        MPI_Request req[2];
        int bias_sd = len * ((my_rank - rnd + comm_sz) % comm_sz);
        int bias_rv = len * ((my_rank - 1 - rnd + comm_sz) % comm_sz);
        int len_rv = (bias_rv == len * (comm_sz - 1)) ? len_lst: len;
        int len_sd = (bias_sd == len * (comm_sz - 1)) ? len_lst: len;

        MPI_Irecv((float *)recvbuf + bias_rv, len_rv, MPI_FLOAT,
                    (my_rank - 1 + comm_sz) % comm_sz, rnd, comm, &req[0]);

        MPI_Isend((float *)sendbuf + bias_sd, len_sd, MPI_FLOAT,
                    (my_rank + 1) % comm_sz, rnd, comm, &req[1]);

        MPI_Waitall(2, req, nullptr);

        for (int i = 0; i < len_rv; i++)
            ((float *)sendbuf)[bias_rv + i] += ((float *)recvbuf)[bias_rv + i];
        memcpy((float *)recvbuf + bias_rv, (float *)sendbuf + bias_rv, len_rv * sizeof(float));
    }

    // Phase 2: Allgather
    for (int rnd = 0; rnd < comm_sz - 1; rnd++) {
        MPI_Request req[2];
        int bias_sd = len * ((my_rank + 1 - rnd + comm_sz) % comm_sz);
        int bias_rv = len * ((my_rank - rnd + comm_sz) % comm_sz);
        int len_rv = (bias_rv == len * (comm_sz - 1)) ? len_lst: len;
        int len_sd = (bias_sd == len * (comm_sz - 1)) ? len_lst: len;

        MPI_Irecv((float *)recvbuf + bias_rv, len_rv, MPI_FLOAT,
                    (my_rank - 1 + comm_sz) % comm_sz, rnd, comm, &req[0]);

        MPI_Isend((float *)recvbuf + bias_sd, len_sd, MPI_FLOAT,
                    (my_rank + 1) % comm_sz, rnd, comm, &req[1]);

        MPI_Waitall(2, req, nullptr);
    }

    if (comm_sz == 1) 
        memcpy(recvbuf, sendbuf, n * sizeof(float));
}


// reduce + bcast
void Naive_Allreduce(void* sendbuf, void* recvbuf, int n, MPI_Comm comm, int comm_sz, int my_rank)
{
    MPI_Reduce(sendbuf, recvbuf, n, MPI_FLOAT, MPI_SUM, 0, comm);
    MPI_Bcast(recvbuf, n, MPI_FLOAT, 0, comm);
}

int main(int argc, char *argv[])
{
    int ITER = atoi(argv[1]);
    int n = atoi(argv[2]);
    float* mpi_sendbuf = new float[n];
    float* mpi_recvbuf = new float[n];
    float* naive_sendbuf = new float[n];
    float* naive_recvbuf = new float[n];
    float* ring_sendbuf = new float[n];
    float* ring_recvbuf = new float[n];

    MPI_Init(nullptr, nullptr);
    int comm_sz;
    int my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    srand(time(NULL) + my_rank);
    for (int i = 0; i < n; ++i)
        mpi_sendbuf[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    memcpy(naive_sendbuf, mpi_sendbuf, n * sizeof(float));
    memcpy(ring_sendbuf, mpi_sendbuf, n * sizeof(float));

    //warmup and check
    MPI_Allreduce(mpi_sendbuf, mpi_recvbuf, n, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
    Naive_Allreduce(naive_sendbuf, naive_recvbuf, n, MPI_COMM_WORLD, comm_sz, my_rank);
    Ring_Allreduce(ring_sendbuf, ring_recvbuf, n, MPI_COMM_WORLD, comm_sz, my_rank);
    bool correct = true;
    for (int i = 0; i < n; ++i)
        if (abs(mpi_recvbuf[i] - ring_recvbuf[i]) > EPS)
        {
            correct = false;
            break;
        }

    if (correct)
    {
        auto beg = ch::high_resolution_clock::now();
        for (int iter = 0; iter < ITER; ++iter)
            MPI_Allreduce(mpi_sendbuf, mpi_recvbuf, n, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
        auto end = ch::high_resolution_clock::now();
        double mpi_dur = ch::duration_cast<ch::duration<double>>(end - beg).count() * 1000; //ms

        beg = ch::high_resolution_clock::now();
        for (int iter = 0; iter < ITER; ++iter)
            Naive_Allreduce(naive_sendbuf, naive_recvbuf, n, MPI_COMM_WORLD, comm_sz, my_rank);
        end = ch::high_resolution_clock::now();
        double naive_dur = ch::duration_cast<ch::duration<double>>(end - beg).count() * 1000; //ms

        beg = ch::high_resolution_clock::now();
        for (int iter = 0; iter < ITER; ++iter)
            Ring_Allreduce(ring_sendbuf, ring_recvbuf, n, MPI_COMM_WORLD, comm_sz, my_rank);
        end = ch::high_resolution_clock::now();
        double ring_dur = ch::duration_cast<ch::duration<double>>(end - beg).count() * 1000; //ms
        
        if (my_rank == 0)
        {
            std::cout << "Correct." << std::endl;
            std::cout << "MPI_Allreduce:   " << mpi_dur << " ms." << std::endl;
            std::cout << "Naive_Allreduce: " << naive_dur << " ms." << std::endl;
            std::cout << "Ring_Allreduce:  " << ring_dur << " ms." << std::endl;
        }
    }
    else
        if (my_rank == 0)
            std::cout << "Wrong!" << std::endl;

    delete[] mpi_sendbuf;
    delete[] mpi_recvbuf;
    delete[] naive_sendbuf;
    delete[] naive_recvbuf;
    delete[] ring_sendbuf;
    delete[] ring_recvbuf;
    MPI_Finalize();
    return 0;
}
