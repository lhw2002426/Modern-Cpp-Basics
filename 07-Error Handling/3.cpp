#include<bits/stdc++.h>

// 如果a < b的表达式本身会抛出异常，那么min函数也会抛出异常
template<typename T>
const T& min(const T& a, const T& b) noexcept(noexcept(a < b))
{
    return a < b ? a : b;
}
/*
外层 noexcept(...) 表示：
“如果括号里的表达式在编译期求值为 true，则整个函数被标记为 noexcept；否则不是 noexcept。”

内层 noexcept(a < b) 表示：
“表达式 a < b 在语义上是否 noexcept（不会抛异常）”

所以：

整句含义：

如果 T 的 operator< 是 noexcept 的，那么整个 min<T> 也是 noexcept 的；
否则，min<T> 就不是 noexcept。

也就是 noexcept 自动根据 T 的能力推导。
*/