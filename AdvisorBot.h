#pragma once

#include <string>

class AdvisorBot
{
public:
    // constructor
    AdvisorBot();
    void init();

private:
    void commandPrompt();
    std::string getUserOption();
    void processUserOptions(std::string userOption);
};