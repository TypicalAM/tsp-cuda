#ifndef TSP_GREEDY
#define TSP_GREEDY

#include "graph.hpp"

class Greedy : public TSPStrategy {
public:
  virtual uint64_t solve(Graph *graph,
                         std::optional<uint64_t> entry_value = std::nullopt);
};

#endif // TSP_GREEDY
