#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include <vector>
#include <string.h>
#include "syntax.h"
#include "interpreter.h"

Exception InterpretPrint(std::vector<int> values);
Exception InterpretPrintLine(std::vector<int> values);

Exception Interpret(std::vector<Statement> statements)
{
    for (Statement i : statements)
    {
        switch (i.instruction)
        {
        case Instruction::Print:
            InterpretPrint(i.values);
            break;
        default:
            return Exception::UnknownInstruction;
            break;
        }
    }

    return Exception::Good;
}

Exception InterpretPrint(std::vector<int> values)
{
    for (char i : values)
    {
        std::cout << i;
    }

    return Exception::Good;
}

