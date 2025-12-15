#include <bits/stdc++.h>
/*
实参是 std::vector<int>，不是 optional，所以需要一个隐式转换：

使用 optional 的 converting constructor：

std::optional<std::vector<int>>::optional(const T& value);


也就是用 v 构造一个 std::optional<std::vector<int>> 临时对象。

这一步里，会拷贝一次 std::vector<int>，把 v 里的内容拷贝到 optional 内部保存的那份 vector<int> 中。
*/
void Test1(std::optional<std::vector<int>> optVector)
{
    if (optVector && !optVector->empty()) // short-circuit.
        std::printf("%d\n", optVector->at(0));
    return;
}
/*
实参仍是 std::vector<int>，不是 optional → 仍然需要构造一个 临时的 std::optional<std::vector<int>>。

构造这临时 optional 的时候，逻辑和 Test1 一样：

用 optional(const T& value) 构造

里面会拷贝一次 std::vector<int>。

然后将这个临时 optional 绑定到形参 const std::optional<std::vector<int>>&：

引用绑定延长了这个临时对象的生命周期到整个函数体。
*/
void Test2(const std::optional<std::vector<int>>& optVector)
{
    if (optVector && !optVector->empty()) // short-circuit.
        std::printf("%d\n", optVector->at(0));
    return;
}
//标准规定 std::optional<T> 的 T 必须是 object type，不能是引用类型，所以 optional<T&> / optional<const T&>
// void Test3(std::optional<const std::vector<int>&> optVector)
// {
//     if (optVector && !optVector->empty()) // short-circuit.
//         std::println("{}", optVector->at(0));
//     return;
// }

/*
optVector 内部只保存一份“指向 v 的引用包装”，不会拷贝 v；

又保留了“可能为空”的 optional 语义。
*/
void Test4(std::optional<std::reference_wrapper<std::vector<int>>> optVector) //
{
    if (optVector && !optVector->get().empty()) // short-circuit.
        std::printf("%d\n", optVector->get()[0]);
    return;
}


int main()
{
    std::vector<int> v{ 1,2,3 };
    Test1(v);
    Test2(v);
    // Test3(v);
    Test4(v);
    return 0;
}