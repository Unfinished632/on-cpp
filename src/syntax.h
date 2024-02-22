#pragma once

#include <iostream>
#include <list>
#include <vector>

enum Instruction
{
    SyntaxError,
    Print,
    CreateVariable
};

enum DataType
{
    Error,
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
std::vector<Statement> Parse(std::list<struct Token> tokens);