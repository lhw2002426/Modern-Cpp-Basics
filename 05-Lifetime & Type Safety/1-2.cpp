#include<bits/stdc++.h>
const std::vector<int>& SomeFunc(const std::vector<int>& vec)
{
    return vec;
}

const auto& a = SomeFunc({1,2,3});
// std::cout << a[0];// UB：a引用了一个临时对象，临时对象在返回后销毁，a变成悬空引用

class LambdaStore
{
public:
    LambdaStore(const std::function<void(float)>& init_fn)
        : fn{init_fn}
    {
        fn(11.1f);    // works, why?
        //初始化时传入的lambda还活着
    }

    // crashes, why?
    //调用时传入的lambda已经销毁
    void ExecuteStoredLambda() { fn(99.9f); }

private:
    const std::function<void(float)>& fn;//把成员的&去掉就可以避免UB
};

int main()
{
    LambdaStore lambdaStore([](float a) { std::cout << a << '\n'; });
    lambdaStore.ExecuteStoredLambda();
    return 0;
}