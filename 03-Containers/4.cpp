#include<bits/stdc++.h>
/*
`deque`是否具有`.data`方法？为什么？
*/

int main()
{
    std::deque<int> d{1,2,3,4,5};
    std::cout << d.data() << std::endl; // 这一行会报错，因为deque没有data()方法
    //因为deque本质上是指针的集合，而不是连续的内存块
}