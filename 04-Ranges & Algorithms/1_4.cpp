#include<bits/stdc++.h>
#include<range/v3/all.hpp>
namespace stdr = std::ranges;
namespace stdv = std::views;

namespace rv = ranges::views;
namespace rr = ranges;

std::generator<int> Fib(int num) // 生成[0, num)的斐波那契数列
{
    int last = 0, curr = 1;
    for(int i = 0; i < num; ++i)
    {
        co_yield curr;
        auto next = last + curr;
        last = curr;
        curr = next;
    }
}
int main()
{
    auto fib5 = Fib(5);
    for(auto num : fib5)
        std::printf("%d ", num); // 1, 1, 2, 3, 5
}