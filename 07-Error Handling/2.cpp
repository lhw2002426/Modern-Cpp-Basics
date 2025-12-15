#include<bits/stdc++.h>
#include<stdexcept>
#include<exception>
/*
我们写一个非常简单的`inplace_vector`，练习一下placement new。这是C++26会引入的新容器，它在栈上分配，但与`std::array`不同的是，它只是保留了固定大小的内存，在插入的时候才会真正构造。我们只完成它的析构函数、`.size()`、`operator[]`、`push_back`和`pop_back`。
*/
template<typename T, std::size_t N>
class InplaceVector
{
public:
    InplaceVector() = default;
    T* Data() noexcept  { return reinterpret_cast<T*>(buffer_); }
    const T* Data() const noexcept { return reinterpret_cast<const T*>(buffer_); }
    std::size_t Size() const noexcept {
        return size_;
    }
    void PushBack(const T& value) {
        if (size_ >= N) throw std::bad_alloc{};

        // 在第 size_ 个位置用 placement new 构造一个 T
        new (Data() + size_) T(value);
        ++size_;
    }

    void PopBack(){
        size_--;
        reinterpret_cast<T*>(&buffer_[size_])->~T();
    }
    T& at(std::size_t index){
        if(index>=size_) throw std::out_of_range("Index out of range");
        return (*(Data() + index));
    }
    // operator[]，const和非const两个版本
    T& operator[](std::size_t index){
        return *(Data() + index);
    }
    const T& operator[](std::size_t index) const {
        return *(Data() + index);
    }
    ~InplaceVector() { 
        for(std::size_t i=0;i<size_;i++){
            reinterpret_cast<T*>(&buffer_[i])->~T();
        }
    }
private:
    // 我们假设成员是一个具有合适对齐的buffer，能够放下N个元素。
    // 同时需要一个std::size_t来记录它目前的实际大小。
    std::size_t size_{0};
    alignas(T) char buffer_[N * sizeof(T)];
};

/*
1. 对象是不是已经“活着”（lifetime）
std::array<T, N> 内部的 T elems_[N];

标准保证：std::array<T, N> 里面就是 T elems_[N];（或者等价形式）。

当你构造一个 std::array<T, N> arr; 的时候：

这 N 个 T 对象的生命周期就已经开始了。

如果 T 有构造函数，会被自动调用。

析构时，也会自动调用 N 个 T 的析构函数。

也就是说：

std::array 里装的是真正的 T 对象，它们 总是处于“已构造”的状态。

你的 buffer_（例如 std::aligned_storage）

你现在写的是类似这样的：

using Storage = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
Storage buffer_[N];         // 注意：这里不是 T
std::size_t size_;


buffer_[i] 的类型是 Storage，不是 T。

当 InplaceVector 构造时：

只是拿到了一块 “对齐好的原始字节存储”，里面没有任何 T 对象在活着。

只有你手动写：

new (&buffer_[i]) T(value);  // placement new


时，某个位置上才真正开始了一个 T 对象的生命周期。

对应的销毁也必须手动：

reinterpret_cast<T*>(&buffer_[i])->~T();


所以：

std::array = “N 个活着的 T”

buffer_ = “一块原始内存 + 你自己决定在其中哪些位置创建多少个 T”

这就是你 PopBack 和析构里必须用 reinterpret_cast 的原因——因为 buffer_[i] 不是 T，你得把它解释成 T* 才能调用 ~T()。
*/

int main()
{
    InplaceVector<int, 10> vec;
    for(int i=0;i<10;i++)
        vec.PushBack(i*i);
    for(std::size_t i=0;i<vec.Size();i++)
        std::printf("%d ", vec[i]);
    std::printf("\n");
    for(int i=0;i<5;i++)
        vec.PopBack();
    for(std::size_t i=0;i<vec.Size();i++)
        std::printf("%d ", vec[i]);
    //test exception
    try{
        for(int i=0;i<6;i++)
            vec.PushBack(i*i);
    }catch(const std::bad_alloc& e){
        std::printf("Caught exception: %s\n", e.what());
    }
    
    try {
        vec.at(10);
    } catch (const std::out_of_range& e) {
        std::printf("Caught exception: %s\n", e.what());
    }
    std::printf("\n");
}