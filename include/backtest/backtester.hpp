#pragma once
#include <vector>
#include "backtest/types.hpp"

namespace backtest {
    Result run_backtest(const std::vector<Bar>& bars, const std::vector<Signal>& signals, double initial_cash = 10000.0);
}
