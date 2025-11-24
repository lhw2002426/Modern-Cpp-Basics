#include <bits/stdc++.h>
std::vector<int> vec{0, 1, 2, 3, 4, 5};
void test1()
{
    auto it = vec.find(1);
    vec.insert(it - 1, 110);
    *it = 2;//vec位置移动，it已经失效
}

void test2()
{
    auto it = vec.find(1);
    vec.insert(it + 1, 110);
    *it = 2;//it本身没问题，但是万一引起扩容了，就不行了
}
void test3()
{
    auto it = vec.find(1);
    if(it.capacity() > it.size())
    {
        vec.insert(it + 1, 110);
        *it = 2;//it本身没问题，因为没有引起扩容
    }
}
int main()
{
    test1();
    test2();
    test3();
}