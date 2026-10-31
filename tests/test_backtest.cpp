#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "backtest/sma.hpp"
#include "backtest/metrics.hpp"
#include "backtest/backtester.hpp"

TEST_CASE("SMA calculation works correctly") {
    std::vector<double> prices = {1, 2, 3, 4, 5};
    auto result = backtest::sma(prices, 3);
    CHECK(result[2] == doctest::Approx(2.0));
    CHECK(result[3] == doctest::Approx(3.0));
    CHECK(result[4] == doctest::Approx(4.0));
}

TEST_CASE("Max Drawdown calculation") {
    std::vector<double> equity = {100, 120, 90, 110};
    CHECK(backtest::max_drawdown(equity) == doctest::Approx(0.25));
}

TEST_CASE("Backtest execution and PnL") {
    std::vector<double> prices = {100, 110, 120, 130, 120, 110};
    std::vector<backtest::Bar> bars;
    for (double p : prices) bars.push_back({p, p, p, p});
    
    std::vector<backtest::Signal> signals = {
        backtest::Signal::Buy,
        backtest::Signal::Hold, 
        backtest::Signal::Hold, 
        backtest::Signal::Sell,
        backtest::Signal::Hold, 
        backtest::Signal::Hold
    };
    
    auto result = backtest::run_backtest(bars, signals, 1000.0);
    CHECK(result.trades.size() == 1);
    CHECK(result.trades[0].entry_price == doctest::Approx(110.0));
    CHECK(result.trades[0].exit_price == doctest::Approx(120.0));
    CHECK(result.realized_pnl == doctest::Approx(10.0));
}