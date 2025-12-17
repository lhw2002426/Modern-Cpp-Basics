#include<bits/stdc++.h>
void OutputTest(int num, std::size_t val)
{
    std::cout<<"num: "<< num <<", end: "<< val <<std::endl;
}
int main()
{
    std::string str{ " 1234 567a" };
    std::size_t end = 0;
    //到1234后面的空格就停止了
    OutputTest(std::stoi(str, &end, 16), end);
}
/*
解析规则（关键点）

stoi 会跳过前导空白。

base = 16，所以合法数字字符是 0-9、a-f、A-F。

解析会从第一个合法数字开始一直读到遇到第一个不属于该 base 的字符为止。

end（pos）返回的是“停止解析的位置”，是相对于原字符串起始位置的下标。

字符串内容（含下标）：

index 0: ' '（空格）

index 1: '1'

index 2: '2'

index 3: '3'

index 4: '4'

index 5: ' '（空格）

index 6: '5'

index 7: '6'

index 8: '7'

index 9: 'a'

解析过程：

跳过 index 0 的空格，从 index 1 开始读。

读到 "1234"（十六进制合法）

在 index 5 遇到空格，停止。

所以：

解析的 token 是 "1234"（16 进制）

值：0x1234 = 4660

end = 5（停在空格的位置）

如果输出格式正确，你想打印的内容应该是：
*/