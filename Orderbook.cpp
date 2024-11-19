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

    bool validateMatchTrade(Price bidPrice, Price askPrice){

        if(bids_.empty() || asks_.empty()){
            return false;    
        }

        if(bidPrice < askPrice){
            return false;
        }

        return true;
    }

    Trades matchTrades(){
        Trades trades;
        trades.reserve(orders_.size());
        
        while (true) {
            auto& [bidPrice, bids] = *bids_.begin();
            auto& [askPrice, asks] = *asks_.begin();

            if (!validateMatchTrade(bidPrice, askPrice)) {
                break;
            }

            while (bids.size() && asks.size()) {
                auto& bid = bids.front();
                auto& ask = asks.front();

                Quantity quantity = std::min(bid->getRemainingQuantity(), ask->getRemainingQuantity());

                bid -> fill(quantity);
                ask -> fill(quantity);

                if (bid -> isFilled()) {
                    bids.pop_front();
                    orders_.erase(bid -> getOrderId());
                }

                if (ask -> isFilled()) {
                    asks.pop_front();
                    orders_.erase(ask -> getOrderId());
                }
                
                Trade matchedTrade = Trade(
                    TradeInfo{bid -> getOrderId(), bid -> getPrice(), quantity},
                    TradeInfo{ask -> getOrderId(), ask -> getPrice(), quantity}
                );

                trades.push_back(matchedTrade);
            }
        }



        cancelFillAndKillOrders();
        return trades;
    }

    void cancelFillAndKillOrders(){
        if(!bids_.empty()) {
            auto& [_, bids] = *bids_.begin();
            auto& order = bids.front();
            if(order->getOrderType() == OrderType::FillAndKill){
                cancelOrder(order->getOrderId());
            }
        }

        if(!asks_.empty()) {
            auto& [_, asks] = *asks_.begin();
            auto& order = asks.front();
            if(order->getOrderType() == OrderType::FillAndKill){
                cancelOrder(order->getOrderId());
            }
        }
    } 
    
    void cancelOrder(OrderId orderId){
        return;
    }
};

int main() {
    return 0;
};
