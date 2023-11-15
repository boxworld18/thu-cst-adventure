#include <chrono>
#include <iostream>
#include <mpi.h>

namespace ch = std::chrono;     

// 模拟耗时为 T ms 的计算任务
void compute(double T)
{
        auto beg = ch::high_resolution_clock::now();
        double dur = 0;

        while ( dur < T )
        {
                auto end = ch::high_resolution_clock::now();
                dur = ch::duration_cast<ch::duration<double>>(end - beg).count() * 1000;
        }
}

int main(int argc, char *argv[])
{
        int ITER = atoi(argv[1]); // 测试轮数
        int n = atoi(argv[2]); // 通信消息大小
        double T = atoi(argv[3]); // 计算量 (ms)
        double* buf = new double[n]; // 通信数据

        // MPI 初始化
        MPI_Init(nullptr, nullptr);

        int comm_sz;
        int my_rank;
        MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        MPI_Request req[ITER];

        // warmup. 第一次通信性能不稳定，排除在测试之外
        if ( my_rank == 0)
        {
                MPI_Send(buf, n, MPI_DOUBLE, 1, ITER, MPI_COMM_WORLD);
        }
        else {
                MPI_Recv(buf, n, MPI_DOUBLE, 0, ITER, MPI_COMM_WORLD, nullptr);
        }

        // 开始测试
        auto beg = ch::high_resolution_clock::now();
        double dur;

        if ( my_rank == 0 )
        {
                // 每轮迭代中，0 号进程向 1 号进程发送大小为 n 的消息，并完成 T ms 的计算
                for(int i = 0; i < ITER; ++i) {
                        auto iter_beg = ch::high_resolution_clock::now();

                        MPI_Isend(buf, n, MPI_DOUBLE, 1, i, MPI_COMM_WORLD, &req[i]);    

                        auto send_end = ch::high_resolution_clock::now();
                        dur = ch::duration_cast<ch::duration<double>>(send_end - iter_beg).count() * 1000; //ms
                        std::cout << "Iter " << i << " MPI_Isend: " << dur << " ms" << std::endl;

                        compute(T);

                        auto iter_end = ch::high_resolution_clock::now();
                        dur = ch::duration_cast<ch::duration<double>>(iter_end - send_end).count() * 1000; //ms
                        std::cout << "Iter " << i << " Compute: " << dur << " ms" << std::endl;
                }

                auto wait_beg = ch::high_resolution_clock::now();
                for(int i = 0; i < ITER; ++i)
                {
                        MPI_Wait(&req[i], nullptr);
                }
                auto wait_end = ch::high_resolution_clock::now();
                dur = ch::duration_cast<ch::duration<double>>(wait_end - wait_beg).count() * 1000; //ms
                std::cout << "Wait Request: " << dur << " ms" << std::endl;
        }
        else
        {
                // 1 号进程仅需要接收消息
                for(int i = 0; i < ITER; ++i)
                {
                        MPI_Recv(buf, n, MPI_DOUBLE, 0, i, MPI_COMM_WORLD, nullptr);
                }
        }

        auto end = ch::high_resolution_clock::now();
        dur = ch::duration_cast<ch::duration<double>>(end - beg).count() * 1000;  // ms

        // 结束测试，输出总时间
        if ( my_rank == 0 ) 
        {
                std::cout << "Total: " << dur << " ms" << std::endl;
        }

        delete[] buf;

        MPI_Finalize();
}
