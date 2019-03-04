#include "Common.hpp"

std::string Common::indentString(std::string theString)
{
    std::string tempString = theString;
    tempString.insert(0, "");
    for(int i = 0; i < tempString.length(); i++)
    {
        if(theString[i] == '\n')
        {
            tempString.insert(i + 5, "    ");
        }
    }
    tempString.insert(0, "\n    ");
    return tempString;
}