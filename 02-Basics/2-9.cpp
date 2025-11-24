#include<bits/stdc++.h>

struct DijkstraInfo
{
    int vertexID;
    int distance; // 作为比较的标准
};

bool Func(const auto& a, const auto& b) //这个地方的auto不合法,这其实是 缩写函数模板（C++20），即一个函数模板，而函数模板本身不是实体函数，不能直接作为函数指针/可调用对象传给 sort。
{
    return a.distance < b.distance;
}

template<typename T>
   struct Functor
   {
       // 如果你的编译器暂时不支持static operator()，把static去掉.
        bool operator()(const T& a, const T& b){ return a.distance < b.distance; }
   };

int main()
{
    std::vector<DijkstraInfo> vec = {
        {1, 10},
        {2, 5},
        {3, 20},
        {4, 15}
    };
   
    std::ranges::sort(vec, [=](const DijkstraInfo& a, const DijkstraInfo& b)->bool {//可以换成auto
        return a.distance < b.distance;
    } );

    // std::ranges::sort(vec, Func); //参数的auto不合法

    std::ranges::sort(vec, Functor<DijkstraInfo>{}); //使用函数对象,需要实例化模板为具体类型

    for (const auto& info : vec) {
        std::cout << "Vertex ID: " << info.vertexID << ", Distance: " << info.distance << "\n";
    }
}

