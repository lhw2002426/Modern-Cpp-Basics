struct A { int a; const float b; } a1 { 1, 1.0f };
static const int a2 = 2;
   
int main()
{
    const int a3 = 2;
    const A a4{ 1, 2.0f };
    // 重用a1.a是否合法？a1.b是否合法？a2, a3, a4.a, a4.b呢？
    //a1可以，a2不行（可能会写到只读区），a3可以，a4可以
    //答案，除了a1都不合法 这块存储不能是 const 对象（或 const 子对象）所占用的存储。
}