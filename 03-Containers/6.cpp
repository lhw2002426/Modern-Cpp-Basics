#include<bits/stdc++.h>
int main()
{
    std::vector vec{ 10,2,3,10,4 };
    auto it = std::ranges::max_element(vec);
    std::erase(vec, *it);//移除了一次后迭代器失效？
    for (auto& i : vec)
        std::printf("%d ", i);
    /*
    // 关键：先拷贝最大值，而不是保存引用
    auto max_it = std::ranges::max_element(vec);
    int max_value = *max_it;  // 拷贝值，不是引用
    
    std::erase(vec, max_value);  // 删除所有等于max_value的元素
    */
}