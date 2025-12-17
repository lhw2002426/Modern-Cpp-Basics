#include<bits/stdc++.h>
#include<format>

struct Data
{
    int a;
    double b;
};

template<typename T>
struct std::formatter<Data, T>
{
    constexpr auto parse(std::format_parse_context& ctx)
        -> std::format_parse_context::iterator
    {
        auto it = ctx.begin();
        /*
        明确拒绝其他格式化符号，否则当用户写了一个std::format("{:>10}", data);  会发现其实结果没对齐
        调用者无法区分「格式被支持」还是「被忽略」
        对内（维护者）：你知道 Data 不支持格式
        对外（调用者）：TA完全不知道
        */
        if (it != ctx.end() && *it != '}')
               throw std::format_error{ "Don't support specifiers currently." };
        return it;
    }

    template<class FormatContext>
    auto format(const Data& d, FormatContext& ctx) const
        -> typename FormatContext::iterator
    {
        return std::format_to(
            ctx.out(),
            "Data{{ a: {}, b: {} }}",
            d.a,
            d.b
        );
    }
};

int main()
{
    Data d{ 42, 3.14 };
    std::cout << std::format("Formatted Data: {}\n", d);
    return 0;
}