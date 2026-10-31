cmake_minimum_required(VERSION 3.14)
project(SmaBacktester VERSION 1.0 LANGUAGES CXX)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)
FetchContent_MakeAvailable(doctest)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.0
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

add_library(backtest_core
    src/sma.cpp
    src/backtester.cpp
    src/metrics.cpp
)
target_include_directories(backtest_core PUBLIC include)

add_executable(backtest_cli src/main.cpp)
target_link_libraries(backtest_cli PRIVATE backtest_core)

add_executable(test_backtest tests/test_backtest.cpp)
target_link_libraries(test_backtest PRIVATE backtest_core doctest::doctest)

enable_testing()
add_test(NAME UnitTests COMMAND test_backtest)

add_executable(bench_backtest benchmarks/bench_backtest.cpp)
target_link_libraries(bench_backtest PRIVATE backtest_core benchmark::benchmark)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
    doxygen_add_docs(docs ${DOXYGEN_INPUT} COMMENT "Generate documentation")
endif()
