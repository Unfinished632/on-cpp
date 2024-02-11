#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include "../include/syntax.h"

void ReadScript(std::string filePath);

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        std::cout << "On version 0.1" << '\n';
    }
    else if (argc == 2)
    {
        ReadScript(argv[1]);
    }

    return 0;
}

void ReadScript(std::string filePath)
{
    //Read Script
    std::ifstream script;
    script.open(filePath);

    if (!script.good())
    {
        std::cout << "File doesn't exist dumbass!\n";
        return;
    }

    std::ostringstream buffer;
    buffer << script.rdbuf();

    //Lex
    std::string code = buffer.str();

    std::list<struct Token> tokens = Lexer(code);

    for (struct Token i : tokens)
    {
        std::cout << i.value << '\n';
    }
}