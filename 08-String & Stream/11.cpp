#include<bits/stdc++.h>
#include<sstream>
#include<fstream>
int main()
{
    /*std::wifstream fin{ "testin.txt" };
    // 读BOM
    std::basic_streambuf<char16_t> *buf =
        dynamic_cast<std::basic_streambuf<char16_t> *>(fin.rdbuf());
    fin>>buf;
    std::string_view sv = buf->str();
    std::cout << sv << "\n";*/
    std::ifstream fin{ "testin.txt" };
    fin.exceptions(std::ios::badbit | std::ios::failbit); // 只允许eof，其他抛异常.
    std::ostringstream str;
    fin>>str.rdbuf();
    std::string_view sv = str.view();
    std::cout << sv << "\n";
}