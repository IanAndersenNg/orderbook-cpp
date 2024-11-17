#pragma once

#include "TradeInfo.h"

class Trade{
    public:
        Trade(const TradeInfo askTrade, const TradeInfo buyTrade):
            askTrade_{ askTrade },
            bidTrade_{ buyTrade }
        {}

    private:
        TradeInfo askTrade_;
        TradeInfo bidTrade_;

    const TradeInfo& getBidTrade() const { return bidTrade_; }
    const TradeInfo& getAskTrade() const { return askTrade_; }
};

using Trades = std::vector<Trade>;