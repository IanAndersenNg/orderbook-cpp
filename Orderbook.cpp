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

        // match bid and ask orders and then return a vector of trades
        Trades matchOrders(){
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

    public :

        Trades AddOrder(OrderPointer order){
            if(orders_.contains(order->getOrderId())){
                return {};
            }

            if(order -> getOrderType() == OrderType::FillAndKill && 
                !canMatch(order->getSide(), order->getPrice())){
                return {};
            }

            OrderPointers::iterator iterator;

            if (order -> getSide() == Side::Buy) {
                auto& orders = bids_[order->getPrice()];
                orders.push_back(order);
                iterator = std::next(orders.begin(), orders.size() - 1);
            } else {
                auto& orders = asks_[order->getPrice()];
                orders.push_back(order);
                iterator = std::next(orders.begin(), orders.size() - 1);
            }

            orders_.insert({ order->getOrderId(), OrderEntry{ order, iterator } });
            return matchOrders();
        }

        void cancelOrder(OrderId orderId) {
            if (!orders_.contains(orderId)) {
                return;
            }

            const auto [order, iterator] = orders_.at(orderId);
            orders_.erase(orderId);

            auto price = order->getPrice();
            
            if (order->getSide() == Side::Sell) {
                auto& orders = asks_[price];
                orders.erase(iterator);
                if (orders.empty()) {
                    asks_.erase(price);
                }
            } else {
                auto& orders = bids_[price];
                orders.erase(iterator);
                if (orders.empty()) {
                    bids_.erase(price);
                }
            }
        }
}; 

int main() {
    return 0;
};