#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

int main()
{
    std::vector<int> v{ 1, 2, 3, 4 };

    for_each(v.begin(), v.end(), [](auto &i){
        cout << i << endl;
    });

    return 0;
}   

