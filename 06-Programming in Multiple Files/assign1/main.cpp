#include "animal.hpp"
#include "animal_interface_impl.hpp"  // 包含模板实现
#include <cstdio>
#include <string>

void Test(AnimalInterface animal)
{
    animal.Walk();
    std::string talkResult = animal.Talk(1);
    printf("%s\n", talkResult.c_str());
}

int main()
{
    Dog dog;
    Cat cat;
    
    Test(dog);
    Test(cat);
    
    return 0;
}