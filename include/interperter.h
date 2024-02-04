#pragma once

#include <fstream>
#include "exceptions.h"
#include "definitions.h"
#include "types.h"

namespace All
{
    class On
    {
    public:
        std::ifstream script;

        char line[MAX_CHAR];

        int row;

        void Read();
        void Print();
        int CreateVariable(Types type, string name, int line);
        int CreateVariable(Types type, string name, int line, string value);

        class heapMemory;
        class interperter;
    };

    class Interperter
    {
    public:
        void ThrowException(Exception exception, int line, int row);
    };

    class HeapMemory
    {
    private:
        string IntVarNames[MAX_HEAP];
        string StringVarNames[MAX_HEAP];
        string DoubleVarNames[MAX_HEAP];
        string FloatVarNames[MAX_HEAP];
        string BoolVarNames[MAX_HEAP];

        bool IntVarExists[MAX_HEAP];
        bool StringVarExists[MAX_HEAP];
        bool DoubleVarExists[MAX_HEAP];
        bool FloatVarExists[MAX_HEAP];
        bool BoolVarExists[MAX_HEAP];

        int *IntHeap[MAX_HEAP];
        string *StringHeap[MAX_HEAP];
        double *DoubleHeap[MAX_HEAP];
        float *FloatHeap[MAX_HEAP];
        bool *BoolHeap[MAX_HEAP];

    public:
        int CheckIfVariableNameExists(Interperter &interperter, string name, int line, int row);
        int CheckIfFreeSpaceInHeap(Interperter &interperter, int line, int row);
        int GetBestPositionInHeap();
        void CreateVariable(Types type, string name, int position);
        void CreateVariable(Types type, string name, int position, string value);
    };
}