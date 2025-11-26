#include <iostream>
#include <set>
class A
{
public:
    A(int init_a) : a{ init_a } { std::printf("Construction: a = %d \n", a); }
    
    // 默认的三路比较运算符和==
    auto operator<=>(const A& other) const = default;
    bool operator==(const A& other) const = default;
    
    // 与int比较的三路比较运算符和== (transparent operators)
    auto operator<=>(int other) const { 
        return a <=> other;
    }
    bool operator==(int other) const {
        return a == other;
    }

private:
    int a;
};

int main()
{
    // 普通set，使用默认比较器
    std::set<A> normalSet{ A{ 1 }, A{ 2 }, A{ 3 } };
    
    // 支持transparent operator的set，使用std::less<> 
    std::set<A, std::less<>> goodSet{ A{ 1 }, A{ 2 }, A{ 3 } };

    std::printf("Begin testing...\n");
    
    std::printf("----For normal set.\n");
    // 这里会构造临时A对象，因为normalSet的比较器需要A类型
    normalSet.find(A{1});
    
    std::printf("----For good set.\n");
    // 这里不会构造临时A对象，因为std::less<>是透明的，可以直接用int比较
    goodSet.find(1);

    return 0;
}