cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
set(project_name "tsp-cuda")
project(${project_name} LANGUAGES CXX C CUDA)  

# Default build type is Release
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(cxx_flags 
	$<$<CXX_COMPILER_ID:MSVC>:-D_SCL_SECURE_NO_WARNINGS /openmp /std:c++17>
	$<$<CXX_COMPILER_ID:GNU>:-m64 -fopenmp -g -std=c++17>
	$<$<CXX_COMPILER_ID:Clang>:-m64 -fopenmp -g -std=c++17>
)

set(MSVC_XCOMPILER_FLAGS "/openmp /std:c++17")
set(cuda_flags
    $<$<CXX_COMPILER_ID:GNU>:-Xcompiler -Wall -fopenmp -O3>
	$<$<CXX_COMPILER_ID:Clang>:-Xcompiler -Wall -fopenmp -O3>
	$<$<CXX_COMPILER_ID:MSVC>:-Xcompiler ${MSVC_XCOMPILER_FLAGS}>
    -Xcudafe=--display_error_number    
	-lineinfo	
	--expt-extended-lambda	
	-use_fast_math		
    $<$<CXX_COMPILER_ID:GNU>:-O3>	
	--expt-relaxed-constexpr	
    -Xptxas -warn-spills -res-usage   
	--ptxas-options=-v	
    #-G	
)

add_library(developer_flags INTERFACE)
target_compile_options(developer_flags INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:${cxx_flags}>
    $<$<COMPILE_LANGUAGE:CUDA>:${cuda_flags}>
)
target_include_directories(developer_flags INTERFACE ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
target_compile_features(developer_flags INTERFACE cxx_std_17)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(developer_flags INTERFACE OpenMP::OpenMP_CXX)
endif()

find_package(nlohmann_json 3.2.0 REQUIRED)
if (nlohmann_json_FOUND)
    target_link_libraries(developer_flags INTERFACE nlohmann_json::nlohmann_json)
endif()

set(SOURCES 
  src/main.cc
  src/graph.cc
  src/bruteforce.cc
  src/bruteforce_omp.cc
  src/greedy.cc
  src/backtracking.cc
  src/bruteforce_cuda.cu
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PUBLIC developer_flags)
