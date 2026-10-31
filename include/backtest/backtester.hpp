#pragma once
#include <vector>
#include "backtest/types.hpp"

namespace backtest {
    /**
     * @brief Запускает симуляцию бэктеста.
     * @param bars Вектор баров (OHLC).
     * @param signals Вектор сигналов.
     * @param initial_cash Начальный капитал.
     * @return Результат бэктеста (сделки, PnL, метрики).
     */
    Result run_backtest(const std::vector<Bar>& bars, const std::vector<Signal>& signals, double initial_cash = 10000.0);
}