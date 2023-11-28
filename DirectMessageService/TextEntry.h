#pragma once
#include <iostream>
#include <string_view>
#include <unordered_map>

// CLIENT-SIDE
namespace TextEntry
{
    const char SERV_COMMAND_CHAR = '/';

    enum Type
    {
        MESSAGE,
        SC_NEW_CHANNEL,
        SC_LIST_USERS,
        SC_UNRECOGNIZED
    };

    struct TypeTextPair
    {
        TextEntry::Type type;
        std::string_view text;
    };

    const std::unordered_map<std::string, TextEntry::Type> servCommandIDs =
    {
        { "talk", Type::SC_NEW_CHANNEL },
        { "list", Type::SC_LIST_USERS }
    };

    TextEntry::Type matchServCommand(std::string_view servCmdTxt);

    TypeTextPair extract(std::string_view entryView);
};



