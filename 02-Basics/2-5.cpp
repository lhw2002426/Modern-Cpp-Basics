#include<bits/stdc++.h>
struct Foo
{
    int foo()
    {
        return this ? 42 : 0;// 正常是0，O2是42
    }
};

int bar()
{
    Foo* fptr = nullptr;
    return fptr->foo();
}
int main()
{
    std::cout<<bar()<<std::endl;
}
/*
✅ 在无优化时

编译器比较“老实”，保留了 return this ? 42 : 0 的判断结果：
this == nullptr → 返回 0

✅ 在 O2 优化下

编译器认为：

成员函数被调用时，this 一定是有效对象
因此 this != nullptr 恒真
⇒ return 42

于是 this ? 42 : 0 变成 return 42，整个条件直接优化掉。
所以不要对空指针操作，这是UB行为
*/