#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include <vector>
#include "syntax.h"


Statement ParseIntoStatement(std::vector<Token> tokens);
Statement ParsePrint(std::vector<Token> tokens);
Statement ParsePrintLine(std::vector<Token> tokens);

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

        if (!arg.empty())
        if (arg.back() == '\n')
        {
            arg.pop_back();
            collumn = 0;
            line++;
        }

        token.collumn = collumn;
        token.line = line;

        if (!arg.empty())
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

std::vector<Statement> Parse(std::list<struct Token> tokens)
{
    std::vector<Statement> ast;
    std::vector<Token> statement;

    for (Token i : tokens)
    {
        if (i.value == ";")
        {
            ast.push_back(ParseIntoStatement(statement));
            statement.clear();
            continue;
        }

        statement.push_back(i);
    }

    return ast;
}

Statement ParseIntoStatement(std::vector<Token> tokens)
{
    if (tokens.at(1).value == ":")
    {
        if (tokens.at(0).value == "Print")
            return ParsePrint(tokens);
        else if (tokens.at(0).value == "Println")
            return ParsePrintLine(tokens);
    }

    Statement error;
    error.instruction = Instruction::SyntaxError;

    return error;
}

Statement ParsePrint(std::vector<Token> tokens)
{
    Statement statement;
    statement.instruction = Instruction::Print;

    tokens.erase(tokens.begin(), tokens.begin() + 2);

    if (tokens.front().value == "\"" && tokens.back().value == "\"")
    {
        tokens.erase(tokens.begin());
        tokens.erase(tokens.begin() + tokens.size());

        for (char i : tokens.front().value)
        {
            statement.values.push_back(i);
        }

        return statement;
    }

    Statement error;
    error.instruction = Instruction::SyntaxError;
    return error;
}

Statement ParsePrintLine(std::vector<Token> tokens)
{
    Statement statement;
    statement.instruction = Instruction::Print;

    tokens.erase(tokens.begin(), tokens.begin() + 2);

    if (tokens.empty())
    {
        statement.values.push_back('\n');

        return statement;
    }
    else if (tokens.front().value == "\"" && tokens.back().value == "\"")
    {
        tokens.erase(tokens.begin());
        tokens.erase(tokens.begin() + tokens.size());

        for (char i : tokens.front().value)
        {
            statement.values.push_back(i);
        }

        statement.values.push_back('\n');

        return statement;
    }

    Statement error;
    error.instruction = Instruction::SyntaxError;
    return error;
}

DataType ParseDataType(std::string token)
{
    if (token == "Int")
        return DataType::Int;
    else if (token == "Double")
        return DataType::Double;
    else if (token == "Float")
        return DataType::Float;
    else if (token == "Bool")
        return DataType::Bool;
    else if (token == "String")
        return DataType::String;
    else
        return DataType::Error;
}