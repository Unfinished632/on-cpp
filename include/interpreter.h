#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include <vector>
#include <string.h>
#include "../include/syntax.h"

enum Exception
{
    Good,
    UnknownInstruction,
    NullReferenceException
};

Exception Interpret(std::vector<Statement> statements);