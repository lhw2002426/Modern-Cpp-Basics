#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <any>
#include <string>
#include <cstdio>

// 完整的 Dog 和 Cat 类定义
class Dog
{
public:
    void Walk();
    std::string Talk(int times);
};

class Cat
{
public:
    void Walk();
    std::string Talk(int times);
};

// AnimalInterface 类定义
class AnimalInterface
{
public:
    template<typename T>
    AnimalInterface(const T &object);
    
    AnimalInterface(const AnimalInterface&) = default;
    AnimalInterface& operator=(const AnimalInterface&) = default;
    
    void Walk();
    std::string Talk(int times);

private:
    std::any hiddenObject_;
    using WalkFn = void(*)(std::any&);
    using TalkFn = std::string(*)(std::any&, int);

    WalkFn walkProxy_{nullptr};
    TalkFn talkProxy_{nullptr};
};

#endif // ANIMAL_HPP