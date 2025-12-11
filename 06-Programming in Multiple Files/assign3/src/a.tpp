// a.tpp
#ifndef A_TPP
#define A_TPP

template<typename T>
void Func() {
    // 使用 std::cout 代替 std::println 以获得更好的兼容性
    std::cout << "Hello from Func<" << typeid(T).name() << ">" << std::endl;
}

#endif // A_TPP