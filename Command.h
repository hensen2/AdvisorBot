#pragma once

#include "AdvisorBot.h"
#include "OrderBook.h"
#include <string>
#include <vector>

class Command
{
public:
    Command();
    void cmdCaller(std::vector<std::string> commands);
    static void help();
    static void helpCmd(std::string command);
    static void prod(OrderBook orderBook);
    static double min(OrderBook orderBook, std::string arg1, std::string arg2, std::string timestep);
    static double max(OrderBook orderBook, std::string arg1, std::string arg2, std::string timestep);
    static void avg(OrderBook orderBook, std::string arg1, std::string arg2, std::string arg3, std::string timestep);
    static void predict(OrderBook orderBook, std::string arg1, std::string arg2, std::string arg3, std::string timestep);
    static void time(std::string timestep);
    static std::string step(OrderBook orderBook, std::string timestep);
    static OrderBook import(std::string filename);

private:
};