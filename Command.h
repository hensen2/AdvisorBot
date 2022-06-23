#pragma once

#include "AdvisorBot.h"
#include "OrderBook.h"
#include <string>
#include <vector>

class Command
{
public:
    Command(std::string _cmd);
    Command(std::string _cmd, std::string _arg1);
    Command(std::string _cmd, std::string _arg1, OrderBookType _arg2, std::string _order);
    Command(std::string _cmd, std::string _arg1, OrderBookType _arg2, std::string _order, std::string _arg3);

    static void help();
    static void helpCmd(std::string command);
    static void prod(OrderBook orderBook);
    static double min(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string timestep, std::string order);
    static double max(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string timestep, std::string order);
    static void avg(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string arg3, std::string timestep, std::string order);
    static void predict(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string arg3, std::string timestep, std::string order);
    static void time(std::string timestep);
    static std::string step(OrderBook orderBook, std::string timestep);
    static OrderBook import(std::string filename);

private:
    std::string cmd{};
    std::string arg1{};
    OrderBookType arg2{};
    std::string order{};
    std::string arg3{};
};