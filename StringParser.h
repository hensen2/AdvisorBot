#pragma once

#include <vector>
#include <string>

class StringParser
{
public:
    StringParser();
    // StringParser(std::string userOption, char userSeparator);
    static std::vector<std::string> tokeniseCmds(std::string userOption, char separator);
    static std::string trimInput(std::string userOption, char separator);
};