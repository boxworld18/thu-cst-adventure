#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <cmath>

#include <omp.h>

const int n = 50000000;
int input[n], output[n];

const int nUniformParts = 100000, nRandomParts = 100;
int uniformParts[nUniformParts + 1], randomParts[nRandomParts + 1];

void prepareInput() {
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        // Used as a parallel random number generatator
        input[i] = ((size_t)i * 373587883 + 472882027) % 2147483647;
    }
}

void clearOutput() {
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        output[i] = 0;
    }
}

void prepareUniformParts(int nParts, int *parts) {
    parts[0] = 0;
    for (int i = 1; i < nParts; i++) {
        parts[i] = (int64_t)n * i / nParts;
    }
    parts[nParts] = n;
}

void prepareRandomParts(int nParts, int *parts) {
    // Generate parts in normal distribution
    std::mt19937 gen{0};
    std::normal_distribution<> d{n / 2, n / 8};

    parts[0] = 0;
    for (int i = 1; i < nParts; i++) {
        parts[i] = std::min(n, std::max(0, (int)round(d(gen))));
    }
    parts[nParts] = n;
    std::sort(parts, parts + nParts + 1);
}

// Split the input array as MANY, UNIFORM-LENGTHED parts, and sort each part in
// a out-of-place manner. The i-th part is in range of [parts[i], parts[i + 1])
void sortEveryUniformParts(int nParts, int *parts) {
    // TODO 1: Parallelize this loop in a proper manner
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < nParts; i++) {
        std::copy(input + parts[i], input + parts[i + 1], output + parts[i]);
        std::sort(output + parts[i], output + parts[i + 1]);
    }
}

// Split the input array as FEW, RANDOM-LENGTHED parts, and sort each part in
// a out-of-place manner. The i-th part is in range of [parts[i], parts[i + 1])
void sortEveryRandomParts(int nParts, int *parts) {
    // TODO 2: Parallelize this loop in a proper manner
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < nParts; i++) {
        std::copy(input + parts[i], input + parts[i + 1], output + parts[i]);
        std::sort(output + parts[i], output + parts[i + 1]);
    }
}

void checkOutput(int nParts, int *parts) {
    for (int i = 0; i < nParts; i++) {
        for (int j = parts[i]; j < parts[i + 1] - 1; j++) {
            assert(output[j] <= output[j + 1]);
        }
    }
}

void test_1() {
    namespace ch = std::chrono;
    prepareUniformParts(nUniformParts, uniformParts);
    // Measure time: drop the first result and average the other 10 measurements
    double t = 0;
    for (int i = 0; i < 11; i++) {
        clearOutput();
        auto beg = ch::high_resolution_clock::now();
        sortEveryUniformParts(nUniformParts, uniformParts);
        auto end = ch::high_resolution_clock::now();
        double dur =
            ch::duration_cast<ch::duration<double>>(end - beg).count() *
            1000;  // ms
        checkOutput(nUniformParts, uniformParts);
        if (i > 0) {
            t += dur;
        }
    }
    t /= 10;
    std::cout << "Sort uniform parts: " << t << " ms" << std::endl;
}

void test_2() {
    namespace ch = std::chrono;
    prepareRandomParts(nRandomParts, randomParts);
    // Measure time: drop the first result and average the other 10 measurements
    double t = 0;
    for (int i = 0; i < 11; i++) {
        clearOutput();
        auto beg = ch::high_resolution_clock::now();
        sortEveryRandomParts(nRandomParts, randomParts);
        auto end = ch::high_resolution_clock::now();
        double dur =
            ch::duration_cast<ch::duration<double>>(end - beg).count() *
            1000;  // ms
        checkOutput(nRandomParts, randomParts);
        if (i > 0) {
            t += dur;
        }
    }
    t /= 10;
    std::cout << "Sort random parts: " << t << " ms" << std::endl;
}

int main() {
    prepareInput();

    // Check in two separated functions to avoid reordering by the compiler
    test_1();
    test_2();

    return 0;
}

