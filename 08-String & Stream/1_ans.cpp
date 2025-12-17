#include<bits/stdc++.h>
#include <range/v3/all.hpp>
namespace rv = ranges::views;
std::string ReplaceAllSubstr1(std::string_view str, 
                                std::string_view oldStr, std::string_view newStr)
{
    return str | rv::split(oldStr)
               | rv::intersperse(newStr)
               | ranges::to<std::string>();
}

std::string ReplaceAllSubstr2(std::string_view str, 
                                std::string_view oldStr, std::string_view newStr)
{
    std::string res, newstr{newStr};
    std::size_t lastPos = 0, pos;
    while((pos = str.find(oldStr, lastPos)) != std::string_view::npos) {
        res+= std::string{str.substr(lastPos, pos - lastPos)};
        res += newstr;
        lastPos = pos + oldStr.size();
    }
    return res += std::string{str.substr(lastPos)};
}

/*
如果单纯使用replace，每次replace都可能重分配内存，导致复杂度变高，接近O(n^2)。
不过实践上可能会更快，是因为传入的string 的capacity通常大于size，减少了重分配的次数。
如果在一开始reserve(str.size())，则可以看出问题
*/
std::string ReplaceAllSubstr3(std::string_view str, 
                                std::string_view oldStr, std::string_view newStr)
{
    std::boyer_moore_searcher searcher{
        oldStr.begin(), oldStr.end()
    };
    std::string res;
    auto beginIt = str.begin();
    auto endIt = str.end();
    while(true) {
        auto SearchRes = searcher(beginIt, endIt);
        res.append(beginIt, SearchRes.first);
        if (SearchRes.first == endIt) 
            break;
        beginIt = SearchRes.second;
        res.append(newStr);
    }
    return res;
}

int mian()
{
    std::string str = "abcdeabcfgabchijabc";
    std::string oldStr = "abc";
    std::string newStr = "xyz";
    std::cout << ReplaceAllSubstr1(str, oldStr, newStr) << std::endl;
    std::cout << ReplaceAllSubstr2(str, oldStr, newStr) << std::endl;
    std::cout << ReplaceAllSubstr3(str, oldStr, newStr) << std::endl;
    return 0;
}