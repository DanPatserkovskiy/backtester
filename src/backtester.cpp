#include "backtest/backtester.hpp"
#include "backtest/metrics.hpp"

namespace backtest {
    Result run_backtest(const std::vector<Bar>& bars, const std::vector<Signal>& signals, double initial_cash) {
        Result res;
        res.trades.clear();
        res.equity_curve.clear();
        double cash = initial_cash;
        double position = 0.0;
        double entry_price = 0.0;
        size_t entry_bar = 0;
        res.realized_pnl = 0.0;
        for (size_t i = 0; i < bars.size(); ++i) {
            if (i > 0) {
                Signal sig = signals[i-1];
                double price = bars[i].open;
                if (sig == Signal::Buy && position == 0.0) {
                    position = 1.0;
                    entry_price = price;
                    entry_bar = i;
                    cash -= position * price;
                } else if (sig == Signal::Sell && position > 0.0) {
                    double pnl = (price - entry_price) * position;
                    res.trades.push_back({entry_bar, i, entry_price, price, position, pnl});
                    res.realized_pnl += pnl;
                    cash += position * price;
                    position = 0.0;
                }
            }
            double equity = cash + position * bars[i].close;
            res.equity_curve.push_back(equity);
        }
        res.unrealized_pnl = (position > 0.0) ? (bars.back().close - entry_price) * position : 0.0;
        res.total_return = total_return(res.equity_curve, initial_cash);
        res.max_drawdown = max_drawdown(res.equity_curve);
        res.sharpe = sharpe(res.equity_curve);
        return res;
    }
}
