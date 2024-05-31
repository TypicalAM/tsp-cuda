#include "greedy.hpp"
#include <cstdint>
#include <limits>

uint64_t Greedy::solve(Graph *graph, std::optional<uint64_t> entry_value) {
  std::vector<uint64_t> vertices(graph->size());
  for (int i = 0; i < graph->size(); i++)
    vertices[i] = i;

  std::vector<bool> visited(graph->size());
  uint64_t total = 0, min_index = 0, vertex = 0;
  for (int i = 0; i < vertices.size() - 1; i++) {
    uint64_t min = std::numeric_limits<uint64_t>::max();
    visited[vertex] = true;

    for (int j = 0; j < vertices.size(); j++) {
      uint64_t dist = graph->distance(vertex, j);
      if (dist && dist < min && !visited[j]) {
        min = dist;
        min_index = j;
      }
    }

    vertex = min_index;
    total += min;
  }

  total += graph->distance(vertex, 0);
  return total;
}
