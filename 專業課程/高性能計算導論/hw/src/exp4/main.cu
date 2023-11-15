#include <chrono>
#include <iostream>
#include <cmath>
#include <sstream>
#include <cassert>

const int H = 10000, W = 10000;
const int kernel_size = 3;
const int n = (W + kernel_size - 1) * (H + kernel_size - 1);
float *input, *output;
float *dev_input, *dev_output;
float *answer = nullptr;
float *produce = nullptr;

#define checkCudaErrors(status)                   \
    do                                            \
    {                                             \
        if (status != 0)                          \
        {                                         \
            fprintf(stderr, "CUDA failure at [%s] (%s:%d): %s\n", __PRETTY_FUNCTION__, __FILE__, __LINE__, cudaGetErrorString(status)); \
            cudaDeviceReset();                    \
            abort();                              \
        }                                         \
    } while (0)

void prepareInput()
{
    input = new float[n];
    output = new float[n];
    for (int i = 0; i < n; i++)
    {
        // input[i] = 1.f;
        input[i] = (((size_t)i * 373587883 + 472882027) % 2147483647) / 2147483647.f;
    }

    checkCudaErrors(cudaMalloc(&dev_input, n * sizeof(float)));
    checkCudaErrors(cudaMalloc(&dev_output, H * W * sizeof(float)));
    checkCudaErrors(cudaMemcpy(dev_input, input, n * sizeof(float), cudaMemcpyHostToDevice));
}

__device__ inline float calc(float input)
{
    // return input;
    return sqrtf(expf(input / 4.0 + 0.24));
}

__global__ void naive(float *dev_input, float *dev_output, int H, int W, int kernel_size)
{
    int thread_id_x = blockDim.x * blockIdx.x + threadIdx.x;
    int thread_id_y = blockDim.y * blockIdx.y + threadIdx.y;
    if (thread_id_x >= W || thread_id_y >= H)
        return;
    float ans = 0.f;
    int init_pos = thread_id_y * (W + kernel_size - 1) + thread_id_x;
    ans += calc(dev_input[init_pos]);
    ans += calc(dev_input[init_pos + 1]);
    ans += calc(dev_input[init_pos + 2]);
    ans += calc(dev_input[init_pos + W + kernel_size - 1]);
    ans += calc(dev_input[init_pos + W + kernel_size]);
    ans += calc(dev_input[init_pos + W + kernel_size + 1]);
    ans += calc(dev_input[init_pos + 2 * (W + kernel_size - 1)]);
    ans += calc(dev_input[init_pos + 2 * (W + kernel_size - 1) + 1]);
    ans += calc(dev_input[init_pos + 2 * (W + kernel_size - 1) + 2]);
    dev_output[thread_id_y * W + thread_id_x] = ans;
}

__global__ void shared_mem(float *dev_input, float *dev_output, int H, int W, int kernel_size)
{
    int thread_id_x = blockDim.x * blockIdx.x + threadIdx.x;
    int thread_id_y = blockDim.y * blockIdx.y + threadIdx.y;
    if (thread_id_x >= W || thread_id_y >= H)
        return;
    extern __shared__ float cache[];
    int init_pos = thread_id_y * (W + kernel_size - 1) + thread_id_x;
    cache[threadIdx.y * (blockDim.x + kernel_size - 1) + threadIdx.x] = calc(dev_input[init_pos]);
    bool x_last = threadIdx.x == blockDim.x - 1 || thread_id_x == W - 1;
    bool y_last = threadIdx.y == blockDim.y - 1 || thread_id_y == H - 1;
    if (x_last)
    {
        cache[threadIdx.y * (blockDim.x + kernel_size - 1) + threadIdx.x + 1] = calc(dev_input[init_pos + 1]);
        cache[threadIdx.y * (blockDim.x + kernel_size - 1) + threadIdx.x + 2] = calc(dev_input[init_pos + 2]);
    }
    if (y_last)
    {
        cache[(threadIdx.y + 1) * (blockDim.x + kernel_size - 1) + threadIdx.x] = calc(dev_input[init_pos + (W + kernel_size - 1)]);
        cache[(threadIdx.y + 2) * (blockDim.x + kernel_size - 1) + threadIdx.x] = calc(dev_input[init_pos + 2 * (W + kernel_size - 1)]);
    }
    if (x_last && y_last)
    {
        cache[(threadIdx.y + 1) * (blockDim.x + kernel_size - 1) + threadIdx.x + 1] = calc(dev_input[init_pos + W + kernel_size - 1 + 1]);
        cache[(threadIdx.y + 1) * (blockDim.x + kernel_size - 1) + threadIdx.x + 2] = calc(dev_input[init_pos + W + kernel_size - 1 + 2]);
        cache[(threadIdx.y + 2) * (blockDim.x + kernel_size - 1) + threadIdx.x + 1] = calc(dev_input[init_pos + 2 * (W + kernel_size - 1) + 1]);
        cache[(threadIdx.y + 2) * (blockDim.x + kernel_size - 1) + threadIdx.x + 2] = calc(dev_input[init_pos + 2 * (W + kernel_size - 1) + 2]);
    }
    __syncthreads();
    float ans = 0.f;
    ans += cache[threadIdx.y * (blockDim.x + kernel_size - 1) + threadIdx.x];
    ans += cache[threadIdx.y * (blockDim.x + kernel_size - 1) + threadIdx.x + 1];
    ans += cache[threadIdx.y * (blockDim.x + kernel_size - 1) + threadIdx.x + 2];
    ans += cache[(threadIdx.y + 1) * (blockDim.x + kernel_size - 1) + threadIdx.x];
    ans += cache[(threadIdx.y + 1) * (blockDim.x + kernel_size - 1) + threadIdx.x + 1];
    ans += cache[(threadIdx.y + 1) * (blockDim.x + kernel_size - 1) + threadIdx.x + 2];
    ans += cache[(threadIdx.y + 2) * (blockDim.x + kernel_size - 1) + threadIdx.x];
    ans += cache[(threadIdx.y + 2) * (blockDim.x + kernel_size - 1) + threadIdx.x + 1];
    ans += cache[(threadIdx.y + 2) * (blockDim.x + kernel_size - 1) + threadIdx.x + 2];
    dev_output[thread_id_y * W + thread_id_x] = ans;
}

