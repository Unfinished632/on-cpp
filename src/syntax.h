#pragma once

#include <iostream>
#include <list>
#include <vector>

enum Instruction
{
    Print,
    Wait
};

enum SyntaxError
{
    NoSemicolon,
    UndefinedInstruction,
    TooManyArguments,
    TooFewArguments,
    WrongType
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
    void* values;
};

std::list<struct Token> Lexer(std::string code);
std::vector<Statement> Parse(std::list<struct Token> tokens);