#include "bruteforce_cuda.hpp"
#include <cstdio>
#include <cuda_runtime.h>

__global__ void lib_kernel() { printf("WHY IS THIS NOT WORKING"); }

uint16_t BruteforceCUDA::solve(Graph *graph,
                               std::optional<uint16_t> entry_value) {
  lib_kernel<<<1, 1>>>();
  return 0;
}
