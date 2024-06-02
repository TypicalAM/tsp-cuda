#ifndef TSP_BRUTEFORCE_CUDA
#define TSP_BRUTEFORCE_CUDA

#include "graph.hpp"

class BruteforceCUDA : public TSPStrategy {
public:
  virtual uint16_t solve(Graph *graph,
                         std::optional<uint16_t> entry_value = std::nullopt);

private:
  const static auto BLOCK_SIZE = 256;
};

#endif // TSP_BRUTEFORCE_CUDA
