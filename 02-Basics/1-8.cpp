#include <map> 
#include <iostream>
int main()
{ 
    std::map<int, int> m; 
    m[0] = m.size();
    std::cout<<m[0];
}