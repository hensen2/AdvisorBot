#pragma once

#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "Wallet.h"
#include <vector>

class MerkelMain
{
public:
    MerkelMain();
    // Call this to start simulation
    void init();

private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOptions(int userOption);

    std::string currentTime;

    OrderBook orderBook{"20200601.csv"};

    Wallet wallet;
};