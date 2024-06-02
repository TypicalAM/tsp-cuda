#include "bruteforce_cuda.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cuda_runtime.h>
#include <limits>
#include <linux/limits.h>

__device__ void swap(uint8_t *a, uint8_t *b) {
  uint8_t temp = *a;
  *a = *b;
  *b = temp;
}

__device__ bool next_permutation(uint8_t *first, uint8_t *last) {
  if (first == last)
    return false;
  uint8_t *i = last - 1;
  while (i > first && *(i - 1) >= *i)
    --i;
  if (i == first)
    return false;
  uint8_t *j = last - 1;
  while (*j <= *(i - 1))
    --j;
  swap(i - 1, j);
  uint8_t *k = last - 1;
  while (i < k)
    swap(i++, k--);
  return true;
}

__global__ void solve_kernel(uint16_t *distances, uint8_t *permutations,
                             uint16_t *results, std::size_t vertex_count,
                             uint16_t entry) {
  int tid = threadIdx.x + blockIdx.x * blockDim.x;
  if (tid >= (vertex_count - 1) * (vertex_count - 1))
    return;

  uint8_t second_vertex = tid % (vertex_count - 1);
  uint8_t third_vertex = (tid - second_vertex) / (vertex_count - 1);
  if (second_vertex == third_vertex) {
    results[tid] = std::numeric_limits<uint16_t>::max();
    return;
  }

  uint8_t *vertices = permutations + tid * sizeof(uint8_t) * vertex_count;
  vertices[0] = 0;
  vertices[1] = second_vertex + 1;
  vertices[2] = third_vertex + 1;

  int vertex_idx = 3;
  for (auto i = 1; i < vertex_count; i++)
    if (i != second_vertex + 1 && i != third_vertex + 1) {
      vertices[vertex_idx] = i;
      vertex_idx++;
    }

  uint16_t result = entry;
  do {
    uint16_t instance = 0;
    int i = 0;
    for (; i < vertex_count && instance < result; i++)
      instance += distances[vertices[i] * vertex_count + vertices[i + 1]];
    if (i == vertex_count && instance < result)
      result = instance;
  } while (next_permutation(vertices + 3, vertices + vertex_count));

  results[tid] = result;
}

uint16_t BruteforceCUDA::solve(Graph *graph,
                               std::optional<uint16_t> entry_value) {
  uint16_t entry = (entry_value.has_value())
                       ? entry_value.value()
                       : std::numeric_limits<uint16_t>::max();

  auto *host_distances = new uint16_t[graph->size() * graph->size()];
  for (auto from = 0; from < graph->size(); from++)
    for (auto to = 0; to < graph->size(); to++)
      host_distances[from * graph->size() + to] = graph->distance(from, to);

  uint16_t *device_distances;
  cudaMalloc(&device_distances,
             sizeof(uint16_t) * graph->size() * graph->size());
  cudaMemcpy(device_distances, host_distances,
             sizeof(uint16_t) * graph->size() * graph->size(),
             cudaMemcpyHostToDevice);

  const std::size_t MAX_THREADS = (graph->size() - 1) * (graph->size() - 1);
  uint8_t *device_permutations;
  cudaMalloc(&device_permutations,
             sizeof(uint8_t) * graph->size() * MAX_THREADS);

  uint16_t *device_results;
  cudaMalloc(&device_results, sizeof(uint16_t) * MAX_THREADS);

  auto block_count = (MAX_THREADS + BLOCK_SIZE - 1) / BLOCK_SIZE;
  solve_kernel<<<block_count, BLOCK_SIZE>>>(device_distances,
                                            device_permutations, device_results,
                                            graph->size(), entry);
  cudaError_t err = cudaDeviceSynchronize();

  // Check for any errors during kernel execution
  if (err != cudaSuccess) {
    printf("CUDA error: %s\n", cudaGetErrorString(err));
    exit(1);
  }

  auto *host_results = new uint16_t[MAX_THREADS];
  cudaMemcpy(host_results, device_results, sizeof(uint16_t) * MAX_THREADS,
             cudaMemcpyDeviceToHost);

  uint16_t result = *std::min_element(host_results, host_results + MAX_THREADS);
  delete[] host_distances;
  delete[] host_results;
  cudaFree(device_distances);
  cudaFree(device_permutations);
  cudaFree(device_results);
  return result;
}
