#include <type_traits>
#include <utility>   // C++23: std::to_underlying
#include <iostream>

enum class Perm : unsigned {
    None    = 0,
    Read    = 1 << 0,
    Write   = 1 << 1,
    Execute = 1 << 2,
};

constexpr Perm operator|(Perm a, Perm b) noexcept {
    return static_cast<Perm>(
        std::to_underlying(a) | std::to_underlying(b)
    );
}

constexpr Perm operator&(Perm a, Perm b) noexcept {
    return static_cast<Perm>(
        std::to_underlying(a) & std::to_underlying(b)
    );
}
constexpr Perm& operator|=(Perm& a, Perm b) noexcept {
    a = a | b;
    return a;
}
int main() {
    Perm p = Perm::Read | Perm::Write;
    if ((p & Perm::Read) == Perm::Read) std::cout << "has read\n";
    p |= Perm::Execute; // 现在包含 read|write|exec
}
