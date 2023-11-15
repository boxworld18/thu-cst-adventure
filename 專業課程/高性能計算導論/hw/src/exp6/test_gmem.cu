#include <cstdio>
#include <cuda.h>
#include <iostream>

// You should modify this parameter.
#define STRIDE 1

__global__ void stride_copy(float *dst, float *src) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    dst[i * STRIDE] = src[i * STRIDE];
}

int main() {
    float *dev_a = 0, *dev_b = 0;
    int size = (1 << 24);
    cudaMalloc((void **)&dev_a, size  * 32 * sizeof(float));
    cudaMalloc((void **)&dev_b, size  * 32 * sizeof(float));
    dim3 gridSize(size / 1024, 1);
    dim3 blockSize(1024, 1);

    cudaEvent_t st, ed;
    cudaEventCreate(&st);
    cudaEventCreate(&ed);
    float duration;

    // The parameters that you should change.
    for (int t = 0; t < 1024; t++) {
        stride_copy<<<gridSize, blockSize>>>(dev_b, dev_a);
    }
    cudaEventRecord(st, 0);
    for (int t = 0; t < 1024; t++) {
        stride_copy<<<gridSize, blockSize>>>(dev_b, dev_a);
    }
    cudaEventRecord(ed, 0);
    cudaEventSynchronize(st);
    cudaEventSynchronize(ed);
    cudaEventElapsedTime(&duration, st, ed);
    duration /= 1024;
    std::cout << "stride:    " << STRIDE << std::endl;
    std::cout << "bandwidth: " << 8 * size / duration / 1e6 << std::endl;
}

