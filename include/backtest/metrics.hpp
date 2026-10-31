#pragma once
#include <vector>

namespace backtest {
    double total_return(const std::vector<double>& equity, double initial_cash);
    double max_drawdown(const std::vector<double>& equity);
    double sharpe(const std::vector<double>& equity);
}
