#ifndef TSP_BRUTEFORCE
#define TSP_BRUTEFORCE

#include "graph.hpp"

class Bruteforce : public TSPStrategy {
public:
  virtual uint16_t solve(Graph *graph,
                         std::optional<uint16_t> entry_value = std::nullopt);
};

#endif // TSP_BRUTEFORCE
