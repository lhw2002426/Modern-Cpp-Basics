#include<bits/stdc++.h>
std::string ReplaceAllSubstr1(std::string_view str, 
                                std::string_view oldStr, std::string_view newStr)
{
    /* 你的实现... */
    while(true) {
        size_t pos = str.find(oldStr);
        if (pos == std::string_view::npos) {
            break;
        }
        str = std::string_view{str.data(), str.size() - oldStr.size() + newStr.size()};
        std::memmove(const_cast<char*>(str.data()) + pos + newStr.size(),
                     str.data() + pos + oldStr.size(),
                     str.size() - pos - newStr.size());
        std::memcpy(const_cast<char*>(str.data()) + pos, newStr.data(), newStr.size());
    }
    return std::string{str};
}

std::string ReplaceAllSubstr2(std::string_view str, 
                                std::string_view oldStr, std::string_view newStr)
{
    /* 你的实现... */
    std::string res = std::string{str};
    while(true) {
        size_t pos = str.find(oldStr);
        if (pos == std::string_view::npos) {
            break;
        }
        res.replace(pos, oldStr.size(), newStr);
    }
    return res;
}

int main()
{
    std::string str = "abcdeabcfgabchijabc";
    std::string oldStr = "abc";
    std::string newStr = "xyz";
    std::cout << ReplaceAllSubstr1(str, oldStr, newStr) << std::endl;
    std::cout << ReplaceAllSubstr2(str, oldStr, newStr) << std::endl;
    return 0;
}