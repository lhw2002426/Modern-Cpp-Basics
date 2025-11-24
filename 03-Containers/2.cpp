#include<bits/stdc++.h>
/*
对`vector`做一些简单的API练习（本题中输出`vector`请包装为一个函数，并用`ostream_iterator`输出）：

   + 创建一个`std::vector v1`，它包含10个5（请不要真的写上去`{5,5,5,5,5...}`）。
   + 创建第二个`std::vector v2`，包含`{2,1,4}`。
   + 将`v2`反向插入到`v1`的第三个位置（即`5,5,4,1,2,5,5...`）。注意使用反向迭代器。
   + 移除从第5个元素开始的所有元素（即`5,5,4,1,2`）。
   + 移除所有奇数，请不要使用`O(n^2)`的方法。
   + 与`vector v{1,7}`做三路比较，打印结果。
*/


void print_vector(const std::vector<int>& vec) {
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

auto v1 = std::vector<int>(10, 5);
auto v2 = std::vector<int>{2, 1, 4};

int main()
{
    v1.insert(v1.begin() + 3,v2.rbegin(),v2.rend());
    print_vector(v1);
    v1.erase(v1.begin()+5,v1.end());
    print_vector(v1);
    v1.erase(std::remove_if(v1.begin(),v1.end(),[](int x){return x%2!=0;}),v1.end());
    print_vector(v1);
    std::vector<int> v3{1,7};
    if (v1 < v3) {
        std::cout << "v1 is less than v3" << std::endl;
    } else if (v1 > v3) {
        std::cout << "v1 is greater than v3" << std::endl;
    } else {
        std::cout << "v1 is equal to v3" << std::endl;
    }
}
