#ifndef TSP_GRAPH
#define TSP_GRAPH

#include <nlohmann/json_fwd.hpp>
#include <optional>

class Graph {
public:
  Graph(nlohmann::json data);

  std::size_t size();
  uint16_t distance(uint8_t from, uint8_t to);
  std::string print();

private:
  std::vector<std::vector<uint16_t>> distances;
};

class TSPStrategy {
public:
  virtual ~TSPStrategy() {}
  virtual uint16_t
  solve(Graph *graph, std::optional<uint16_t> entry_value = std::nullopt) = 0;
};

#endif // TSP_GRAPH
