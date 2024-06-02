#include "bruteforce_omp.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <limits>

uint16_t BruteforceOMP::solve(Graph *graph,
                              std::optional<uint16_t> entry_value) {
  uint16_t entry = (entry_value.has_value())
                       ? entry_value.value()
                       : std::numeric_limits<uint16_t>::max();

  // The first element will always be zero, since the traversal must cross
  // through a common point
  std::size_t parallel_loops = (graph->size() - 1) * (graph->size() - 1);
  auto results = new int[parallel_loops];

#pragma omp parallel for shared(results)
  for (int i = 0; i < parallel_loops; i++) {
    std::vector<uint8_t> vertices(graph->size());
    vertices[0] = 0;
    vertices[1] = i / (graph->size() - 1) + 1;
    vertices[2] = i % (graph->size() - 1) + 1;
    if (vertices[1] == vertices[2]) {
      results[i] = entry;
      continue;
    }

    int vertex_idx = 3;
    for (int j = 1; j < graph->size(); j++)
      if (j != vertices[1] && j != vertices[2]) {
        vertices[vertex_idx] = j;
        vertex_idx++;
      }

    uint16_t result = entry;

    do {
      uint16_t instance = 0;
      int j = 0;
      for (; j < vertices.size() && instance < result; j++)
        instance += graph->distance(vertices[j], vertices[j + 1]);
      if (j == vertices.size() && instance < result)
        result = instance;
    } while (std::next_permutation(vertices.begin() + 3, vertices.end()));

#pragma omp critical
    { results[i] = result; }
  }

  uint16_t result = *std::min_element(results, results + parallel_loops);
  delete[] results;
  return result;
}
