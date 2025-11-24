#include <vector>
#include <cstddef>
#include <cassert>
#include <iostream>

template <class T>
class Array3D {
public:
    using size_type = std::size_t;

    Array3D() = default;

    Array3D(size_type x, size_type y, size_type z, const T& init = T{})
        : nx_(x), ny_(y), nz_(z), data_(x * y * z, init) {}

    // --- 拷贝构造：深拷贝（对 std::vector 默认拷贝即可，这里显式写出以示意图）
    Array3D(const Array3D& other)
        : nx_(other.nx_), ny_(other.ny_), nz_(other.nz_), data_(other.data_) {}

    // --- 拷贝赋值：需要考虑自赋值（拷贝构造不需要）
    Array3D& operator=(const Array3D& other) {
        if (this == &other) return *this;     // 自赋值保护
        nx_ = other.nx_; ny_ = other.ny_; nz_ = other.nz_;
        data_ = other.data_;                  // vector 自带深拷贝
        return *this;
    }

    // --- 移动语义
    Array3D(Array3D&&) noexcept = default;
    Array3D& operator=(Array3D&&) noexcept = default;

    // 维度
    size_type dim_x() const noexcept { return nx_; }
    size_type dim_y() const noexcept { return ny_; }
    size_type dim_z() const noexcept { return nz_; }

    // --- 下标访问（方式一）：多参数调用 a(i,j,k)
    T& operator()(size_type i, size_type j, size_type k) {
        assert(i < nx_ && j < ny_ && k < nz_);
        return data_[index(i,j,k)];
    }
    const T& operator()(size_type i, size_type j, size_type k) const {
        assert(i < nx_ && j < ny_ && k < nz_);
        return data_[index(i,j,k)];
    }

    // --- 下标访问（方式二）：a[i][j][k]，通过代理类逐级返回
    class RowProxy {
    public:
        RowProxy(T* base, size_type nz) : base_(base), nz_(nz) {}
        T& operator[](size_type k)       { return base_[k]; }
        const T& operator[](size_type k) const { return base_[k]; }
    private:
        T* base_;
        size_type nz_;
    };

    class PlaneProxy {
    public:
        PlaneProxy(T* base, size_type ny, size_type nz)
            : base_(base), ny_(ny), nz_(nz) {}
        RowProxy operator[](size_type j) {
            // j-th row of this plane
            return RowProxy(base_ + j * nz_, nz_);
        }
        const RowProxy operator[](size_type j) const {
            return RowProxy(base_ + j * nz_, nz_);
        }
    private:
        T* base_;
        size_type ny_, nz_;
    };

    PlaneProxy operator[](size_type i) {
        assert(i < nx_);
        return PlaneProxy(data_.data() + i * ny_ * nz_, ny_, nz_);
    }
    const PlaneProxy operator[](size_type i) const {
        assert(i < nx_);
        return PlaneProxy(const_cast<T*>(data_.data()) + i * ny_ * nz_, ny_, nz_);
    }

    // 原始指针（如需与 C API 交互）
    T* data() noexcept { return data_.data(); }
    const T* data() const noexcept { return data_.data(); }

private:
    size_type index(size_type i, size_type j, size_type k) const noexcept {
        // 平铺索引：i-major（行主序）
        return i * (ny_ * nz_) + j * nz_ + k;
    }

    size_type nx_ = 0, ny_ = 0, nz_ = 0;
    std::vector<T> data_;
};

// ------------------- 演示 -------------------
int main() {
    Array3D<int> a(2,3,4, 0);
    a(1,2,3) = 42;             // 方式一
    a[0][1][2] = 7;            // 方式二

    // 拷贝构造（不涉及自赋值）
    Array3D<int> b = a;
    std::cout << b(1,2,3) << " " << b[0][1][2] << "\n"; // 42 7

    // 拷贝赋值（需要自赋值保护）
    b = b;                     // 自赋值不应破坏数据
    std::cout << b(1,2,3) << " " << b[0][1][2] << "\n"; // 42 7
}
