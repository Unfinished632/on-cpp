#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include <vector>
#include <string.h>
#include <chrono>
#include <thread>
#include "syntax.h"
#include "interpreter.h"

Exception InterpretPrint(std::string* values);
Exception InterpretWait(unsigned int* values);

Exception Interpret(std::vector<Statement> statements)
{
    for (Statement i : statements)
    {
        switch (i.instruction)
        {
        case Instruction::Print:
            InterpretPrint((std::string*)i.values);
            break;
        case Instruction::Wait:
            InterpretWait((unsigned int*)i.values);
            break;
        default:
            return Exception::UnknownInstruction;
            break;
        }
    }

    for (Statement statement : statements)
    {
        switch (statement.instruction)
        {
            case Instruction::Print:
                delete((std::string*)statement.values);
                break;
            case Instruction::Wait:
                delete((unsigned int*)statement.values);
                break;
        }
    }

    return Exception::Good;
}

Exception InterpretPrint(std::string* values)
{
    std::cout << *values;

    return Exception::Good;
}

Exception InterpretWait(unsigned int* values)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(*values));
    return Exception::Good;
}

