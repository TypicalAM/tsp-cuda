#include "bruteforce_omp.hpp"
#include <algorithm>
#include <cstdint>
#include <limits>

uint16_t BruteforceOMP::solve(Graph *graph,
                              std::optional<uint16_t> entry_value) {
  uint16_t entry = (entry_value.has_value())
                       ? entry_value.value()
                       : std::numeric_limits<uint16_t>::max();

  // The first element will always be zero, since the traversal must cross
  // through a common point
  std::size_t parallel_loops = (graph->size() - 1) * (graph->size() - 1);
  std::vector<uint8_t> results(parallel_loops);

#pragma omp parallel for
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
    for (int i = 1; i < graph->size(); i++)
      if (i != vertices[1] && i != vertices[2]) {
        vertices[vertex_idx] = i;
        vertex_idx++;
      }

    uint16_t result = entry;

    do {
      uint16_t instance =
          graph->distance(vertices[vertices.size() - 1], vertices[0]);
      int i = 0;
      for (; i < vertices.size() && instance < result; i++)
        instance += graph->distance(vertices[i], vertices[i + 1]);
      if (i == vertices.size() && instance < result)
        result = instance;
    } while (std::next_permutation(vertices.begin() + 3, vertices.end()));

    results[i] = result;
  }

  return *std::min_element(results.begin(), results.end());
}
