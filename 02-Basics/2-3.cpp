#include <iostream>
#include <iomanip>
using namespace std;

struct Empty { };                          // 空类：标准要求 size >= 1
struct EmptyVirtual { virtual void f(){} }; // 多态类：通常多一个 vptr

struct P1 { int x; };
struct P2 { int x; virtual void f(){} };    // 在 P1 基础上加虚函数

struct P3 { int x; double y; };
struct P4 { int x; double y; virtual void f(){} }; // 再观察对齐与填充

struct OneV { virtual void f(){} };
struct TwoV { virtual void f(){} virtual void g(){} }; // 多个虚函数通常仍只有一根 vptr
// 总大小必须是最大对齐系数的倍数

int main() {
    cout << "Pointer size            : " << sizeof(void*) << "\n\n";

    cout << left << setw(22) << "sizeof(Empty)"        << sizeof(Empty)        << "\n";
    cout << left << setw(22) << "sizeof(EmptyVirtual)" << sizeof(EmptyVirtual) << "  (has vptr)\n\n";

    cout << left << setw(22) << "sizeof(P1)" << sizeof(P1) << "\n";
    cout << left << setw(22) << "sizeof(P2)" << sizeof(P2) << "  (P1 + vptr + padding?)\n\n";

    cout << left << setw(22) << "sizeof(P3)" << sizeof(P3) << "  (int + padding + double)\n";
    cout << left << setw(22) << "sizeof(P4)" << sizeof(P4) << "  (vptr + int + padding + double)\n\n";

    cout << left << setw(22) << "sizeof(OneV)" << sizeof(OneV) << "  (1 vptr)\n";
    cout << left << setw(22) << "sizeof(TwoV)" << sizeof(TwoV) << "  (still 1 vptr)\n";
}
