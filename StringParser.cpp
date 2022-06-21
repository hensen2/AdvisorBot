#include "StringParser.h"
#include <iostream>

StringParser::StringParser() = default;

std::vector<std::string> StringParser::tokeniseCommands(std::string userOption, char separator)
{
    std::vector<std::string> commands;
    short start = userOption.find_first_not_of(separator, 0);
    short end = userOption.find_first_of(separator, start);

    if (end == std::string::npos)
    {
        commands.push_back(userOption.substr(start, userOption.length()));
        return commands;
    }

    while (end != std::string::npos) // end <= userOption.length()
    {
        if (userOption.find_first_not_of(separator, end) == std::string::npos)
        {
            std::cout << "No trailing spaces allowed" << std::endl;
            return commands;
        }
        commands.push_back(userOption.substr(start, end - start));
        start = userOption.find_first_not_of(separator, end);
        end = userOption.find_first_of(separator, start);
        if (end == std::string::npos)
        {
            commands.push_back(userOption.substr(start, userOption.length()));
        }
    }
    return commands;
}