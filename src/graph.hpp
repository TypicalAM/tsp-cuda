#ifndef TSP_GRAPH
#define TSP_GRAPH

#include <nlohmann/json_fwd.hpp>
#include <optional>

class Graph {
public:
  Graph(nlohmann::json data);

  const std::size_t size();
  const uint64_t distance(uint64_t from, uint64_t to);
  const std::string print();

private:
  std::vector<std::vector<uint64_t>> distances;
};

class TSPStrategy {
public:
  virtual ~TSPStrategy() {}
  virtual uint64_t
  solve(Graph *graph, std::optional<uint64_t> entry_value = std::nullopt) = 0;
};

#endif // TSP_GRAPH
