#ifndef TSP_BACKTRACKING
#define TSP_BACKTRACKING

#include "graph.hpp"
#include <optional>

class Backtracking : public TSPStrategy {
public:
  virtual uint64_t solve(Graph *graph,
                         std::optional<uint64_t> entry_value = std::nullopt);

private:
  void helper(Graph *graph, std::vector<bool> visited, uint64_t pos,
              uint64_t count, uint64_t dist, uint64_t *ans);
};

#endif // TSP_BACKTRACKING
