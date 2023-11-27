#include "TextEntry.h"





TextEntry::Type TextEntry::matchServCommand(std::string_view servCmdTxt)
{
    try
    {
        return servCommandIDs.at(std::string(servCmdTxt));
    }
    catch (std::out_of_range& ex)
    {
        return Type::SC_UNRECOGNIZED;
    }
}


TextEntry::TypeTextPair TextEntry::extract(std::string_view entryView)
{
    TypeTextPair ttPair;

    // clip front whitespace, test if first char is the server command identifier ('/')
    size_t firstCharPos = entryView.find_first_not_of(' ');
    char firstChar = (firstCharPos == std::string_view::npos) ? entryView[0] : entryView[firstCharPos];

    if (firstChar == SERV_COMMAND_CHAR)
    {
        size_t servCmdStart = firstCharPos + 1;
        size_t servCmdEnd = entryView.find(' ', servCmdStart);

        std::string_view servCmdToken = entryView.substr(servCmdStart, servCmdEnd - servCmdStart); // extract the command text

        size_t restOfTxtStart = entryView.find_first_not_of(' ', servCmdEnd);
        size_t restOfTxtEnd = entryView.find_last_not_of(' ') + 1;

        std::string_view restOfText = entryView.substr(restOfTxtStart, restOfTxtEnd - restOfTxtStart); // extract the rest of the text with end whitespace clipped

        ttPair.type = matchServCommand(servCmdToken);
        ttPair.text = restOfText;
    }

    else
    {
        std::string_view entireText = entryView.substr(firstCharPos, entryView.find_last_not_of(' ') - firstCharPos + 1); // get all text with end whitespace clipped

        ttPair.type = Type::MESSAGE;
        ttPair.text = entireText;
    }

    return ttPair;
}
