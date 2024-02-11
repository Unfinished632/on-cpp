#pragma once

#include <iostream>
#include <list>
#include <vector>

enum Instruction
{
    SynatxError,
    Print,
    CreateVar,
    Wait,
    Crush
};

enum Type
{
    Int,
    Double,
    Float,
    String,
    Bool
};

struct Token
{
    std::string value;
    int line;
    int collumn;
};

struct Statement
{
    Instruction instruction;
    std::vector<int> values;
};

std::list<struct Token> Lexer(std::string code);