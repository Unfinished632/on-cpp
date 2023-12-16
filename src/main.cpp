//x86_64-w64-mingw32-g++ src/main.cpp -o On.exe

#include <iostream>
#include <fstream>
#include "../include/exceptions.h"
#include "../include/types.h"
#define string std::string

std::ifstream cex;

const int MAXCHAR = 100;

const int MAX_INT_HEAP = 50;
const int MAX_STR_HEAP = 20;
const int MAX_DOUB_HEAP = 20;
const int MAX_FLOA_HEAP = 20;

string IntVarNames[MAX_INT_HEAP];
string StrVarNames[MAX_STR_HEAP];
string DoubVarNames[MAX_DOUB_HEAP];
string FloaVarNames[MAX_FLOA_HEAP];

int *IntHeap[MAX_INT_HEAP];
string *StrHeap[MAX_STR_HEAP];
double *DoubHeap[MAX_DOUB_HEAP];
float *FloaHeap[MAX_FLOA_HEAP];

char line[MAXCHAR];

int row = 0;

void Read();
void Print();
void ThrowException(Exception exception, int line);
void CreateVar(Types type, string name);
void CreateVar(Types type, string name, string value);

int main()
{   
    Read();

    std::cin.get();

    return 0;
}

void Read()
{
    string path;
    std::cin >> path;
    cex.open(path);

    while (true)
    {
        cex.getline(line, MAXCHAR);
        int size = sizeof(line) / sizeof(line[0]);
        string arg;
        int lastLine = 0;

        if (line[0] == ' ')
            continue;

        for (; lastLine < size; lastLine++)
        {
            if (line[lastLine] == ' ')
            {
                lastLine++;
                break;
            }

            arg += line[lastLine];
        }

        if (arg == "Off;")
        {
            return;
        }
        else if (arg == "Print:" || arg == "Println:")
        {
            Types type;
            string arg2;

            if (line[lastLine] == '"')
                type = Types::String;
            else
            {
                ThrowException(Exception::IncorrectType, lastLine);
                return;
            }
            
            lastLine++;

            for (; lastLine < size; lastLine++)
            {
                if (line[lastLine] == '"' && line[lastLine + 1] == ';')
                {
                    break;
                }

                arg2 += line[lastLine];
            }

            std::cout << arg2;
            if (arg == "Println:")
                std::cout << '\n';
        }

        else if (arg == "NewVar:")
        {
            Types type;
            string arg2;
            string name;
            string value;

            for (; lastLine < size; lastLine++)
            {
                if (line[lastLine] = ' ')
                {
                    lastLine++;
                    break;
                }

                arg2 += line[lastLine];
            }

            if (arg2 == "Int")
                type == Types::Int;
            else if (arg2 == "String")
                type == Types::String;
            else if (arg2 == "Float")
                type == Types::Float;
            else if (arg2 == "Double")
                type == Types::Double;
            else if (arg2 == "Bool")
                type == Types::Bool;
            else
            {
                ThrowException(Exception::UnidentifiedType, lastLine);
                return;
            }

            if (line[lastLine] != ' ')
            {
                for (; lastLine < size; lastLine++)
                {
                    if (line[lastLine] = ' ' || line[lastLine == ';'])
                    {
                        lastLine++;
                        break;
                    }

                    name += line[lastLine];
                }

                if (line[lastLine - 1] = ';')
                {
                    CreateVar(type, name);
                }
                else if (line[lastLine] = '=')
                {
                    for (; lastLine < size; lastLine++)
                    {
                        if (line[lastLine] == '"' && line[lastLine + 1] == ';')
                        {
                            if (type != Types::String)
                            {
                                ThrowException(Exception::IncorrectType, lastLine);
                                return;
                            }

                            CreateVar(type, name, value);
                            break;
                        }
                        else if (line[lastLine + 1] == ';')
                        {
                            CreateVar(type, name, value);
                            break;
                        }

                        value += line[lastLine];
                    }
                }
            }
            else
            {
                ThrowException(Exception::VariableNameExpected, lastLine);
                return;
            }

        }

        row++;
    }
}

void ThrowException(Exception exception, int line)
{
    switch (exception)
    {
    case Exception::UnexpectedSpace:
        std::cout << "\nUnexpectedSpaceException";
        break;
    case Exception::IncorrectType:
        std::cout << "\nIncorrectTypeException";
    case Exception::WrongNotation:
        std::cout << "\nWrongNotationException";
    case Exception::MissingSemicolon:
        std::cout << "\nMissingSemicolonException";
    case Exception::UnidentifiedType:
        std::cout << "\nUnidentifiedTypeException";
    }

    std::cout << " on line:" << line << " row:" << row;
}