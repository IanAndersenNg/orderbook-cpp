# include "Usings.h"
# include "LevelInfo.h"
# include "OrderType.h"
# include "Side.h"

class OrderBookLevelInfos {
    private:
        LevelInfos bids_;
        LevelInfos asks_;

    public:
        OrderBookLevelInfos(LevelInfos& bids, LevelInfos& asks):
            bids_{ bids }, asks_{ asks }
        {}

        const LevelInfos& GetBids() const { return bids_; }
        const LevelInfos& GetAsks() const { return asks_; }
};