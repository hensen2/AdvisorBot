#pragma once

#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <string>
#include <vector>

class OrderBook
{
public:
    /** constructor, reading a csv data file */
    OrderBook(std::string filename);
    /** return vector of all known products in the dataset */
    std::vector<std::string> getKnownProducts();
    /** return vector of all known timestamps in the dataset */
    std::vector<std::string> getKnownTimestamps();
    /** return vector of Orders according to the sent filters */
    std::vector<OrderBookEntry> getOrders(std::string product,
                                          OrderBookType type,
                                          std::string timestamp);

    std::vector<OrderBookEntry> getOrdersTP(std::string product,
                                            OrderBookType type);

    /** returns the earliest time in the orderbook */
    std::string getEarliestTime();
    /** returns the time thirty minutes into the orderbook */
    std::string getLaterTime();
    /** returns the next time after the sent time in the orderbook
     * If there is no next timestamp, wraps around to the start
     */
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry &order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    static double getHighPrice(std::vector<OrderBookEntry> &orders);
    static double getLowPrice(std::vector<OrderBookEntry> &orders);

private:
    std::vector<OrderBookEntry> orders;
};