#pragma once
#include <vector>
#include "backtest/types.hpp"

namespace backtest {
    /**
     * @brief Вычисляет простую скользящую среднюю (SMA).
     * @param prices Вектор цен.
     * @param window Размер окна (период).
     * @return Вектор значений SMA. Первые window-1 элементов равны 0.
     */
    std::vector<double> sma(const std::vector<double>& prices, size_t window);

    /**
     * @brief Генерирует сигналы Buy/Sell на основе пересечения двух SMA.
     * @param prices Вектор цен.
     * @param short_w Размер короткого окна.
     * @param long_w Размер длинного окна.
     * @return Вектор сигналов (Buy, Sell, Hold).
     */
    std::vector<Signal> sma_crossover_signals(const std::vector<double>& prices, size_t short_w, size_t long_w);
}
