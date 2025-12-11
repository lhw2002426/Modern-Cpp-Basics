#include "animal.hpp"
#include <string>
#include <cstdio>

// Dog 实现
void Dog::Walk() { 
    std::printf("Dog walk...\n"); 
}

std::string Dog::Talk(int times)
{
    std::string result{};
    for (int i = 0; i < times; i++) {
        result += "Woof! ";
    }
    return result;
}

// Cat 实现
void Cat::Walk()  { 
    std::printf("Cat walk...\n");  
}

std::string Cat::Talk(int times)
{
    return "Meow! Lazy to talk for " + std::to_string(times) + " times.";
}

// AnimalInterface 非模板成员函数定义
void AnimalInterface::Walk() { walkProxy_(hiddenObject_); }
std::string AnimalInterface::Talk(int times) { return talkProxy_(hiddenObject_, times); }