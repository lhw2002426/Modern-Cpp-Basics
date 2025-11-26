#include<bits/stdc++.h>
// #include <ranges>
#include <range/v3/all.hpp>
namespace stdv = std::views;
namespace stdr = std::ranges;

namespace rv = ranges::views;
namespace rr = ranges;

template<typename Cont>
Cont QuickSort(const Cont& cont)
{
    // 如果是空，返回空容器；否则...
    return stdr::empty(cont) ? cont :
    // Your code...
    ([&]{
        auto pivot = *cont.begin();                         // evaluate once, store by value
        Cont left  = cont | rv::filter([&](auto const& v){ return v < pivot; }) | rr::to<Cont>();
        Cont right = cont | rv::filter([&](auto const& v){ return v > pivot; }) | rr::to<Cont>();
        return std::array<Cont, 3>{QuickSort(left), (rv::single(pivot) | rr::to<Cont>()), QuickSort(right)} | stdv::join | rr::to<Cont>();
    }());
}
/*
droped

ranges::views::concat(
        QuickSort(cont | rv::filter([&](const auto& v){ return v < *cont.begin(); })
                        | rr::to<Cont>()), // 小于基准值的部分
        stdv::single(*cont.begin()), // 基准值
        QuickSort(rv::filter([&](const auto& v){ return v > *cont.begin(); })
                      | rr::to<Cont>()) // 大于基准值的部分
    ) | rr::to<Cont>(); // 转换为常见容器类型
*/
/*
且 cont 是 view（不是容器）时：

view 的 begin() 假设 view 内部数据来源仍有效

但在 recursive QuickSort 中，你常常 materialize 成新容器

pivot 可能指向一个临时 view 的内部路径

后续递归可能已销毁原始 view

导致 pivot 是 悬空引用（UB）
*/

int main()
{
    std::vector vec{ 10,2,3,10,4,5,6,7,8,9,1 };
    auto sorted = QuickSort(vec);
    for (auto& i : sorted)
        std::printf("%d ", i);
}