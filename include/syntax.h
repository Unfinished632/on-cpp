#pragma once

#include <iostream>
#include <vector>

enum Instruction
{
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

struct Statement
{
    Instruction instruction;
    int value;
};

struct AST
{
    std::vector<Statement> statements;
};