#include<bits/stdc++.h>
#include<variant>
#include <iostream>
#include <variant>

std::string Process(const std::string &value) { return value; }
std::string Process(int value) { return std::to_string(value); }
std::string Process(float value) { return std::to_string(value); }

int main()
{
    // 测试类型 A
    std::vector<std::variant<int, float, std::string>> v{ 1, "test", 2.0f };
    std::string result{};
    for (auto &currVar : v)
    {
        result += std::visit([](const auto &value) { return Process(value); },
                            currVar);
    }
    std::cout << result << std::endl; // 输出 "1test2.000000"
    
    return 0;
}