#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void fill(double* p, int n) {
	for (int i = 0; i < n; ++i)
		p[i] = 2 * drand48() - 1;
}

double wall_time() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return 1. * t.tv_sec + 1.e-6 * t.tv_usec;
}

void matmul(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int M, int N, int K, double alpha, double beta) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
			double tmp = C[i * N + j] * beta;
            for (int k = 0; k < K; ++k) {
                tmp += alpha * A[i * K + k] * B[k * N + j];
            }
			C[i * N + j] = tmp;
        }
    }
}

int main() {
	int M = 512, N = 512, K = 512;

	double *A = (double*)malloc(M * K * sizeof(double));
	double *B = (double*)malloc(K * N * sizeof(double));
	double *C = (double*)malloc(M * N * sizeof(double));
	
	fill(A, M * K);
	fill(B, K * N);
	fill(C, M * N);

	// warm up
	matmul(A, B, C, M, N, K, 1.0, 1.0);

	double start = wall_time();
	int iter = 5;
	for (int i = 0; i < iter; ++i) {
		matmul(A, B, C, M, N, K, 1.0, 1.0);
	}
	double end = wall_time();
	double avg_time = (end - start) / iter;
	printf("Elapsed time: %.4f seconds, performance: %.4f GFlops\n", avg_time, 2.0 * M * N * K / avg_time / 1e9);

	return 0;
}
