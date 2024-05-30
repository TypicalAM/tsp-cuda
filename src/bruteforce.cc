#include "bruteforce.hpp"
#include <algorithm>
#include <limits>
#include <vector>

uint64_t Bruteforce::solve(Graph *graph, std::optional<uint64_t> entry_value) {
  std::vector<uint64_t> vertices(graph->size() - 1);
  for (int i = 0; i < vertices.size(); i++)
    vertices[i] = i;

  uint64_t result = std::numeric_limits<uint64_t>::max();
  do {
    uint64_t total = graph->distance(0, vertices[vertices.size() - 1] + 1) +
                     graph->distance(0, vertices[0] + 1);
    for (int i = 0; i < vertices.size() - 1; i++)
      total += graph->distance(vertices[i] + 1, vertices[i + 1] + 1);
    if (total < result)
      result = total;
  } while (std::next_permutation(vertices.begin(), vertices.end()));

  return result;
};
