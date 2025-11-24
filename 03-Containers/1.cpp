#include<bits/stdc++.h>

//对第一个元素`*2`，并累加所有的元素
template<typename Range>
void Function(Range& range)
{
    using std::begin;
    using std::end;
    int sum = 0;
    // auto it = range.begin();
    auto it = begin(range);
    *it *= 2; // 对第一个元素*2
    // for(auto it = range.begin(); it != range.end(); ++it)
    for (auto it = begin(range); it != end(range); ++it)
    {
        sum += *it;
    }
    std::cout << "Sum: " << sum << std::endl;
}
int main()
{
    // 请测试以下情况：
   std::vector v{1,2,3}; Function(v);
   for (auto x : v) std::cout << x << " "; std::cout << std::endl; // 验证第一个元素是否被*2
   std::list l{1,2,3}; Function(l);
   for (auto x : l) std::cout << x << " "; std::cout << std::endl; // 验证第一个元素是否被*2
   int arr[]{1,2,3}; Function(arr); // 看到这里，你就应该明白不能使用.begin，而是使用什么？ begin(range)
   for (auto x : arr) std::cout << x << " "; std::cout << std::endl; // 验证第一个元素是否被*2
}
   