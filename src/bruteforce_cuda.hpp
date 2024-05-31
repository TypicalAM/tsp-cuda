#ifndef TSP_BRUTEFORCE_CUDA
#define TSP_BRUTEFORCE_CUDA

#include "graph.hpp"

class BruteforceCUDA : public TSPStrategy {
public:
  virtual uint16_t solve(Graph *graph,
                         std::optional<uint16_t> entry_value = std::nullopt);
};

#endif // TSP_BRUTEFORCE_CUDA
