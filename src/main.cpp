#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include <string.h>
#include "syntax.h"
#include "interpreter.h"
#include "BuildConfig.h"

std::string ReadScript(std::string filePath);
void PrintLexed(std::string code);
void PrintAST(std::string code);
std::string InstructionToString(Instruction instruction);
void RunCode(std::string code);

int main(int argc, char* argv[]){
    if (argc <= 1){
        std::cout << "error: No arguments\n";
        return 0;
    }

    if (!strcmp(argv[1], "--help"))
        std::cout << "Commands:\n" <<
        "   --help => Prints all possible arguments and what they do.\n" <<
        "   --version => Prints the version of the program.\n" <<
        "   <onFilePath> => Interprets the file.\n" <<
        "   -lexed <onFilePath> => Prints the lexed version of the file.\n" <<
        "   -ast <onFilePath> => Prints the AST of the file.\n"; 
    else if (!strcmp(argv[1], "--version"))
        std::cout << "On version " << OnLang_VERSION_MAJOR << '.' << OnLang_VERSION_MINOR << '\n';
    else if (!strcmp(argv[1], "-lexed"))
        PrintLexed(ReadScript(argv[2]));
    else if (!strcmp(argv[1], "-ast"))
        PrintAST(ReadScript(argv[2]));
    else
        RunCode(ReadScript(argv[1]));

    return 0;
}

std::string ReadScript(std::string filePath){
    //Read Script
    std::ifstream script;
    script.open(filePath);

    if (!script.good()){
        std::cout << "This file doesn't exist dumbass!\n";
        exit(0);
    }

    std::ostringstream buffer;
    buffer << script.rdbuf();

    return buffer.str();;
}

void PrintLexed(std::string code){
    std::list<struct Token> tokens = Lexer(code);

    for (Token i : tokens){
        std::cout << i.value << " line:" << i.line << " collumn:" << i.collumn << '\n';
    }
}

void PrintAST(std::string code){
    std::list<struct Token> tokens = Lexer(code);
    std::vector<Statement> ast = Parse(tokens);

    for (Statement i : ast){
        std::cout << InstructionToString(i.instruction) << " => ";

        switch (i.instruction){
            case Instruction::Print:
                std::cout << *(std::string*)i.values;
                break;
            case Instruction::Wait:
                std::cout << *(unsigned int*)i.values;
                break;
        }
        
        std::cout << '\n';
    }
}

std::string InstructionToString(Instruction instruction){
    switch (instruction){
        case Instruction::Print:
            return "Print";
        case Instruction::Wait:
            return "Wait";
        default:
            return "Undefined";
    }
}

void RunCode(std::string code){
    std::list<struct Token> tokens = Lexer(code);
    std::vector<Statement> ast = Parse(tokens);

    Interpret(ast);
}