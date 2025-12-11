// a.cpp
#include "../include/a.h"
#include "../include/a.tpp"  // 包含模板定义

// 显式实例化
template void Func<int>();
template void Func<double>();