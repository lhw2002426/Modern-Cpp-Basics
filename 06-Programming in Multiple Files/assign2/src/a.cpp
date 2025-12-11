#include "a.h"
#include <cstdio>

//理论上来说模板函数的定义应该放在头文件中，但这里为了测试多文件编译，特意放在了源文件中
template<typename T>
void Func() { std::printf("Hello.\n"); }
static void test() { Func<int>(); }