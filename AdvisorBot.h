#pragma once

#include "OrderBook.h"
#include <string>
#include <vector>

class AdvisorBot
{
public:
    // constructor
    AdvisorBot();
    void init();
    static void welcomePrompt();

private:
    std::vector<std::string> getUserOption();
    void handleUserOptions(OrderBook orderBook, std::string currentTime, std::vector<std::string> input);
    std::vector<std::string> possibleCmds{"help", "prod", "min", "max", "avg", "predict", "time", "step", "import"};
    std::vector<std::string> possibleArgs{"bid", "ask", "ETH/BTC", "DOGE/BTC", "BTC/USDT", "ETH/USDT", "DOGE/USDT", "prod", "min", "max", "avg", "predict", "time", "step", "import"};
    std::string currentTime;
    OrderBook orderBook{"20200601.csv"};
};