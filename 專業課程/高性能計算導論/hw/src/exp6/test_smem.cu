#include "cuda_utils.h"
#include <cstdio>
#include <cuda.h>
#include <iostream>

// You should modify these parameters.
#define BITWIDTH 4
#define STRIDE 1

constexpr int times = 4096;

__global__ void test_shmem() {
#if (BITWIDTH == 2)
    volatile __shared__ uint16_t shm[32 * 128];
    volatile uint16_t tmp;
#elif (BITWIDTH == 4)
    volatile __shared__ uint32_t shm[32 * 128];
    volatile uint32_t tmp;
#elif (BITWIDTH == 8)
    volatile __shared__ uint64_t shm[32 * 128];
    volatile uint64_t tmp;
#endif

    for (int i = 0; i < times; i++) {
        tmp = shm[threadIdx.x * STRIDE];
    }
}

int main() {
    int size = (1 << 16);
    dim3 gridSize(size / 128, 1);
    dim3 blockSize(128, 1);

    cudaEvent_t st, ed;
    cudaEventCreate(&st);
    cudaEventCreate(&ed);
    float duration;

    // Warm up.
    for (int t = 0; t < 1024; t++) {
        test_shmem<<<gridSize, blockSize>>>();
        cudaCheckError();
    }

    cudaEventRecord(st, 0);
    for (int t = 0; t < 1024; t++) {
        test_shmem<<<gridSize, blockSize>>>();
        cudaCheckError();
    }
    cudaEventRecord(ed, 0);
    cudaEventSynchronize(st);
    cudaEventSynchronize(ed);
    cudaEventElapsedTime(&duration, st, ed);
    duration /= float(1024) * float(times);
    
    std::cout << "bitwidth:  " << BITWIDTH << std::endl;
    std::cout << "stride:    " << STRIDE << std::endl;
    std::cout << "bandwidth: " << size * BITWIDTH / duration / 1e6 << std::endl;
}

