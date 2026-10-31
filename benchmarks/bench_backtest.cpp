#include <benchmark/benchmark.h>
#include "backtest/sma.hpp"
#include "backtest/backtester.hpp"

static void BM_SmaCrossover(benchmark::State& state) {
    std::vector<double> prices(state.range(0));
    for (size_t i = 0; i < prices.size(); ++i) {
        prices[i] = 100.0 + (i % 20);
    }
    for (auto i : state) {
        auto signals = backtest::sma_crossover_signals(prices, 10, 30);
        benchmark::DoNotOptimize(signals);
    }
}
BENCHMARK(BM_SmaCrossover)->Range(1<<10, 1<<20);

static void BM_BacktestRun(benchmark::State& state) {
    std::vector<double> prices(state.range(0), 100.0);
    std::vector<backtest::Bar> bars;
    for (double p : prices) {
        bars.push_back({p, p, p, p});
    }
    auto signals = backtest::sma_crossover_signals(prices, 10, 30);
    for (auto i : state) {
        auto result = backtest::run_backtest(bars, signals, 10000.0);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_BacktestRun)->Range(1<<10, 1<<20);
BENCHMARK_MAIN();