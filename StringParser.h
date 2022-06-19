#pragma once

#include <vector>
#include <string>

class StringParser
{
public:
    StringParser();

    static std::vector<std::string> tokeniseCommands(std::string userOption, char separator);
};