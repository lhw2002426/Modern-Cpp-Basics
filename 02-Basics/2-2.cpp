#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    // 1. 列表初始化：直接初始化一个std::vector
    std::vector<int> v{1, 2, 3, 4, 5}; // 列表初始化
    cout << "Vector: ";
    for (int num : v) {
        cout << num << " ";
    }
    cout << endl;

    // 2. 值初始化：使用空的花括号来进行值初始化
    int a{}; // 使用空的花括号进行值初始化，a 会被初始化为 0
    cout << "a (value initialized): " << a << endl;

    // 3. 聚合初始化：直接使用花括号初始化结构体或类成员
    struct Point {
        int x, y;
    };

    // 聚合初始化：指定成员的值
    Point p1{10, 20}; // 成员 x 被初始化为 10，y 被初始化为 20
    cout << "Point p1: (" << p1.x << ", " << p1.y << ")" << endl;

    // 4. 使用统一初始化初始化 std::map
    std::map<int, std::string> m{{1, "apple"}, {2, "banana"}, {3, "cherry"}};
    cout << "Map: ";
    for (const auto& pair : m) {
        cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    cout << endl;

    // 5. 使用统一初始化初始化 std::unordered_map
    std::unordered_map<int, std::string> um{{1, "dog"}, {2, "cat"}, {3, "rabbit"}};
    cout << "Unordered Map: ";
    for (const auto& pair : um) {
        cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    cout << endl;

    return 0;
}
