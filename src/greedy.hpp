#ifndef TSP_GREEDY
#define TSP_GREEDY

#include "graph.hpp"

class Greedy : public TSPStrategy {
public:
  virtual uint16_t solve(Graph *graph,
                         std::optional<uint16_t> entry_value = std::nullopt);
};

#endif // TSP_GREEDY
