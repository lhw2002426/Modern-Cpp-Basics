#include <array>
#include <ranges>

namespace stdr = std::ranges;
namespace stdv = std::views;

template<typename Cont>
Cont QuickSort(const Cont &cont)
{
    // 如果是空，返回空容器；否则...
    return stdr::empty(cont)
            ? cont
            : std::array<Cont, 3>{
                    QuickSort(cont | stdv::drop(1) | stdv::filter([&](const auto &elem) {
                        return elem < *stdr::begin(cont);
                    }) | stdr::to<Cont>()),
                    stdv::single(*stdr::begin(cont)) | stdr::to<Cont>(),
                    QuickSort(cont | stdv::drop(1) | stdv::filter([&](const auto &elem) {
                        return elem >= *stdr::begin(cont);
                    }) | stdr::to<Cont>()),
                } | stdv::join | stdr::to<Cont>();
}

int main()
{
    std::vector vec{ 10,2,3,10,4,5,6,7,8,9,1 };
    auto sorted = QuickSort(vec);
    for (auto& i : sorted)
        std::printf("%d ", i);
}