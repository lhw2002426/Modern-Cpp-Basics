#include<bits/stdc++.h>
#include<locale>
#include<fstream>
#include<sstream>
#include<spanstream>

int main()
{
    std::string s0{ "1.234 567 " };
    // std::array<char, 20> buffer{s0.begin(), s0.end()};
    // std::spanstream s{ buffer.data(), buffer.size() };
    std::spanstream s{ s0 };
    float a; int b;
    s >> a >> b;
    std::printf("a = %f, b = %d\n", a, b);
    s << b;
    std::printf("get pos = %ld, put pos = %ld \n", s.tellg() - std::streampos{0}, 
                 s.tellp() - std::streampos{0});
    auto sapn = s.span();
    // std::printf("original string = %s,\nunderlying string = %s \n", s0.c_str(), s.str().c_str());
    std::printf("original string = %s,\nunderlying string = %.*s \n", s0, 
                 std::string_view{ sapn.data(), sapn.data() + sapn.size() });
}