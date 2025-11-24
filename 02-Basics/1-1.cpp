#include <limits>
int main()
{
    int a = std::numeric_limits<int>::max();
    int b = a + 1;
    return 0;
}