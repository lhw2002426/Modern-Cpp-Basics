#include<bits/stdc++.h>
using namespace std;
enum class Color { Red, Green, Blue };

void PrintColor(Color color) {
    using enum Color;
    switch (color) {
        case Red:
            [[fallthrough]]; 
        case Green:
            cout << "hello\n";
            break;
        case Blue:
            cout << "world\n";
            break;
    }
}

int main() {
    PrintColor(Color::Red);    // Hello
    PrintColor(Color::Green);  // Hello
    PrintColor(Color::Blue);   // World
}