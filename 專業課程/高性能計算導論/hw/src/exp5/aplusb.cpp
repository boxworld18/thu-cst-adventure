#include "aplusb.h"

#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <functional>

template <typename F>
void run(F &&func, float* a, float* b, float* c, int n, const char* name) {
    //warmup
    func(a, b, c, n);

    // measure time
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= 10; i++) {
        func(a, b, c, n);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    printf("%s: %d us\n", name, int(duration.count()) / 10);
    fflush(stdout);
}

int main() {
    int n = 1 << 20;
    float *a = (float*) aligned_alloc(32, sizeof(float) * n);
    float *b = (float*) aligned_alloc(32, sizeof(float) * n);
    float *c1 = (float*) aligned_alloc(32, sizeof(float) * n);
    float *c2 = (float*) aligned_alloc(32, sizeof(float) * n);
    float *c3 = (float*) aligned_alloc(32, sizeof(float) * n);
    for (int i = 0; i < n; i++) a[i] = rand() * 1.0 / RAND_MAX;
    for (int i = 0; i < n; i++) b[i] = rand() * 1.0 / RAND_MAX;

    // time measure
    run(a_plus_b_baseline, a, b, c1, n, "baseline");
    run(a_plus_b_auto_simd, a, b, c2, n, "auto simd");

    // check result
    a_plus_b_baseline(a, b, c1, n);
    a_plus_b_intrinsic(a, b, c3, n);
    for (int i = 0; i < n; i++) {
        float eps = c3[i] - c1[i];
        if (eps > 1e-10 || eps < -1e-10) {
            printf("Wrong answer at %d: c1 = %f, c3 = %f\n", i, c1[i], c3[i]);
            exit(1);
        }
    }

    // time measure
    run(a_plus_b_intrinsic, a, b, c3, n, "intrinsic");

    delete[] a;
    delete[] b;
    delete[] c1;
    delete[] c2;
    delete[] c3;
    return 0;
}
