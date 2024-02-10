#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include "parser.cpp"

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

    std::ostringstream buffer;
    buffer << script.rdbuf();

    //Lex
    std::string code = buffer.str();

    std::list<std::string> tokens = Lex(code);

    for (std::string i : tokens)
        std::cout << i + '\n';
}