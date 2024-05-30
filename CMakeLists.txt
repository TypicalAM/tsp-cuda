cmake_minimum_required(VERSION 3.12)
project(tsp-cuda)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(spdlog REQUIRED)

set(SOURCES 
  src/main.cc
  src/graph.cc
  src/bruteforce.cc
  src/greedy.cc
  src/backtracking.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-g")
target_link_libraries(${PROJECT_NAME}
  spdlog::spdlog
  nlohmann_json::nlohmann_json
  pthread
)
