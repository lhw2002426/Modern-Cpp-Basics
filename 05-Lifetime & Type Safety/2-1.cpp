#include<bits/stdc++.h>
struct A { int a; };
struct B { int b; };
struct C : A, B { int ddd; };//C不是standard layout
C c;

int main()
{
    A* aPtr = &c;
    bool test = (aPtr == &c);// false类型不一样 答案：true一样，因为发生了隐式转换
    bool test2 = (static_cast<C*>(aPtr) == &c); //true static可以转子类
    bool test3 = (reinterpret_cast<C*>(aPtr) == &c);// true相当于基类中转  答案：不确定 转成`reinterpret_cast<C*>`的结果是地址不变。而`aPtr`和`&c`的地址值未必相同，因此未必返回`true`

    //同上
    B* bPtr = &c;
    bool test4 = (bPtr == &c);
    bool test5 = (static_cast<C*>(bPtr) == &c);
    bool test6 = (reinterpret_cast<C*>(bPtr) == &c);
    //如果把`A`和`B`的成员都去掉，那么`C`就满足standard layout，因此得到的结果就是`&c`，此时确定地得到true。
}