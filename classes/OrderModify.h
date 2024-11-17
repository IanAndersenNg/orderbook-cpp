#pragma once

# include "Usings.h"
# include "LevelInfo.h"
# include "OrderType.h"
# include "Side.h"
# include "Order.h"

// a pojo class that represents an order modify request
class OrderModify {
    private:
        OrderId orderId_;
        Side side_;
        Price price_;
        Quantity quantity_;

    public:
        OrderModify(OrderId orderId, Side side, Price price, Quantity quantity):
            orderId_(orderId),
            side_(side), 
            price_(price), 
            quantity_(quantity)
        {}

        OrderId getOrderId() const { return orderId_; }
        Side getSide() const { return side_; }
        Price getPrice() const { return price_; }
        Quantity getQuantity() const { return quantity_; }

        OrderPointer toOrderPointer(OrderType type) const {
            return std::make_shared<Order>(type, getOrderId(), getSide(), getPrice(), getQuantity());
        }
};