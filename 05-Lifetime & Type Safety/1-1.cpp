#include <iostream>
#include <cassert>

void SetValue(void* dst)
{
    // 将dst视为int指针，如果dst原来是float，这是UB行为
    int* m = (int*)dst;
    for(int i = 0; i < 4; i++)
        m[i] = i;
    return;
}

int main()
{
    assert(sizeof(int) == sizeof(float) && alignof(int) == alignof(float));
    
    float a[4]{};
    SetValue(a);
    for(int i = 0; i < 4; i++)
        std::cout << a[i] << ' ';
    return 0;
}

/*

lhw@thinkbooklhw:~/c++/Modern-Cpp-Basics/05-Lifetime & Type Safety$ g++ 1-1.cpp -o 1-1 -std=gnu++23 
lhw@thinkbooklhw:~/c++/Modern-Cpp-Basics/05-Lifetime & Type Safety$ ./1-1
0 1.4013e-45 2.8026e-45 4.2039e-45 
lhw@thinkbooklhw:~/c++/Modern-Cpp-Basics/05-Lifetime & Type Safety$ g++ 1-1.cpp -o 1-1 -std=gnu++23 -O
lhw@thinkbooklhw:~/c++/Modern-Cpp-Basics/05-Lifetime & Type Safety$ ./1-1
0 1.4013e-45 2.8026e-45 4.2039e-45 
lhw@thinkbooklhw:~/c++/Modern-Cpp-Basics/05-Lifetime & Type Safety$ g++ 1-1.cpp -o 1-1 -std=gnu++23 -O2
lhw@thinkbooklhw:~/c++/Modern-Cpp-Basics/05-Lifetime & Type Safety$ ./1-1
0 0 0 0

在典型的 gcc + x86 + IEEE754 下：

a[0] 的比特是 0 → float 也是 0.0

a[1] 的比特是 0x00000001 → 超级小的非正规数 ≈ 1.4e-45

a[2] ≈ 2.8e-45

a[3] ≈ 4.2e-45

所以在 -O0（不开优化） 时，gcc 一般会老老实实地从内存读，输出类似：

0 1.4013e-45 2.8026e-45 4.2039e-45

而在 -O2（开启优化） 时，情况完全变了：
因为这里存在 生命周期 / 严格别名规则（strict aliasing）上的 UB，优化器可以假设“通过 int* 不会修改 float 对象”，于是它认为 a 在整个 main 中从未被写过（只有初始化那次），从而把循环直接优化为输出 4 个 0.0：

0 0 0 0


或者其他更奇怪的东西都可以——因为 一旦是 UB，任何结果都是允许的。

生命周期问题的体现：没有初始化int，则作为int的生命周期还没开始
*/