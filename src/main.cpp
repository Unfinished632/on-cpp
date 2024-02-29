#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include <string.h>
#include "syntax.h"
#include "interpreter.h"

std::string ReadScript(std::string filePath);
void PrintLexed(std::string code);
void PrintAST(std::string code);
std::string InstructionToString(Instruction instruction);
void RunCode(std::string code);

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        std::cout << "error: No arguments";
        return 0;
    }

    if (!strcmp(argv[1], "--help"))
        std::cout << "Commands:\n" <<
        "   --help => Prints all possible arguments and what they do.\n" <<
        "   --version => Prints the version of the program.\n" <<
        "   <onFilePath> => Interprets the file.\n" <<
        "   -lexed <onFilePath> => Prints the lexed version of the file.\n" <<
        "   -ast <onFilePath> => Prints the AST of the file.\n"; 
    else if (!strcmp(argv[1], "--version"))
        std::cout << "On version 0.1\n";
    else if (!strcmp(argv[1], "-lexed"))
        PrintLexed(ReadScript(argv[2]));
    else if (!strcmp(argv[1], "-ast"))
        PrintAST(ReadScript(argv[2]));
    else
        RunCode(ReadScript(argv[1]));

    return 0;
}

std::string ReadScript(std::string filePath)
{
    //Read Script
    std::ifstream script;
    script.open(filePath);

    if (!script.good())
    {
        std::cout << "This file doesn't exist dumbass!\n";
        exit(0);
    }

    std::ostringstream buffer;
    buffer << script.rdbuf();

    return buffer.str();;
}

void PrintLexed(std::string code)
{
    std::list<struct Token> tokens = Lexer(code);

    for (Token i : tokens)
    {
        std::cout << i.value << " line:" << i.line << " collumn:" << i.collumn << '\n';
    }
}

void PrintAST(std::string code)
{
    std::list<struct Token> tokens = Lexer(code);
    std::vector<Statement> ast = Parse(tokens);

    for (Statement i : ast)
    {
        std::cout << InstructionToString(i.instruction) << " => ";

        for (int x : i.values)
            std:: cout << x << ' ';
        
        std::cout << '\n';
    }
}

std::string InstructionToString(Instruction instruction)
{
    switch (instruction)
    {
        case 0:
            return "Syntax Error";
        case 1:
            return "Print";
        case 2:
            return "Wait";
        default:
            return "Undefined";
    }
}

void RunCode(std::string code)
{
    std::list<struct Token> tokens = Lexer(code);
    std::vector<Statement> ast = Parse(tokens);

    Interpret(ast);
}