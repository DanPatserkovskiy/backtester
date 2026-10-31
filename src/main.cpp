#include <iostream>
#include "backtest/sma.hpp"
#include "backtest/backtester.hpp"
#include "backtest/metrics.hpp"

int main() {
    std::vector<double> prices = {
    110, 105, 100, 95, 90, 85, 80,
    85, 90, 95, 100, 105, 110, 115, 120, 125,
    120, 115, 110, 105, 100, 95, 90
    };
    std::vector<backtest::Bar> bars;
    for (double p : prices) {
        bars.push_back({p, p, p, p});
    }
    auto signals = backtest::sma_crossover_signals(prices, 3, 5);
    auto result = backtest::run_backtest(bars, signals, 10000.0);
    std::cout << "Total Return: " << result.total_return * 100 << "%\n";
    std::cout << "Max Drawdown: " << result.max_drawdown * 100 << "%\n";
    std::cout << "Sharpe Ratio: " << result.sharpe << "\n";
    std::cout << "Trades executed: " << result.trades.size() << "\n";
    return 0;
}