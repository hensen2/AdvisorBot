#pragma once

#include "AdvisorBot.h"
#include "OrderBook.h"
#include <string>
#include <vector>

class Command
{
public:
    Command(OrderBook _orderBook, std::string _currentTime, std::string _cmd);
    Command(OrderBook _orderBook, std::string _currentTime, std::string _cmd, std::string _arg1);
    Command(OrderBook _orderBook, std::string _currentTime, std::string _cmd, std::string _arg1, OrderBookType _arg2, std::string _order);
    Command(OrderBook _orderBook, std::string _currentTime, std::string _cmd, std::string _arg1, OrderBookType _arg2, std::string _order, std::string _arg3);

    void invoke();
    void help();
    void helpCmd(std::string command);
    void prod(OrderBook orderBook);
    double min(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string timestep, std::string order);
    double max(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string timestep, std::string order);
    void avg(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string arg3, std::string timestep, std::string order);
    void predict(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string arg3, std::string timestep, std::string order);
    void time(std::string timestep);
    std::string step(OrderBook orderBook, std::string timestep);
    OrderBook import(std::string filename);

private:
    OrderBook orderBook;
    std::string currentTime;
    std::string cmd;
    std::string arg1;
    OrderBookType arg2;
    std::string order;
    std::string arg3;
};