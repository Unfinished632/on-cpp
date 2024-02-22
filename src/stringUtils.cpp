#include <iostream>
#include "stringUtils.h"

int String::CountLines(std::string string)
{
    int lines;

    for (int i = 0; i < string.length(); i++)
    {
        if (string[i] == '\n')
            lines++;
    }

    return lines;
}

struct String::SwitchStr
{
    std::string string;
    int value;

    SwitchStr(std::string string, int value)
    {
        this->string = string;
        this->value = value;
    }
};