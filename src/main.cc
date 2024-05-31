#include "backtracking.hpp"
#include "bruteforce.hpp"
#include "bruteforce_cuda.hpp"
#include "bruteforce_omp.hpp"
#include "graph.hpp"
#include "greedy.hpp"
#include <bits/chrono.h>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <nlohmann/json.hpp>
#include <utility>

using json = nlohmann::json;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

std::pair<milliseconds, uint16_t>
run_strategy(TSPStrategy *strategy, Graph *graph,
             std::optional<uint16_t> entry = std::nullopt) {
  auto start = high_resolution_clock::now();
  uint16_t result = strategy->solve(graph, entry);
  auto end = high_resolution_clock::now();
  milliseconds time = duration_cast<milliseconds>(end - start);
  return std::make_pair(time, result);
}

int main(int argc, char *argv[]) {
  Graph graph(json::parse(std::ifstream(argv[1])));
  printf("%s", graph.print().c_str());

  Greedy greed;
  auto [greedy_time, greedy_res] = run_strategy(&greed, &graph);
  printf("Greedy solution took %ld ms, result: %d\n", greedy_time.count(),
         greedy_res);

  Backtracking bt;
  auto [bt_time, bt_res] = run_strategy(&bt, &graph);
  printf("Backtracking non-seeded solution took %ld ms, result: %d\n",
         bt_time.count(), bt_res);

  auto [bt_seeded_time, bt_seeded_res] = run_strategy(&bt, &graph, greedy_res);
  printf("Backtracking seeded solution took %ld ms, result: %d\n",
         bt_seeded_time.count(), bt_seeded_res);

  Bruteforce bf;
  auto [bf_time, bf_res] = run_strategy(&bf, &graph, greedy_res);
  printf("Bruteforce seeded solution took %ld ms, result: %d\n",
         bf_time.count(), bf_res);

  BruteforceOMP bf_omp;
  auto [bf_omp_time, bf_omp_res] = run_strategy(&bf_omp, &graph);
  printf("Bruteforce OMP seeded solution took %ld ms, result: %d\n",
         bf_omp_time.count(), bf_omp_res);

  BruteforceCUDA bf_cuda;
  auto [bf_cuda_time, bf_cuda_res] = run_strategy(&bf_cuda, &graph);
  printf("Bruteforce CUDA solution took %ld ms, result: %d\n",
         bf_cuda_time.count(), bf_cuda_res);
  return 0;
}
