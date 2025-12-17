#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using Iter1 = std::istream_iterator<char>;
using Iter2 = std::istreambuf_iterator<char>;

void test1()
{
    std::stringstream str{ "123 456\n789" };
    std::string s;
    std::copy(Iter1{ str }, Iter1{}, std::back_inserter(s));
    std::cout << s;
}

void test2()
{
    std::stringstream str{ "123 456\n789" };
    std::string s;
    std::copy(Iter2{ str }, Iter2{}, std::back_inserter(s));
    std::cout << s;
}

int main()
{
    test1();
    std::cout << '\n';
    test2();
    return 0;
}
/*
Iter1 = std::istream_iterator<char> 是格式化输入迭代器（formatted input iterator）。它内部等价于反复执行：

char c;
str >> c;   // 注意是 operator>>，属于格式化提取


对 char 的 operator>> 有一个关键行为：

默认会跳过空白字符（受 std::ios::skipws 影响，默认开启）

“空白字符”包括空格 ' '、换行 '\n'、制表符等

所以从 "123 456\n789" 中提取 char 时：

' ' 被跳过

'\n' 被跳过

其余数字字符被依次读出

因此拼出来就是：

"123456789"

为什么 test2() 输出原样 123 456\n789？

Iter2 = std::istreambuf_iterator<char> 是缓冲区迭代器（unformatted / raw buffer iterator）。它直接从流的 streambuf 逐字节读取，等价于：

不走 operator>>

不进行格式化解析

不受 skipws 影响

空格和换行都会原样读取

所以拷贝结果就是原字符串：

"123 456\n789"

输出到 cout 时就显示为两行
*/