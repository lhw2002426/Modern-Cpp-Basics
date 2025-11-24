#include<bits/stdc++.h>
using namespace std;
class Vector3
{
    public:
    float x, y, z;
    Vector3 (float x=0, float y=0, float z=0): x(x), y(y), z(z) {}
    [[nodiscard]]Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    // Vector3 operator+=(const Vector3& other) {
    //     x += other.x; y += other.y; z += other.z;
    //     return *this;
    // }
    [[nodiscard]]Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    [[nodiscard]]Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    [[nodiscard]]Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    std::partial_ordering operator<=>(const Vector3& other) const {
        if (auto cmp = x <=> other.x; cmp != 0) return cmp;
        if (auto cmp = y <=> other.y; cmp != 0) return cmp;
        return z <=> other.z;
    }
    
    friend ostream& operator<<(ostream& os, const Vector3& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;  // 返回流本身
    }
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    float magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }
    Vector3 normalize() const {
        float mag = magnitude();
        return Vector3(x / mag, y / mag, z / mag);
    }
};

[[nodiscard]]
Vector3 operator+(const Vector3& a, const Vector3 &b) //全局函数可以支持1+vec的操作，但是加上explicit后就不行了
{
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

int main()
{
    Vector3 vec; // (0, 0, 0)
    Vector3 vec2{1}; // (1, 0, 0)
    Vector3 vec3{1, 2}; //  (1, 2, 0)
    cout<< vec <<endl << vec2 << endl << vec3 << endl;
    // cout<<vec.x<<" "<<vec.y<<" "<<vec.z<<endl;
    // cout<<vec2.x<<" "<<vec2.y<<" "<<vec2.z<<endl;
    // cout<<vec3.x<<" "<<vec3.y<<" "<<vec3.z<<endl;
    cout<<1+vec<<endl;
    cout<<(1>vec2)<<endl;
    return 0;
}