#include <vector>
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& i : vec)
    {
        os << i << ' ';
    }
    return os;
}

int main()
{
    std::vector<int> v{1,2,3,4,5};
    std::cout << v << std::endl;
    
    return 0;
}
