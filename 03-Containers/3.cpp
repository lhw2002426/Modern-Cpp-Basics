#include<bits/stdc++.h>
/*
 创建一个`std::list l1`，它包含10个5。
   + 创建第二个`std::list l2`，包含`{2,1,4}`。
   + 将`l2`融合到`l1`中，操作后`l2`变为空。
   + 对`l1`去除相邻的重复元素。
   + 对`l1`排序。
*/

std::list<int> l1(10, 5);
std::list<int> l2{2, 1, 4};
void print_list(const std::list<int>& lst) {
    std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main()
{
    l1.merge(l2);
    print_list(l1);
    print_list(l2);
    l1.unique();
    print_list(l1);
    l1.sort();
    print_list(l1);   
}