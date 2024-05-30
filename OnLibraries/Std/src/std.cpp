#include "../include/std.h"
#include <iostream>
#include <thread>
#include <chrono>

bool Print(char* text){
    std::cout << text;
    return true;
}

bool Println(char* text){
    std::cout << text << '\n';
    return true;
}

bool Wait(unsigned int* milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(*milliseconds));
    return true;
}