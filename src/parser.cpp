#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include "../include/syntax.h"

std::list<std::string> Lex(std::string code);
AST Parse(std::list<std::string> tokens);

std::list<std::string> Lex(std::string code)
{
    std::string arg = "";

    //Filtering new line characters from the code
    std::string filteredCode = "";

    for (char i : code)
    {
        if (i != '\n')
            filteredCode += i;
    }

    code = filteredCode;

    //Lexing
    std::list<std::string> tokens[1];
    bool allowSpaces = false;

    for (int i = 0; i < code.length(); i++)
    {
        arg += code[i];

        if (arg.back() == ' ' && !allowSpaces)
        {
            arg.pop_back();

            if (arg != "")
                tokens->push_back(arg);
            arg = "";
        }
        else if (arg.back() == '"')
        {
            allowSpaces = !allowSpaces;

            if (allowSpaces)
                tokens->push_back("\"");
            else
            {
                arg.pop_back();
                tokens->push_back(arg);
                tokens->push_back("\"");
            }
            
            arg = "";
        }
        else if (arg.back() == ';')
        {
            arg.pop_back();
            if (arg != "")
                tokens->push_back(arg);
            tokens->push_back(";");
            
            arg = "";
        }
        else if (arg.back() == ':')
        {
            arg.pop_back();
            if (arg != "")
                tokens->push_back(arg);
            tokens->push_back(":");
            
            arg = "";
        }
        else if (arg.back() == ',')
        {
            arg.pop_back();
            if (arg != "")
                tokens->push_back(arg);
            tokens->push_back(",");
            
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