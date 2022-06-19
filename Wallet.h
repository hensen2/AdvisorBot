#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <map>

class Wallet
{
public:
    Wallet();
    /** insert currency to the wallet */
    void insertCurrency(std::string type, double amount);
    /** remove currency from the wallet */
    bool removeCurrency(std::string type, double amount);
    /** check if wallet has sufficient funds */
    bool containsCurrency(std::string type, double amount);
    /** checks if wallet can fulfill ask/bid */
    bool canFulfillOrder(OrderBookEntry order);
    /** update the contents of the wallet */
    void processSale(OrderBookEntry &sale);
    /** generate a string representation of the wallet */
    std::string toString();

    friend std::ostream &operator<<(std::ostream &os, Wallet &wallet);

private:
    std::map<std::string, double> currencies;
};