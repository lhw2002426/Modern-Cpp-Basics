#include<bits/stdc++.h>
#include<stdexcept>

#include <algorithm>
#include <memory>
#include <format>

template<typename T>
struct ListNode
{
    ListNode* prev;
    ListNode* next;
    T val; // 正常来说应该是像InplaceVector一样搞个buffer
            // 这样就不用担心T不能默认构造的问题，我们简化处理
};
/*
我们把sentinel放到基类里，避免在派生类里出现切片问题
*/
template<typename T>
class ListBase
{
protected:
    ListNode<T> sentinel_{ &sentinel_, &sentinel_ };
    ~ListBase()
    {
        auto curr = sentinel_.next;
        while (curr != &sentinel_)
        {
            auto next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

template<typename T>
class List : public ListBase<T>
{
    // 可以修改到其他类里
    // ListNode<T> sentinel_{ &sentinel_, &sentinel_ };
    
    // 如果你使用基类并把sentinel放到里面，this->是必需的。我们在模板会讲述原因。
    auto& GetSentinel_() { return this->sentinel_; }
    
public:
    class ConstIterator
    {
        const ListNode<T> *node_;
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        ConstIterator(const ListNode<T> *node) : node_{ node } {}
        ConstIterator operator++(int) noexcept
        {
            auto node0 = node_;
            node_ = node_->next;
            return ConstIterator{ node0 };
        }

        ConstIterator &operator++() noexcept
        {
            node_ = node_->next;
            return *this;
        }
        const T &operator*() const noexcept { return node_->val; }
        const T *operator->() const noexcept { return &(node_->val); }
        bool operator==(const ConstIterator &another) const noexcept = default;
    };    
    
    // template<typename It>
    // List(It begin, It end)
    // {
    //     // TODO...
    //     // 如果构造失败，注意对分配的元素进行释放
    //     // 你可以选择使用标准库中VectorBase或VectorImpl一样的方法
    //     // 利用已经构造好的部分总会析构的特性
    //     // 也可以自己写一个Guard类承接sentinel并连接出链表，在退出前再Release给sentinel。
    //     ListNode<It> new_head{ nullptr, nullptr, *begin };
    //     ListNode<It> new_tail{ nullptr, nullptr, *(end - 1) };
    //     swap(sentinel_.next, new_head);
    //     swap(sentinel_.prev, new_tail);
    // }

    template<typename It>
    List(It begin, It end)
    {
        auto pos = &this->sentinel_;
        while(begin != end)
        {
            // 先分配节点，使用unique_ptr防止异常时内存泄漏
            std::unique_ptr<ListNode<T>> ptr{ new ListNode<T>{ pos, pos->next, *begin } };
            ++begin;
            // 连接节点
            pos->next->prev = ptr.get();
            pos->next = ptr.release();
            pos = pos->next;
        }
        return;
    }
    auto begin() const { return ConstIterator{ this->sentinel_.next }; }
    auto end() const { return ConstIterator{ &this->sentinel_ }; }
    
    void swap(List& another) noexcept
    {
        std::swap(this->sentinel_.prev, another.sentinel_.prev);
        std::swap(this->sentinel_.next, another.sentinel_.next);

        auto fix = [](ListNode<T>& s) {
            s.next->prev = &s;
            s.prev->next = &s;
        };

        fix(this->sentinel_);
        fix(another.sentinel_);
    }

    // 委托构造函数(Delegating ctor)，我记得好像是讲过了
    List(const List& another) : List{ another.begin(), another.end() } {}
    // List& operator=(const List &another)
    // {
    //     // TODO...
    //     List temp{ another };
    //     swap(this->sentinel_, temp.sentinel_);
    //     return *this;
    // }
    List& operator=(const List &another)
    {
        if (this != &another)
        {
            List temp{ another };
            swap(temp);
        }
        return *this;
    }
    // 根据你的实现方式，确定是否需要手动写~List()。
};

// template<typename T> 
// struct std::formatter<List<T>>
// {
//     constexpr auto parse(auto& ctx) { return ctx.begin(); }
//     auto format(const List<T>& lst, auto& ctx) 
//     {
//         std::string s = "[";
//         for (auto it = lst.begin(); it != lst.end(); ++it)
//         {
//             if (it != lst.begin())
//                 s += "=> ";
//             s += std::to_string(*it);
//         }
//         s += "]";
//         return std::formatter<std::string>::format(s, ctx);
//     }
// };

template<typename T>
struct std::formatter<List<T>, char> 
{
    // 关键：parse 必须 constexpr，且签名要用 std::format_parse_context
    constexpr auto parse(std::format_parse_context& ctx)
        -> std::format_parse_context::iterator
    {
        // 不支持任何自定义格式说明，直接返回
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(const List<T>& lst, FormatContext& ctx) const
        -> typename FormatContext::iterator
    {
        // 直接写到 ctx.out()，避免构造中间 string 的额外分配
        auto out = ctx.out();

        out = std::format_to(out, "[");
        bool first = true;

        for (auto it = lst.begin(); it != lst.end(); ++it)
        {
            if (!first)
                out = std::format_to(out, "=> ");
            first = false;

            // 对 int 没问题；如果 T 不是算术类型，建议改为 std::format_to(out, "{}", *it);
            out = std::format_to(out, "{}", *it);
        }

        out = std::format_to(out, "]");
        return out;
    }
};

void test1(){
   std::vector<int> v{ 1,2,3 };
   List<int> l{ v.begin(), v.end() };
   for (auto it = l.begin(); it != l.end(); it++)
       std::printf("%d\n", *it);
}

class SomeClassMayThrow
{
    int val_;
public:
    SomeClassMayThrow(int val) : val_{val} {}
    SomeClassMayThrow() : val_(0) {}
    static inline int i = 0;
    static inline int max_copies = 2;
    static void Reset(int val)
    {
        i = 0;
        max_copies = val;
    }
    SomeClassMayThrow(const SomeClassMayThrow &another) : val_{ another.val_ }
    {
        if (i++ == max_copies)
        {
            // 拷贝到第三个对象时抛出异常，模拟构造失败
            throw std::runtime_error{ "Test" };
        }
        std::printf("Constructed.\n");
    }
    ~SomeClassMayThrow() { std::printf("Dtor.\n"); }
    auto GetVal() const noexcept { return val_; }
};

void test2(){
   
   std::vector<SomeClassMayThrow> a;
   a.reserve(3);
   a.emplace_back(1);
   a.emplace_back(2);
   a.emplace_back(3);
   try
   {
       List<SomeClassMayThrow> l{ a.begin(), a.end() };
   }
   catch (const std::exception &ex)
   {
       std::printf("%s\n", ex.what());
   }
}
void test3(){
    SomeClassMayThrow::Reset(5);
   std::vector<SomeClassMayThrow> a;
   a.reserve(3);
   a.emplace_back(1);
   a.emplace_back(2);
   a.emplace_back(3);
   List<SomeClassMayThrow> l{ a.begin(), a.end() };
   List<SomeClassMayThrow> l2{ a.begin() + 1, a.end() };
   try
   {
       l2 = l;
       printf("test3 assignment succeeded unexpectedly\n");
   }
   catch (const std::exception &ex)
   {
       std::printf("test3 %s\n", ex.what());
       // 应当输出2, 3，即赋值失败对其无影响。
       for (auto it = l2.begin(); it != l2.end(); ++it)
           std::printf("%d\n", it->GetVal());
   }
}

//测试format
void test4(){
    std::vector<int> v{ 1,2,3 };
    List<int> l{ v.begin(), v.end() };
    std::cout << std::format("List: {}\n", l);
}

int main()
{
    printf("----- test1 -----\n");
    test1();
    printf("----- test2 -----\n");
    test2();
    printf("----- test3 -----\n");
    test3();
    printf("----- test4 -----\n");
    test4();
    return 0;
}