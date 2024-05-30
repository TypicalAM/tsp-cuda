#ifndef TSP_GRAPH
#define TSP_GRAPH

#include <nlohmann/json_fwd.hpp>

class Graph {
public:
	Graph(nlohmann::json data);

	std::size_t size();
	uint64_t distance(uint64_t from, uint64_t to);
	std::string print();

private:
	std::vector<std::vector<uint64_t>> distances;
};

#endif // TSP_GRAPH
