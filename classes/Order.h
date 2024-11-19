#pragma once

#include <stdexcept>
#include <memory>
#include <list>

# include "Usings.h"
# include "LevelInfo.h"
# include "OrderType.h"
# include "Side.h"

class Order {
    private:
        OrderType orderType_;
        OrderId orderId_;
        Side side_;
        Price price_;
        Quantity quantity_;
        Quantity initialQuantity_;
        Quantity remainingQuantity_;

    public:
        Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity):
            orderType_(orderType), 
            orderId_(orderId), 
            side_(side), 
            price_(price), 
            quantity_(quantity), 
            initialQuantity_(quantity), 
            remainingQuantity_(quantity)
        {}

    OrderType getOrderType() const { return orderType_; }
    OrderId getOrderId() const { return orderId_; }
    Side getSide() const { return side_; }
    Price getPrice() const { return price_; }
    Quantity getQuantity() const { return quantity_; }
    Quantity getInitialQuantity() const { return initialQuantity_; }
    Quantity getRemainingQuantity() const { return remainingQuantity_; }

    void fill(Quantity quantity){#include <list>
        if(quantity > remainingQuantity_){
            throw std::logic_error("Quantity to fill is greater than remaining quantity");
        }

        remainingQuantity_ -= quantity;
    }

    bool isFilled() const { return getRemainingQuantity() == 0; }
    
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;