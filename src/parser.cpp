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
Statement ParseWait(std::vector<Token> tokens);
void ThrowError(SyntaxError error, int line, int collumn);
std::string ErrorToString(SyntaxError error);

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

    bool hasSemicolon = false;

    for (Token i : tokens)
    {
        if (i.value == ";")
        {
            hasSemicolon = true;
            ast.push_back(ParseIntoStatement(statement));
            statement.clear();
            continue;
        }

        statement.push_back(i);
    }

    if (!hasSemicolon)
        ThrowError(SyntaxError::NoSemicolon, tokens.back().line, tokens.back().collumn);

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
        else if (tokens.at(0).value == "Wait")
            return ParseWait(tokens);
        else if (tokens.at(0).value == "Var")
            return ParseWait(tokens);
    }

    ThrowError(SyntaxError::UndefinedInstruction, tokens.front().line, tokens.front().collumn);
}

Statement ParsePrint(std::vector<Token> tokens)
{
    Statement statement;
    statement.instruction = Instruction::Print;

    int errorLine = tokens.back().line;
    int errorCollumn = tokens.back().collumn;
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    if (tokens.empty())
        ThrowError(SyntaxError::TooFewArguments, errorLine, errorCollumn);

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

    ThrowError(SyntaxError::WrongType, tokens.back().line, tokens.back().collumn);
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

    ThrowError(SyntaxError::WrongType, tokens.back().line, tokens.back().collumn);
}

Statement ParseWait(std::vector<Token> tokens)
{
    Statement statement;
    statement.instruction = Instruction::Wait;

    int errorLine = tokens.back().line;
    int errorCollumn = tokens.back().collumn;
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    if (tokens.empty())
        ThrowError(SyntaxError::TooFewArguments, errorLine, errorCollumn);

    try
    {
        statement.values.push_back(std::stoi(tokens.back().value));
    }
    catch (std::exception exception)
    {
        ThrowError(SyntaxError::WrongType, tokens.back().line, tokens.back().collumn);
    }

    return statement;
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

std::string ErrorToString(SyntaxError error)
{
    switch (error)
    {
        case 0:
            return "No Semicolon";
        case 1:
            return "Undefined Instruction";
        case 2:
            return "Too Many Arguments";
        case 3:
            return "Too Few Arguments";
        case 4:
            return "Wrong Type";
        default:
            return "Undefined";
    }
}

void ThrowError(SyntaxError error, int line, int collumn)
{
    std::cout << "\n\nSyntax Error: " << ErrorToString(error);
    std::cout << "\n   Line: " << line << " Collumn: " << collumn;
    exit(0);
}