#include "StringParser.h"
#include <iostream>

// StringParser::StringParser(std::string userOption, char userSeparator)
// {
//     separator = userSeparator;
//     commands = StringParser::tokeniseCmds(userOption, separator);
// }
StringParser::StringParser() = default;

std::string StringParser::trimInput(std::string userOption, char separator)
{
    std::string trimmedOption{};
    short start = userOption.find_first_not_of(separator, 0);
    short end = userOption.find_last_not_of(' ');
    if (start != std::string::npos && end != std::string::npos)
    {
        trimmedOption = userOption.substr(start, end - start + 1);
    }
    return trimmedOption;
}

std::vector<std::string> StringParser::tokeniseCmds(std::string userOption, char separator)
{
    std::string trimStr = trimInput(userOption, separator);

    std::vector<std::string> commands;
    short start = 0;
    short end = trimStr.find_first_of(separator, start);

    if (end == std::string::npos)
    {
        commands.push_back(trimStr.substr(0, trimStr.length()));
        return commands;
    }

    while (end != std::string::npos)
    {
        commands.push_back(trimStr.substr(start, end - start));
        start = trimStr.find_first_not_of(separator, end);
        end = trimStr.find_first_of(separator, start);
        if (end == std::string::npos)
        {
            commands.push_back(trimStr.substr(start, trimStr.length()));
        }
    }
    return commands;
}