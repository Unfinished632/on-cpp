#include <iostream>
#include "../include/utils.h"

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