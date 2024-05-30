#ifndef TSP_BRUTEFORCE
#define TSP_BRUTEFORCE

#include "graph.hpp"

class Bruteforce : public TSPStrategy {
public:
  virtual uint64_t solve(Graph *graph,
                         std::optional<uint64_t> entry_value = std::nullopt);
};

#endif // TSP_BRUTEFORCE
