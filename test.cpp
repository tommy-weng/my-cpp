#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

int main()
{
    cout << "Version: <--" << __VERSION__ << "--> " << endl;
    cout << "Cplusplus: <--" << __cplusplus << "-->" << endl;

    std::vector<int> v{ 1, 2, 3 };
    v.emplace_back(4);

    for_each(v.begin(), v.end(), [](int &i){
        cout << i << endl;
        });

    return 0;
}   

