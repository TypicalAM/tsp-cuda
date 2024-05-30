#include "backtracking.hpp"
#include <limits>

uint64_t Backtracking::solve(Graph *graph, std::optional<uint64_t> entry_value) { 
	std::vector<bool> visited(graph->size());
	visited[0] = true;
	uint64_t result = (entry_value.has_value()) ? entry_value.value() : std::numeric_limits<uint64_t>::max();
	helper(graph, visited, 0, 1, 0, &result);
	return result;
}

void Backtracking::helper(Graph *graph, std::vector<bool> visited, uint64_t pos,
                          uint64_t count, uint64_t dist, uint64_t *ans) {
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
      helper(graph, visited, i, count + 1, dist + graph->distance(pos, i), ans);
      visited[i] = false;
    }
}
