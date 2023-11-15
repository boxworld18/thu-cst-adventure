#include "aplusb.h"
void a_plus_b_auto_simd(float* a, float* b, float* c, int n) {
    #pragma omp simd
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}