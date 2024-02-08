#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>

void ReadScript(std::string filePath);
std::list<std::string> Lex(std::string code);

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
    {
        std::cout << i + '\n';
    }
}

//Returns number of commands.
std::list<std::string> Lex(std::string code)
{
    std::string arg = "";

    std::list<std::string> tokens[1];

    for (int i = 0; i < code.length(); i++)
    {
        arg += code[i];

        if (arg.back() == ' ')
        {
            arg.pop_back();
            tokens->push_back(arg);
            arg = "";
        }
        else if (i + 1 >= code.length())
        {
            tokens->push_back(arg);
            arg = "";
        }
    }

    return *tokens;
}