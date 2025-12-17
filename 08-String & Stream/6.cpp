#include <bits/stdc++.h>
#include <numbers>
#include <format>
#include <iomanip>   // std::quoted

/*
   + 以宽度为10的左对齐方式输出数字`10086`和`10085`，多余部分留空格。
   + 以二进制方式、八进制方式和十六进制方式输出数字`1898`，其中16进制带前缀并大写字母。
   + 对于`pi`，分别输出七位有效数字和小数点后七位。
   + 输出`123\n\t`的 escaped 形式。
*/

int main()
{
    // 左对齐，宽度 10
    std::cout << std::format("{:<10}\n{:<10}\n", 10086, 10085);

    // 二进制 / 八进制 / 十六进制（带前缀，大写）
    std::cout << std::format("{:b}\n{:o}\n{:#X}\n", 1898, 1898, 1898);

    // 七位有效数字 / 小数点后七位
    std::cout << std::format("{:.7g}\n{:.7f}\n",
                             std::numbers::pi,
                             std::numbers::pi);

    // escaped 形式（标准库做法）
    std::cout << std::quoted("123\n\t") << '\n';

    return 0;
}
