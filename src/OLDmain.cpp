//g++ src/main.cpp src/Interperter.cpp -o On.exe

#include <iostream>
#include <fstream>
#include "../include/exceptions.h"
#include "../include/types.h"
#include "../include/definitions.h"
#include "../include/interperter.h"

int main()
{   
    On on;

    on.Read();

    std::cin.get();

    return 0;
}

class On
{
    public:
        std::ifstream script;

        char line[MAX_CHAR];

        int row = 0;

        void Read();
        void Print();
        int CreateVariable(Types type, string name, int line);
        int CreateVariable(Types type, string name, int line, string value);

        All::HeapMemory heapMemory;
        All::Interperter interperter;

        int CreateVariable(Types type, string name, int line)
        {
            if (heapMemory.CheckIfVariableNameExists(interperter, name ,line, row) != 0)
                return 1;

            int position;

            if (heapMemory.CheckIfFreeSpaceInHeap(interperter, line, row) != 0)
                return 1;

            position = heapMemory.GetBestPositionInHeap();

            heapMemory.CreateVariable(type, name, position);

            return 0;
        }
        int CreateVariable(Types type, string name, int line, string value)
        {
            if (heapMemory.CheckIfVariableNameExists(interperter, name, line, row) != 0)
                return 1;

            int position;

            if (heapMemory.CheckIfFreeSpaceInHeap(interperter, line, row) != 0)
                return 1;

            position = heapMemory.GetBestPositionInHeap();

            heapMemory.CreateVariable(type, name, position, value);

            return 0;
        }

        void Read()
        {
            string path;
            std::cin >> path;
            script.open(path);

            while (true)
            {
                script.getline(line, MAX_CHAR);
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
                        interperter.ThrowException(Exception::IncorrectType, lastLine, row);
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
                        interperter.ThrowException(Exception::UnidentifiedType, lastLine, row);
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
                            if (CreateVariable(type, name, lastLine) != 0)
                                return;
                        }
                        else if (line[lastLine] = '=')
                        {
                            for (; lastLine < size; lastLine++)
                            {
                                if (line[lastLine] == '"' && line[lastLine + 1] == ';')
                                {
                                    if (type != Types::String)
                                    {
                                        interperter.ThrowException(Exception::IncorrectType, lastLine, row);
                                        return;
                                    }

                                    if (CreateVariable(type, name, lastLine, value) != 0)
                                        return;
                                    break;
                                }
                                else if (line[lastLine + 1] == ';')
                                {
                                    if (CreateVariable(type, name, lastLine, value) != 0)
                                        return;
                                    break;
                                }
                                else
                                {
                                    interperter.ThrowException(Exception::MissingSemicolon, lastLine, row);
                                    return;
                                }

                                value += line[lastLine];
                            }
                        }
                        else
                        {
                            interperter.ThrowException(Exception::UnidentifiedOrWrongOperator, lastLine, row);
                        }
                    }
                    else
                    {
                        interperter.ThrowException(Exception::VariableNameExpected, lastLine, row);
                        return;
                    }
                }

                row++;
            }
        }
};