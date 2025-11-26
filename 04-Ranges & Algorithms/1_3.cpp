#include<bits/stdc++.h>
#include<range/v3/all.hpp>
namespace stdr = std::ranges;
namespace stdv = std::views;

namespace rv = ranges::views;
namespace rr = ranges;

int main()
{
    std::string s = "abc";
    for(auto [idx, elem] : rv::enumerate(s) )
       elem = (elem - 'a' + idx) % 26 + 'a';
    std::cout << s << "\n"; // ace
}