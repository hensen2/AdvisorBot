#include "AdvisorBot.h"
#include "StringParser.h"
#include "Command.h"
#include <iostream>
#include <string>
#include <algorithm>

// Tell compiler to create default constructor
AdvisorBot::AdvisorBot() = default;

void AdvisorBot::init()
{
    std::vector<std::string> input;
    currentTime = orderBook.getLaterTime();
    welcomePrompt();

    while (true)
    {
        input = getUserOption();
        handleUserOptions(orderBook, currentTime, input);
    }
}

void AdvisorBot::welcomePrompt()
{
    std::cout << "===============================================" << std::endl;
    std::cout << "  $$$$$***** Welcome to AdvisorBot *****$$$$$  " << std::endl;
    std::cout << "==============================================="
              << "\n"
              << std::endl;

    std::cout << "Usage:"
              << "\n"
              << std::endl;
    std::cout << " advisorbot$ <info>"
              << std::endl;
    std::cout << " user$ <cmd>"
              << "\n"
              << std::endl;

    std::cout << "All commands:"
              << "\n"
              << std::endl;
    std::cout << " help                                    "
              << "list all available commands" << std::endl;

    std::cout << " help <cmd>                              "
              << "output help for the specified <command>" << std::endl;

    std::cout << " prod                                    "
              << "list available products" << std::endl;

    std::cout << " min <product> <order>                   "
              << "find minimum <order> for <product> in current time step" << std::endl;

    std::cout << " max <product> <order>                   "
              << "find maximum <order> for <product> in current time step" << std::endl;

    std::cout << " avg <product> <order> <timesteps>       "
              << "compute average <order> for the sent <product> over the sent number of <timesteps>" << std::endl;

    std::cout << " predict <max/min> <order> <product>     "
              << "predict <max> or <min> and <order> for the sent <product> for the next time step" << std::endl;

    std::cout << " time                                    "
              << "state current time in dataset, i.e. which timeframe are we looking at" << std::endl;

    std::cout << " step                                    "
              << "move to next time step" << std::endl;

    std::cout << " import <file>                           "
              << "update current csv <file> to be used as new dataset" << std::endl;

    std::cout << "\n"
              << std::endl;
    std::cout << "Inputs:"
              << "\n"
              << std::endl;
    std::cout << " <product>                               "
              << "ETH/BTC, DOGE/BTC, BTC/USDT, ETH/USDT, DOGE/USDT" << std::endl;
    std::cout << " <order>                                 "
              << "bid, ask" << std::endl;
    std::cout << " <timesteps>                             "
              << "integer (i.e. 50, 999)" << std::endl;
    std::cout << " <file>                                  "
              << "*.csv (timestep, product, order, price, amount)" << std::endl;

    std::cout << "\n"
              << std::endl;
}

std::vector<std::string> AdvisorBot::getUserOption()
{
    // User input
    std::string userOption;
    std::string line;

    // Commands vector to be returned
    std::vector<std::string> commands;

    // Main menu prompt
    std::cout << "advisorbot$ "
              << "Please enter a valid command, or enter help to list all available commands" << std::endl;

    std::cout << "user$ ";

    // Accept user input and test for correctness
    std::getline(std::cin, line);
    try
    {
        userOption = line;
        std::cout << "advisorbot$ You entered: " << userOption << std::endl;

        // Call command parser and return vector of strings
        commands = StringParser::tokeniseCmds(userOption, ' ');

        if (commands.size() < 1 || commands.size() > 4) // Incorrect input
        {
            std::cout << "Bad input, incorrect number of arguments" << std::endl;
            throw std::exception{};
        }

        if (std::find(possibleCmds.begin(), possibleCmds.end(), commands[0]) != possibleCmds.end())
        {
            for (int i = 1; i < commands.size(); i++)
            {
                if (std::find(possibleArgs.begin(), possibleArgs.end(), commands[i]) != possibleArgs.end())
                {
                    continue;
                }
                else
                {
                    std::cout << "Bad input, incorrect arguments given" << std::endl;
                    throw std::exception{};
                }
            }
        }
        else
        {
            std::cout << "Bad input, incorrect command given" << std::endl;
            throw std::exception{};
        }
    }
    catch (const std::exception &e)
    {
        //
    }
    return commands;
}

void AdvisorBot::handleUserOptions(OrderBook orderBook, std::string currentTime, std::vector<std::string> userOption)
{
    // Call different constructor methods based on size of input from user
    if (userOption.size() == 1)
    {
        std::string cmd = userOption[0];
        Command command(orderBook, currentTime, cmd);
        command.invoke();
    }

    if (userOption.size() == 2)
    {
        std::string cmd = userOption[0];
        std::string arg1 = userOption[1];
        Command command(orderBook, currentTime, cmd, arg1);
        command.invoke();
    }

    if (userOption.size() == 3)
    {
        std::string cmd = userOption[0];
        std::string arg1 = userOption[1];
        std::string order = userOption[2];
        OrderBookType arg2 = OrderBookEntry::stringToOrderBookType(userOption[2]);
        Command command(orderBook, currentTime, cmd, arg1, arg2, order);
        command.invoke();
    }

    if (userOption.size() == 4)
    {
        std::string cmd = userOption[0];
        std::string arg1 = userOption[1];
        std::string order = userOption[2];
        OrderBookType arg2 = OrderBookEntry::stringToOrderBookType(userOption[2]);
        std::string arg3 = userOption[3];
        Command command(orderBook, currentTime, cmd, arg1, arg2, order, arg3);
        command.invoke();
    }
}