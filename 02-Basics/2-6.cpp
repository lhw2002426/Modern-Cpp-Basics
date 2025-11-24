#include<bits/stdc++.h>

template <class T>
class Array3D {
public:
    using size_type = std::size_t;
    Array3D() = default;
    Array3D(size_type x, size_type y, size_type z, const T& init = T{})
        : nx_(x), ny_(y), nz_(z), data_(x * y * z, init) {}
    // 拷贝构造
    Array3D(const Array3D& other)
        :nx_(other.nx_), ny_(other.ny_), nz_(other.nz_), data_(other.data_) {}
    // 拷贝赋值 需要考虑自赋值
    Array3D& operator=(const Array3D& other) {
        if (this == &other) return *this;
        nx_ = other.nx_; ny_ = other.ny_; nz_ = other.nz_;
        data_ = other.data_;
        return *this;
    }
    //移动语义
    Array3D(Array3D&&) noexcept = default;
    Array3D& operator=(Array3D&&) noexcept = default;

    //函数调用式下标访问
    T& operator()(size_type i, size_type j, size_type k){
        assert(i < nx_ && j < ny_ && k < nz_);
        return data_[index(i,j,k)];
    }
    const T& operator()(size_type i, size_type j, size_type k) const {
        assert(i < nx_ && j < ny_ && k < nz_);
        return data_[index(i,j,k)];
    }
    // 数组式下标访问，需要先写代理
    class RowProxy {
    public:
        RowProxy(T* base, size_type nz) : base_(base), nz_(nz) {}
        T& operator[](size_type k) {
            return base_[k];
        }
        const T& operator[](size_type k) const {
            return base_[k];
        }
    private:
        T* base_;
        size_type nz_;
    };
    class PlaneProxy{
    public:
        PlaneProxy(T* base, size_type ny, size_type nz)
            : base_(base), ny_(ny), nz_(nz) {}
        RowProxy operator[](size_type j) {
            assert(j < ny_);
            return RowProxy(base_ + j * nz_, nz_);
        }
        const RowProxy operator[](size_type j) const {
            assert(j < ny_);
            return RowProxy(base_ + j * nz_, nz_);
        }
    private:
        T* base_;
        size_type ny_, nz_;
    };
    PlaneProxy operator[](size_type i) {
        assert(i < nx_);
        return PlaneProxy(data_.data() + i * (ny_ * nz_), ny_, nz_);
    }
    const PlaneProxy operator[](size_type i) const {
        assert(i < nx_);
        return PlaneProxy(data_.data() + i * (ny_ * nz_), ny_, nz_);
    }
    //c风格原始指针
    T* data() noexcept { return data_.data(); }
    const T* data() const noexcept { return data_.data();}
private:
    size_type nx_{0}, ny_{0}, nz_{0};
    std::vector<T> data_;

    size_type index(size_type i, size_type j, size_type k) const {
        return i * (ny_ * nz_) + j * nz_ + k;
    }
};
int main()
{
    Array3D<int> arr(4, 3, 2, 0); // 创建一个 4x3x2 的三维数组，初始值为 0

    // 使用函数调用式下标访问
    arr(1, 2, 0) = 42;
    std::cout << "arr(1, 2, 0) = " << arr(1, 2, 0) << std::endl;

    // 使用数组式下标访问
    arr[2][1][1] = 99;
    std::cout << "arr[2][1][1] = " << arr[2][1][1] << std::endl;

    // 拷贝构造（不涉及自赋值）
    Array3D<int> b = arr;
    std::cout << b(1, 2, 0) << " " << b[2][1][1] << "\n"; // 42 99

    // 拷贝赋值（需要自赋值保护）
    b = b;                     // 自赋值不应破坏数据
    std::cout << b(1, 2, 0) << " " << b[2][1][1] << "\n"; // 42 99
    return 0;
}
