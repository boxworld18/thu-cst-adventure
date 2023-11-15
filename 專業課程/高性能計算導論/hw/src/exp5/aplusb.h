#pragma once

void a_plus_b_baseline(float* a, float* b, float* c, int n);
void a_plus_b_intrinsic(float* a, float* b, float* c, int n);
void a_plus_b_auto_simd(float* a, float* b, float* c, int n);
