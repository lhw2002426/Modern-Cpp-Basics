#include<bits/stdc++.h>
class A
{
public:
    A(int init_a) : a{init_a}{}
    int GetBaseVal() const { return a; }
    virtual ~A() = default;
    // 编写一个Clone方法
    virtual A &Clone(const A &another) { return A::operator=(another); } //但是clone不会报错
protected:
    A &operator=(const A &) = default; //让直接的等号报错
private:
    int a;
};

class B : public A
{
public:
    B(int init_a, int init_b): A{init_a}, b{init_b} {}
    int GetDerivedVal() const { return b; }
    // 编写一个Clone方法
    B &Clone(const A &another) override
    {
        const auto &bRef = dynamic_cast<const B &>(another);
        //dynamic_cast 判断的是对象的动态类型是否真的是 B 或 B 的子类。A是B的父类所以报错
        return B::operator=(bRef);
    }
private:
    int b;
};

void Test(A& a)
{
    B b{2,3};
    // a = b; // Make it compile error
    a.Clone(b); // Right
}
   
void Test2(A& a)
{
    A a2{4};
    // a = a2; // Make it compile error
    a.Clone(a2); // Right
}

int main()
{
   A a{1};
   B b{4,5};
   Test(a);
   std::printf("%d\n", a.GetBaseVal()); // 2
   Test2(a);
   std::printf("%d\n", a.GetBaseVal()); // 4
   
   Test(b);
   std::printf("%d %d\n", b.GetBaseVal(), b.GetDerivedVal()); // 2, 3
   Test2(b); // 运行时错误（即利用转型的抛异常），因为A不能拷贝到B类型。
   /*
   Test(b) 后，b 被一个 B{2,3} 复制（base=2, derived=3）。
    Test2(b) 时，从 A 拷贝到 B 要 运行时抛异常。
   */
}
/*
你的 Clone 方案为什么能避免 Slicing？

看你的目标：

a = b; → 必须编译期禁止

a.Clone(b); → 必须进行运行时类型检查 + 正确的拷贝语义

对 B：

可以从 B 复制到 B

不能从 A 复制到 B（抛异常）

对 A：

可以从 A 和 B 复制，只拷贝 base 部分
*/