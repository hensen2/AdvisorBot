#include "StringParser.h"
#include <iostream>

StringParser::StringParser() = default;

std::vector<std::string> StringParser::tokeniseCommands(std::string userOption, char separator)
{
    std::vector<std::string> commands;
    size_t start = 0;
    size_t end = userOption.find(separator);

    if (end == std::string::npos)
    {
        commands.push_back(userOption);
        return commands;
    }

    while (end != std::string::npos)
    {
        commands.push_back(userOption.substr(start, end - start));
        start = end + 1;
        if (userOption.find(separator, start) == std::string::npos)
        {
            commands.push_back(userOption.substr(start, userOption.size() - 1));
        }
        end = userOption.find(separator, start);
    }
    return commands;
}