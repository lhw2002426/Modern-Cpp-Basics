#include<bits/stdc++.h>
#include<any>
class AnimalInterface
{
public:
//通过构造函数，来将没有继承关系的类转换成Interface.之后可以通过AnimalInterface来调用它们的Walk和Talk方法，由于可以是任意类型，把传进来的类当做any存进来。所以使用any_cast来还原源类型
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
    using WalkFn = void(*)(std::any &);
    using TalkFn = std::string(*)(std::any &, int);

    WalkFn walkProxy_{};
    TalkFn talkProxy_{};
};
class Dog
{
public:
    void Walk() { std::printf("Dog walk...\n"); }
    std::string Talk(int times)
    {
        std::string result{};
        for (int i = 0; i < times; i++)
            result += "Woof! ";
        return result;
    }
};

class Cat
{
public:
    void Walk()  { std::printf("Cat walk...\n");  }
    std::string Talk(int times)
    {
        return "Meow! Lazy to talk for " + std::to_string(times) + " times.";
    }
};

// 事实上如果我们的Walk和Talk实现为const方法（当然这最好也一并要求Dog和Cat也是const的），这里也可以用const AnimalInterface&。
void Test(AnimalInterface animal)
{
    animal.Walk();
    std::printf("%d\n", animal.Talk(1));
}

int main()
{
    Test(Dog{});
    Test(Cat{});
    return 0;
}