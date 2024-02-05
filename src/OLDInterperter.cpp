#include <iostream>
#include "../include/definitions.h"
#include "../include/interperter.h"
#include "../include/exceptions.h"
#include "../include/types.h"

void All::Interperter::ThrowException(Exception exception, int line, int row)
{
    switch (exception)
    {
    case Exception::UnexpectedSpace:
        std::cout << "\nUnexpectedSpaceException";
        break;
    case Exception::IncorrectType:
        std::cout << "\nIncorrectTypeException";
        break;
    case Exception::WrongNotation:
        std::cout << "\nWrongNotationException";
        break;
    case Exception::MissingSemicolon:
        std::cout << "\nMissingSemicolonException";
        break;
    case Exception::UnidentifiedType:
        std::cout << "\nUnidentifiedTypeException";
        break;
    case Exception::ExpectedEqualSign:
        std::cout << "\nExpectedEqualSignException";
        break;
    case Exception::VariableNameExpected:
        std::cout << "\nVariableNameExpectedException";
        break;
    case Exception::UnidentifiedOrWrongOperator:
        std::cout << "\nUnidentifiedOrWrongOperatorException";
        break;
    case Exception::VariableNameAlreadyExists:
        std::cout << "\nVariableNameAlreadyExistsException";
        break;
    case Exception::MaxedHeap:
        std::cout << "\nMaxedHeapException";
        break;
    }

    std::cout << " on line:" << line << " row:" << row;
}

int All::HeapMemory::CheckIfVariableNameExists(Interperter &interperter, string name, int line, int row)
{
    for (int i = 0; i < MAX_HEAP; i++)
    {
        if (IntVarNames[i] == name)
        {
            interperter.ThrowException(Exception::VariableNameAlreadyExists, line, row);
            return 1;
        }
        else if (StringVarNames[i] == name)
        {
            interperter.ThrowException(Exception::VariableNameAlreadyExists, line, row);
            return 1;
        }
        else if (DoubleVarNames[i] == name)
        {
            interperter.ThrowException(Exception::VariableNameAlreadyExists, line, row);
            return 1;
        }
        else if (FloatVarNames[i] == name)
        {
            interperter.ThrowException(Exception::VariableNameAlreadyExists, line, row);
            return 1;
        }
        else if (BoolVarNames[i] == name)
        {
            interperter.ThrowException(Exception::VariableNameAlreadyExists, line, row);
            return 1;
        }
    }

    return 0;
}

int All::HeapMemory::CheckIfFreeSpaceInHeap(Interperter &interperter, int line, int row)
{
    for (int i = 0; i < MAX_HEAP; i++)
    {
        if (!IntVarExists[i])
        {
            return 0;
            break;
        }
        else if (!StringVarExists[i])
        {
            return 0;
            break;
        }
        else if (!DoubleVarExists[i])
        {
            return 0;
            break;
        }
        else if (!FloatVarExists[i])
        {
            return 0;
            break;
        }
        else if (!BoolVarExists[i])
        {
            return 0;
            break;
        }
        else
        {
            interperter.ThrowException(Exception::MaxedHeap, line, row);
            return 1;
        }
    }
}

int All::HeapMemory::GetBestPositionInHeap()
{
    for (int i = 0; i < MAX_HEAP; i++)
    {
        if (!IntVarExists[i])
        {
            return i;
            break;
        }
        else if (!StringVarExists[i])
        {
            return i;
            break;
        }
        else if (!DoubleVarExists[i])
        {
            return i;
            break;
        }
        else if (!FloatVarExists[i])
        {
            return i;
            break;
        }
        else if (!BoolVarExists[i])
        {
            return i;
            break;
        }
    }
}

void All::HeapMemory::CreateVariable(Types type, string name, int position)
{
    switch (type)
    {
    case Types::Int:
        IntHeap[position] = new int;
        IntVarNames[position] = name;
        IntVarExists[position] = true;
        break;
    case Types::String:
        StringHeap[position] = new string;
        StringVarNames[position] = name;
        StringVarExists[position] = true;
        break;
    case Types::Double:
        DoubleHeap[position] = new double;
        DoubleVarNames[position] = name;
        DoubleVarExists[position] = true;
        break;
    case Types::Float:
        FloatHeap[position] = new float;
        FloatVarNames[position] = name;
        FloatVarExists[position] = true;
        break;
    case Types::Bool:
        BoolHeap[position] = new bool;
        BoolVarNames[position] = name;
        BoolVarExists[position] = true;
        break;
    }
}
void All::HeapMemory::CreateVariable(Types type, string name, int position, string value)
{
    int newValue;

    switch (type)
    {
    case Types::Int:
        newValue = std::stoi(value);

        IntHeap[position] = new int;
        *IntHeap[position] = newValue;
        IntVarNames[position] = name;
        IntVarExists[position] = true;
        break;
    case Types::String:
        StringHeap[position] = new string;
        StringVarNames[position] = name;
        StringVarExists[position] = true;
        break;
    case Types::Double:
        DoubleHeap[position] = new double;
        DoubleVarNames[position] = name;
        DoubleVarExists[position] = true;
        break;
    case Types::Float:
        FloatHeap[position] = new float;
        FloatVarNames[position] = name;
        FloatVarExists[position] = true;
        break;
    case Types::Bool:
        BoolHeap[position] = new bool;
        BoolVarNames[position] = name;
        BoolVarExists[position] = true;
        break;
    }
}