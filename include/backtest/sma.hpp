#pragma once
#include <vector>
#include "backtest/types.hpp"

namespace backtest {
    std::vector<double> sma(const std::vector<double>& prices, size_t window);
    std::vector<Signal> sma_crossover_signals(const std::vector<double>& prices, size_t short_w, size_t long_w);
}
