#include<bits/stdc++.h>
void FillFibonacci(std::vector<int>& v)
{
    int a = 0, b = 1;//a,b定义放在前面
    std::ranges::generate(v, [/*a=0, b=1*/ =] () mutable {
        for (size_t i = 0; i < v.size(); ++i) {
            int current = a;
            int next = a + b;
            a = b;
            b = next;
            return current;
        }
    });
}
std::vector<int> fib(10);
int main()
{
    FillFibonacci(fib);
    for (const auto& num : fib) {
        std::cout << num << " ";
    }
}