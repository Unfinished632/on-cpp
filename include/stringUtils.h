#pragma once

#include <iostream>
#include "stringUtils.h"

namespace String
{
    int CountLines(std::string string);
    struct SwitchStr
    {
        std::string string;
        int value;

        SwitchStr(std::string string, int value);
    };
}