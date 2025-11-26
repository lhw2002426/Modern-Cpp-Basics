#include<bits/stdc++.h>
#include <range/v3/all.hpp>
namespace stdv = std::views;
namespace stdr = std::ranges;

namespace rv = ranges::views;
namespace rr = ranges;
std::vector<std::string> SplitString(const std::string& str, 
                                        const std::string& delim)
{
    return str | std::views::split(delim)
               | std::views::transform([](auto&& rng) {
                     return std::string(&*rng.begin(), std::ranges::distance(rng));
                 })
               | rr::to<std::vector<std::string>>();
}

int main()
{
    std::string s = "Hello,World,from,Modern,C++";
    std::string delimiter = ",";
    auto result = SplitString(s, delimiter);
    for (const auto& part : result) {
        std::cout << part << std::endl;
    }
}