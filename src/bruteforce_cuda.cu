#include "bruteforce_cuda.hpp"
#include <cstdio>
#include <cuda_runtime.h>

__global__ void lib_kernel() { printf("WHY IS THIS NOT WORKING"); }

uint64_t BruteforceCUDA::solve(Graph *graph,
                               std::optional<uint64_t> entry_value) {
  lib_kernel<<<1, 1>>>();
  return 0;
}
