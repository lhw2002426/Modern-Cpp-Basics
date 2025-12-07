#include<bits/stdc++.h>
class A {
public:
    virtual ~A() = default;
};
/*
当没有虚析构函数时A 不是多态类型（non-polymorphic），因为类里没有任何 virtual 函数。

标准规定：
对于非多态类型，当通过引用使用 typeid(a) 时，得到的是静态类型（static type），而不是实际对象类型。

静态类型 = 编译器认为它是什么类型（这里是 A&）
*/

/*
当有虚析构函数时A 成为 多态类型（polymorphic type）

对多态类型的引用/指针使用 typeid 时：

会返回运行时动态类型（dynamic type）
*/
class B : public A { };

void OutputType(A& a)
{
    std::printf("%s", typeid(a).name());
}

B b;
int main()
{   
    OutputType(b);
}