#include <fstream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

int main (int argc, char *argv[]) {
	spdlog::info("Hello world!");
	json data = json::parse(std::ifstream(argv[1]));
	spdlog::info("Dumped {}", data.dump(4));
	return 0;
}
