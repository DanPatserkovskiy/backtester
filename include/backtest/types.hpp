#pragma once
#include <vector>
#include <cstddef>

namespace backtest {
    struct Bar { 
        double open, high, low, close; 
    };

    enum class Signal { 
        Buy, Sell, Hold 
    };

    struct Trade {
        size_t entry_bar;
        size_t exit_bar;
        double entry_price;
        double exit_price;
        double qty;
        double pnl;
    };

    struct Result {
        std::vector<double> equity_curve;
        std::vector<Trade> trades;
        double realized_pnl;
        double unrealized_pnl;
        double total_return;
        double max_drawdown;
        double sharpe;
    };
}
