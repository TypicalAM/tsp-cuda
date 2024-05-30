#include "bruteforce.hpp"
#include <algorithm>
#include <limits>
#include <vector>

uint64_t Bruteforce::solve(Graph *graph, std::optional<uint64_t> entry_value) {
  std::vector<uint64_t> vertices(graph->size() - 1);
  for (int i = 0; i < vertices.size(); i++)
    vertices[i] = i;

  uint64_t result = (entry_value.has_value())
                        ? entry_value.value()
                        : std::numeric_limits<uint64_t>::max();
  do {
    uint64_t total = graph->distance(0, vertices[vertices.size() - 1] + 1) +
                     graph->distance(0, vertices[0] + 1);
    int i = 0;
    for (; i < vertices.size() - 1 && total < result; i++)
      total += graph->distance(vertices[i] + 1, vertices[i + 1] + 1);
    if (i == vertices.size() - 1 && total < result)
      result = total;
  } while (std::next_permutation(vertices.begin(), vertices.end()));

  return result;
};
