#include "AdvisorBot.h"
#include "StringParser.h"
#include "Command.h"
#include <iostream>
#include <string>

// Tell compiler to create default constructor
AdvisorBot::AdvisorBot() = default;

void AdvisorBot::init()
{
    std::string input;
    commandPrompt();

    while (true)
    {
        input = getUserOption();
        processUserOptions(input);
    }
}

void AdvisorBot::commandPrompt()
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

    std::cout << " max                                     "
              << "find maximum <order> for <product> in current time step" << std::endl;

    std::cout << " avg <product> <order> <timesteps>       "
              << "compute average <order> for the sent <product> over the sent number of <timesteps>" << std::endl;

    std::cout << " predict <max/min> <product> <order>     "
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

std::string AdvisorBot::getUserOption()
{
    // User input
    std::string userOption;
    std::string line;

    // Main menu prompt
    std::cout << "advisorbot$ "
              << "Please enter a valid command, or enter help to list all available commands" << std::endl;

    std::cout << "user$ ";
    std::getline(std::cin, line);
    try
    {
        userOption = line;
        std::cout << "You entered: " << userOption << std::endl;
        std::vector<std::string> commands = StringParser::tokeniseCommands(userOption, ' ');
        for (std::string command : commands)
        {
            std::cout << "Array: " << command << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        //
    }
    return userOption;
}

void AdvisorBot::processUserOptions(std::string userOption)
{
    if (userOption == "help")
    {
        return;
    }
}