# include <iostream>
# include <algorithm>
# include <string>
# include <map> 
# include <unordered_map>

#include "AllHeaders.h"

class OrderBook {
    private:

        struct OrderEntry {
            OrderPointer order_{ nullptr };
            OrderPointers::iterator location_;
        };

    std::map<Price, OrderPointers, std::greater<Price>> bids_;
    std::map<Price, OrderPointers, std::less<Price>> asks_;
    std::unordered_map<OrderId, OrderEntry> orders_;

    bool canMatch(Side side, Price price){
        if(side == Side::Buy){
            if(asks_.empty()){
                return false;
            }

            // dereference iterator to get the first element
            // std::pair<const Price, OrderPointers>

            const auto& [bestAsk, _] = *asks_.begin(); 
            return price >= bestAsk;

        } else {
            if(bids_.empty()){
                return false;
            }

            const auto& [bestBid, _] = *bids_.begin();
            return price <= bestBid;
        } 
    }

    // TODO : Implement this function
    Trades matchTrades(){
        Trades trades;
        trades.reserve(orders_.size());
        
        while (true) {

            if(bids_.empty() || asks_.empty()){
                break;
            }

            auto& [bidPrice, bids] = *bids_.begin();
            auto& [askPrice, asks] = *asks_.begin();

            if(bidPrice < askPrice){
                break;
            }

            while (bids.size() && asks.size()) {
                auto& bid = bids.front();
                auto& ask = asks.front();
            }

        }
        
    }
};

int main() {
    return 0;
};