void validate(float *a1, float *a2)
{
    for (int i = 0; i < H * W; ++i)
    {
        if (abs(a1[i] - a2[i]) > 1e-5)
        {
            std::cout << "error answer: " << i << ' ' << a1[i] << ' ' << a2[i] << std::endl;
            exit(1);
        }
    }
}

void test_func(int block_size_x, int block_size_y, bool use_shared_memory = 0, bool validation = 0)
{
    std::string mode = "naive";
    if (use_shared_memory)
        mode = "shared_memory";
    namespace ch = std::chrono;
    double t = 0;
    int test = 20;
    int warmup = 10;
    dim3 grid, block;
    block.x = block_size_x;
    block.y = block_size_y;
    grid.x = (W + block.x - 1) / block.x;
    grid.y = (H + block.y - 1) / block.y;

    if (validation)
    {
        if (answer == nullptr)
        {
            answer = new float[H * W];
            produce = new float[H * W];
            naive<<<grid, block>>>(dev_input, dev_output, H, W, kernel_size);
            checkCudaErrors(cudaMemcpy(answer, dev_output, H * W * sizeof(float), cudaMemcpyDefault));
        }
        if (use_shared_memory)
        {
            shared_mem<<<grid, block, (block_size_x + kernel_size - 1) * (block_size_y + kernel_size - 1) * sizeof(float)>>>(dev_input, dev_output, H, W, kernel_size);
        }
        else
        {
            naive<<<grid, block>>>(dev_input, dev_output, H, W, kernel_size);
        }
        checkCudaErrors(cudaMemcpy(produce, dev_output, H * W * sizeof(float), cudaMemcpyDefault));
        validate(produce, answer);
    }

    for (int i = 0; i < warmup + test; i++)
    {
        checkCudaErrors(cudaDeviceSynchronize());
        auto beg = ch::high_resolution_clock::now();
        if (use_shared_memory)
        {
            shared_mem<<<grid, block, (block_size_x + kernel_size - 1) * (block_size_y + kernel_size - 1) * sizeof(float)>>>(dev_input, dev_output, H, W, kernel_size);
        }
        else
        {
            naive<<<grid, block>>>(dev_input, dev_output, H, W, kernel_size);
        }
        checkCudaErrors(cudaDeviceSynchronize());
        auto end = ch::high_resolution_clock::now();
        double dur = ch::duration_cast<ch::duration<double>>(end - beg).count() * 1000; // ms
        if (i >= warmup)
            t += dur;
    }
    t /= test;
    std::cout << mode << ' ' << block_size_x << ' ' << block_size_y << ' ' << "Exec-time: " << t << " ms" << std::endl;
}

int main()
{
    prepareInput();
    for (int i = 32; i <= 1024; i += 32) // blockDim.x
        for (int j = 1; j <= 32; ++j)    // blockDim.y
        {
            if (i * j > 1024)
                break;
            test_func(i, j, false, 0); // default: no validation
            test_func(i, j, true, 0);
        }
    return 0;
}
