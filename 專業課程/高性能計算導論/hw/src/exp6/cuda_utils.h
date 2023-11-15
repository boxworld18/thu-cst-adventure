#pragma once
#include <iostream>

#define cudaSafeCall(err) __cudaSafeCall(err, __FILE__, __LINE__)
#define cudaCheckError() __cudaCheckError(__FILE__, __LINE__)

inline void __cudaSafeCall(cudaError err, const char *file, const int line) {
    if (cudaSuccess != err) {
        std::cout << "[ERROR] " << file << "::" << line
                  << ": cudaSafeCall() failed. " << cudaGetErrorString(err)
                  << std::endl;
        exit(-1);
    }
    return;
}

inline void __cudaCheckError(const char *file, const int line) {
    cudaError err = cudaGetLastError();
    if (cudaSuccess != err) {
        std::cout << "[ERROR] " << file << "::" << line
                  << ": cudaCheckError() failed. " << cudaGetErrorString(err)
                  << std::endl;
        exit(-1);
    }
    return;
}

