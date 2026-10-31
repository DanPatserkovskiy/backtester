#include "backtest/metrics.hpp"
#include <cmath>
#include <algorithm>

namespace backtest {
    double total_return(const std::vector<double>& equity, double initial_cash) {
        if (equity.empty() || initial_cash == 0) {
            return 0.0;
        }
        return (equity.back() / initial_cash) - 1.0;
    }

    double max_drawdown(const std::vector<double>& equity) {
        if (equity.empty()) {
            return 0.0;
        }
        double max_dd = 0.0;
        double peak = equity[0];
        for (double val : equity) {
            if (val > peak) {
                peak = val;
            }
            double dd = (peak - val) / peak;
            if (dd > max_dd) {
                max_dd = dd;
            }
        }
        return max_dd;
    }

    double sharpe(const std::vector<double>& equity) {
        if (equity.size() < 2) { 
            return 0.0;
        }
        std::vector<double> returns;
        for (size_t i = 1; i < equity.size(); ++i) {
            returns.push_back((equity[i] / equity[i-1]) - 1.0);
        }
        double mean = 0.0;
        for (double r : returns) {
            mean += r;
        }
        mean /= returns.size();
        double var = 0.0;
        for (double r : returns) {
            var += (r - mean) * (r - mean);
        }
        var /= (returns.size() - 1);
        double stddev = std::sqrt(var);
        if (stddev == 0) {
            return 0.0;
        }
        return (mean / stddev) * std::sqrt(252.0);
    }
}
