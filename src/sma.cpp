#include "backtest/sma.hpp"
#include <numeric>

namespace backtest {
    std::vector<double> sma(const std::vector<double>& prices, size_t window) {
        std::vector<double> result(prices.size(), 0.0);
        if (prices.size() < window || window == 0) {
            return result;
        }
        double sum = 0.0;
        for (size_t i = 0; i < prices.size(); ++i) {
            sum += prices[i];
            if (i >= window) {
                sum -= prices[i - window];
            }
            if (i >= window - 1) {
                result[i] = sum / window;
            }
        }
        return result;
    }
    std::vector<Signal> sma_crossover_signals(const std::vector<double>& prices, size_t short_w, size_t long_w) {
        auto s = sma(prices, short_w);
        auto l = sma(prices, long_w);
        std::vector<Signal> signals(prices.size(), Signal::Hold);
        for (size_t i = 1; i < prices.size(); ++i) {
            if (i < long_w) {
                continue;
            }
            if (s[i-1] <= l[i-1] && s[i] > l[i]) {
                signals[i] = Signal::Buy;
            }
            else if (s[i-1] >= l[i-1] && s[i] < l[i]) {
                signals[i] = Signal::Sell;
            }
        }
        return signals;
    }
}
