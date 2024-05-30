#include "graph.hpp"
#include <fstream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

int main (int argc, char *argv[]) {
	Graph g(json::parse(std::ifstream(argv[1])));
	spdlog::info(g.print());
	return 0;
}
