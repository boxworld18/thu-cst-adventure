#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <x86intrin.h>

#ifndef UNROLL_N
#define UNROLL_N 1
#endif

void fill(double* p, int n) {
    for (int i = 0; i < n; ++i)
        p[i] = 2 * drand48() - 1;
}

double wall_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return 1. * t.tv_sec + 1.e-6 * t.tv_usec;
}

void matmul_4x8(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int M, int N, int K) {
    __m256d c0 = _mm256_loadu_pd(C);
    __m256d c1 = _mm256_loadu_pd(C + 4);
    __m256d c2 = _mm256_loadu_pd(C + 8);
    __m256d c3 = _mm256_loadu_pd(C + 12);
    __m256d c4 = _mm256_loadu_pd(C + 16);
    __m256d c5 = _mm256_loadu_pd(C + 20);
    __m256d c6 = _mm256_loadu_pd(C + 24);
    __m256d c7 = _mm256_loadu_pd(C + 28);

    #pragma unroll(UNROLL_N)
    for (int k = 0; k < K; ++k) {
        __m256d b0 = _mm256_loadu_pd(B + 8 * k);
        __m256d b1 = _mm256_loadu_pd(B + 4 + 8 * k);
        __m256d a0 = _mm256_set1_pd(A[k]);
        c0 += a0 * b0;
        c1 += a0 * b1;
        __m256d a1 = _mm256_set1_pd(A[K + k]);
        c2 += a1 * b0;
        c3 += a1 * b1;
        __m256d a2 = _mm256_set1_pd(A[2 * K + k]);
        c4 += a2 * b0;
        c5 += a2 * b1;
        __m256d a3 = _mm256_set1_pd(A[3 * K + k]);
        c6 += a3 * b0;
        c7 += a3 * b1;
    }

    _mm256_storeu_pd(C, c0);
    _mm256_storeu_pd(C + 4, c1);
    _mm256_storeu_pd(C + 8, c2);
    _mm256_storeu_pd(C + 12, c3);
    _mm256_storeu_pd(C + 16, c4);
    _mm256_storeu_pd(C + 20, c5);
    _mm256_storeu_pd(C + 24, c6);
    _mm256_storeu_pd(C + 28, c7);
}

int main() {
    int M = 4, K = 512, N = 8;

    double *A = (double*)malloc(M * K * sizeof(double));
    double *B = (double*)malloc(K * N * sizeof(double));
    double *C = (double*)malloc(M * N * sizeof(double));


    fill(A, M * K);
    fill(B, K * N);
    fill(C, M * N);

    // warm up
    for (int i = 0; i < 10; ++i) {
        matmul_4x8(A, B, C, M, N, K);
    }

    double start = wall_time();
    int iter = 1000000;
    for (int i = 0; i < iter; ++i) {
        matmul_4x8(A, B, C, M, N, K);
    }
    double end = wall_time();
    double avg_time = (end - start);
    printf("Elapsed time: %.4f seconds, performance: %.4f GFlops\n", avg_time, 2.0 * iter * K * M * N / avg_time / 1e9);

    return 0;
}    
