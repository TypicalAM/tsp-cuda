#include "graph.hpp"
#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

using json = nlohmann::json;

Graph::Graph(json data) {
  auto adjacency = data["adjacency"];
  for (json::iterator node = adjacency.begin(); node != adjacency.end();
       ++node) {
    std::vector<uint64_t> row;
    row.resize(adjacency.size());
    distances.push_back(row);
  }

  int from = 0;
  for (json::iterator node = adjacency.begin(); node != adjacency.end();
       ++node) {
    for (json::iterator edge = node->begin(); edge != node->end(); ++edge) {
      uint64_t weight = (*edge)["weight"];
      uint64_t to = (*edge)["id"];
      distances[from][to] = weight;
      distances[to][from] = weight;
    }

    from++;
  }
}

std::size_t Graph::size() { return distances.size(); }

uint64_t Graph::distance(uint64_t from, uint64_t to) {
  return distances[from][to];
}

std::string Graph::print() {
  std::stringstream ss;
  ss << "\n";
  for (const auto row : distances) {
    for (const auto elem : row)
      ss << std::setw(3) << std::to_string(elem) << " ";
    ss << "\n";
  }
  return ss.str();
}
