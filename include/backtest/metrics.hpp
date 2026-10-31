#pragma once
#include <vector>

namespace backtest {
    /** @brief Вычисляет общую доходность (Total Return). */
    double total_return(const std::vector<double>& equity, double initial_cash);
    
    /** @brief Вычисляет максимальную просадку (Max Drawdown). */
    double max_drawdown(const std::vector<double>& equity);
    
    /** @brief Вычисляет коэффициент Шарпа (Sharpe Ratio). */
    double sharpe(const std::vector<double>& equity);
}