#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include <vector>
#include "../include/syntax.h"

//std::vector<Statement> Parse(std::list<std::string> tokens);

std::list<struct Token> Lexer(std::string code)
{
    std::list<struct Token> tokens;
    std::string arg = "";

    //Lexing
    bool allowSpaces = false;
    struct Token token;
    int collumn = 0;
    int line = 1;
    
    for (int i = 0; i < code.length(); i++)
    {
        arg += code[i];

        collumn++;

        if (arg.back() == '\n')
        {
            arg.pop_back();
            collumn = 0;
            line++;
        }

        token.collumn = collumn;
        token.line = line;

        if (arg.back() == ' ' && !allowSpaces)
        {
            arg.pop_back();
            token.value = arg;

            if (arg != "")
                tokens.push_back(token);
            arg = "";
        }
        else if (arg.back() == '"')
        {
            allowSpaces = !allowSpaces;

            if (allowSpaces)
            {
                token.value = "\"";
                tokens.push_back(token);
            }
            else
            {
                arg.pop_back();

                token.value = arg;
                token.collumn = collumn - arg.length();
                tokens.push_back(token);

                token.value = "\"";
                token.collumn = collumn;
                tokens.push_back(token);
            }
            
            arg = "";
        }

        else if (i + 1 >= code.length())
        {
            token.value = arg;

            token.collumn = (collumn - arg.length()) + 1;

            tokens.push_back(token);
            arg = "";
        }
        
        else
        {
            switch (arg.back())
            {
                case ';':
                    arg.pop_back();

                    if (arg != "")
                    {
                        token.value = arg;
                        token.collumn = collumn - arg.length();
                        tokens.push_back(token);
                    }

                    token.value = ";";
                    token.collumn = collumn;
                    tokens.push_back(token);
                    arg = "";
                    break;
                case ':':
                    arg.pop_back();
                    
                    if (arg != "")
                    {
                        token.value = arg;
                        token.collumn = collumn - arg.length();
                        tokens.push_back(token);
                    }

                    token.value = ":";
                    token.collumn = collumn;
                    tokens.push_back(token);
                    arg = "";
                    break;
                case ',':
                    arg.pop_back();
                    
                    if (arg != "")
                    {
                        token.value = arg;
                        token.collumn = collumn - arg.length();
                        tokens.push_back(token);
                    }

                    token.value = ",";
                    token.collumn = collumn;
                    tokens.push_back(token);
                    arg = "";
                    break;
            }
        }
    }

    return tokens;
}

/*
std::vector<Statement> Parse(std::list<std::string> tokens)
{
    std::vector<Statement> ast;

    for (std::string i : tokens)
    {
        Statement statement;
        
    }
}
*/