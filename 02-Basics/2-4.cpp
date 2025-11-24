/*
C++ 重载决议只看参数列表（含 cv/ref、noexcept 等）、所属作用域、模板实参等，不看返回类型。

绝大多数 ABI 的符号名（mangled name）也只编码函数名 + 作用域 + 参数类型 + 模板实参；返回类型一般不编码。

因此第一组会产生相同符号名（冲突）；第二组里模板版本会把 <T>（即使 T 只在返回类型里用到）编码进符号名，例如 Itanium ABI 下大致类似：

非模板 void Test(int) → _Z4Testi

模板 Test<void>(int) → _Z4TestIvEi（注意 IvE 表示模板实参 void，与上一个不同）
*/
#include<bits/stdc++.h>
// file: case1.cpp
// 这段代码会编译失败：redefinition with different return type
// 非模板版本
void Test(int) {
    std::puts("non-template: void Test(int)");
}
// int  Test(int);  // ❌ 同名同参，仅返回类型不同，非法

// 模板版本（返回类型是模板参数 T）
template<typename T>
T Test(int) {
    std::puts("template: T Test(int)");

    if constexpr (!std::is_void_v<T>) {
        return T{};        // 可构造的类型
    } else {
        return;            // void 版本必须写 return;
    }
}

int main() {
    Test(42);           // ✅ 选中非模板（模板不能从返回类型推导 T）

    auto x = Test<long>(7);  // ✅ 显式指定 T=long，调用模板版本
    static_assert(std::is_same_v<decltype(x), long>);

    Test<void>(0);      // ✅ 显式指定 T=void，调用模板版本（与非模板不同符号名）
}
