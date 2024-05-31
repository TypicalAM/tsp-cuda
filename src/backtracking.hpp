#ifndef TSP_BACKTRACKING
#define TSP_BACKTRACKING

#include "graph.hpp"
#include <optional>

class Backtracking : public TSPStrategy {
public:
  virtual uint16_t solve(Graph *graph,
                         std::optional<uint16_t> entry_value = std::nullopt);

private:
  void helper(uint8_t pos, uint16_t count, uint16_t dist);

  Graph *graph;
  std::vector<bool> visited;
  uint16_t *ans;
};

#endif // TSP_BACKTRACKING
