# Orderbook Project

This project is an orderbook made in C++ that tracks buy and sell order with different types

## Classes Explanation

### Price Levels

**Level info**: The level info represent the price level and the quantity available at that price level. 

Example: $50 stocks at 90 quantity.

**Order Book level info**: Seperates the level info into bid and asks. bids are for buyers and ask for seller.

Example: buyer's bids of $90 at 10 quantity, seller's asks of $90 at 10 quantity. This class aims to differentiate these cases to bids and asks in the orderbook.

### Orders

**Side** : Enum class to differentiate buy/sell side order.

**OrderType** : Enum class to show different order types such as FillAndKill and GoodTillCancel.

**Order** : The order class represents a trader's order 

**OrderModify** :  a pojo class to modify the order class

### Trade

**Trade** : A class that contains the bid TradeInfo and askTradeInfo being traded (?)

**TradeInfo** : Provides information about the trade providing the orderId, price and quantity.





