#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>

// Tell compilier to create default constructor
MerkelMain::MerkelMain() = default;

void MerkelMain::init()
{
    std::cout << "=============================" << std::endl;
    std::cout << "*** Welcome to AdvisorBot ***" << std::endl;
    std::cout << "=============================\n"
              << std::endl;

    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOptions(input);
    }
}

// Main menu options printed to console
void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help" << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer" << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid" << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet" << std::endl;
    // 6 continue
    std::cout << "6: Continue" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
}

// console message for user input 1
void MerkelMain::printHelp()
{
    std::cout << "You do need help... You're broke! We are here to make some money, so let's analyze the crypto market to start making some bids and offers." << std::endl;
}

// console message for user input 2
void MerkelMain::printMarketStats()
{
    for (std::string const &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p,
                                                                  currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
}

// console message for user input 3
void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter amount: product,price,amount (e.g. ETH/BTC,200,0.5)" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);

            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds." << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "MerkelMain::enterAsk - Bad input" << std::endl;
        }
    }
}

// console message for user input 4
void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter amount: product,price,amount (e.g. ETH/BTC,200,0.5)" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input!" << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid);

            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds." << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "MerkelMain::enterBid - Bad input" << std::endl;
        }
    }
}

// console message for user input 5
void MerkelMain::printWallet()
{
    // std::cout << "Your wallet is empty. Re-evaluate your entire life." << std::endl;
    std::cout << wallet.toString() << std::endl;
}

// console message for user input 6
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame..." << std::endl;

    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;

        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price: " << sale.price << "amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    // User input
    int userOption = 0;
    std::string line;

    // Main menu prompt
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "You selected: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOptions(int userOption)
{
    // Conditional output based on user input
    if (userOption == 0 || userOption > 6)
    {
        std::cout << "Invalid choice. Choose a number 1-6" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
}