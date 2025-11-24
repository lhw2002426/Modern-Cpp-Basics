#include<bits/stdc++.h>
// 接受一个 “返回 int、参数 float 和 double” 的函数指针，自己返回 void
void CallIt(int (*fp)(flaot, double)){
    int res = fp(1.0,2.0);
    (void)res;
}
