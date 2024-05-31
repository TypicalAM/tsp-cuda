#include "backtracking.hpp"
#include <cstdint>
#include <limits>

uint16_t Backtracking::solve(Graph *graph,
                             std::optional<uint16_t> entry_value) {
  std::vector<bool> visited(graph->size());
  visited[0] = true;
  uint16_t result = (entry_value.has_value())
                        ? entry_value.value()
                        : std::numeric_limits<uint16_t>::max();
  this->visited = visited;
  this->ans = &result;
  this->graph = graph;
  helper(0, 1, 0);
  return result;
}

void Backtracking::helper(uint8_t pos, uint16_t count, uint16_t dist) {
  if (dist > *ans)
    return;

  if (count == graph->size() && graph->distance(pos, 0)) {
    if (dist + graph->distance(pos, 0) < *ans)
      *ans = dist + graph->distance(pos, 0);
    return;
  }

  for (int i = 0; i < graph->size(); i++)
    if (!visited[i] && graph->distance(pos, i)) {
      visited[i] = true;
      helper(i, count + 1, dist + graph->distance(pos, i));
      visited[i] = false;
    }
}
