#include<bits/stdc++.h>
#include<any>
class AnimalInterface
{
public:
// 1. 写一个模板构造函数，它接受任意对象，用以构造hiddenObject
//2. 请在构造函数里写一个lambda表达式，它对hiddenObject做any_cast，变换回原本的类型，再调用Walk。
    template<typename T>
    AnimalInterface(const T &object) : hiddenObject_{ object }
    {
        walkProxy_ = [](std::any &object) {
            std::any_cast<T &>(object).Walk();
        };
        talkProxy_ = [](std::any &object, int times) {
            return std::any_cast<T &>(object).Talk(times);
        };
    }
    void Walk() { walkProxy_(hiddenObject_); }
    std::string Talk(int times) { return talkProxy_(hiddenObject_, times); }
private:
    std::any hiddenObject_;
    void (*walkProxy_)(std::any &);
    std::string (*talkProxy_)(std::any &, int);
};
class Dog { 
    //实现上面两个函数;
public:
    std::string Talk(int times) {
        std::string result;
        for (int i = 0; i < times; ++i) {
            result += "Woof! ";
        }
        return result;
    }
    void Walk() {
        std::printf("The dog is walking.\n");
    }
};
class Cat {
    //实现上面两个函数;
public:
    std::string Talk(int times) {
        std::string result;
        for (int i = 0; i < times; ++i) {
            result += "Meow! ";
        }
        return result;
    }
    void Walk() {
        std::printf("The cat is walking.\n");
    }
};

void Test(const AnimalInterface& animal)
{
    animal.Walk();
    std::printf("%s\n", animal.Talk(1));
}

int main()
{
    //不想通过继承来实现下面的内容
    Test(Dog{});
    Test(Cat{});
    return 0;
}