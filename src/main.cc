#include "backtracking.hpp"
#include "bruteforce.hpp"
#include "graph.hpp"
#include "greedy.hpp"
#include <bits/chrono.h>
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <utility>

using json = nlohmann::json;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

std::pair<milliseconds, uint64_t>
run_strategy(TSPStrategy *strategy, Graph *graph,
             std::optional<uint64_t> entry = std::nullopt) {
  auto start = high_resolution_clock::now();
  uint64_t result = strategy->solve(graph, entry);
  auto end = high_resolution_clock::now();
  milliseconds time = duration_cast<milliseconds>(end - start);
  return std::make_pair(time, result);
}

int main(int argc, char *argv[]) {
  Graph graph(json::parse(std::ifstream(argv[1])));
  spdlog::info(graph.print());

  Greedy greed;
  auto [greedy_time, greedy_res] = run_strategy(&greed, &graph);
  spdlog::info("Greedy solution took {}ms, result: {}", greedy_time.count(),
               greedy_res);

  Backtracking bt;
  auto [bt_time, bt_res] = run_strategy(&bt, &graph);
  spdlog::info("Backtracking non-seeded solution took {}ms, result: {}",
               bt_time.count(), bt_res);

  auto [bt_seeded_time, bt_seeded_res] = run_strategy(&bt, &graph, greedy_res);
  spdlog::info("Backtracking seeded solution took {}ms, result: {}",
               bt_seeded_time.count(), bt_seeded_res);

  Bruteforce bf;
  auto [bf_time, bf_res] = run_strategy(&bf, &graph);
  spdlog::info("Bruteforce solution took {}ms, result: {}", bf_time.count(),
               bf_res);
  return 0;
}
