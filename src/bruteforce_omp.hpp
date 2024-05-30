#ifndef TSP_BRUTEFORCE_OMP
#define TSP_BRUTEFORCE_OMP

#include "graph.hpp"

class BruteforceOMP : public TSPStrategy {
public:
  virtual uint64_t solve(Graph *graph,
                         std::optional<uint64_t> entry_value = std::nullopt);
};

#endif // TSP_BRUTEFORCE_OMP
