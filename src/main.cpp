#include <iostream>
#include <fstream>
#include <sstream>

const std::string parserPath = "prs";

void Parser(std::string filePath);

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        std::cout << "On version 0.1";
    }
    else if (argc == 2)
    {
        Parser(argv[1]);
    }

    return 0;
}

void Parser(std::string filePath)
{
    std::ifstream script;
    script.open(filePath);
    
    std::fstream parsedScript;
    parsedScript.open(parserPath);

    std::ostringstream buffer;
    buffer << script.rdbuf();


    std::string code = buffer.str();

    std::cout << code;
}