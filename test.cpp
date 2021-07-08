#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

void version()__attribute__((constructor));
void version()
{
    cout << "Version <--" << __VERSION__ << "--> " << "Cplusplus <--" << __cplusplus << "-->" << endl;
}

int main()
{
    std::vector<int> v{ 1, 2, 3 };
    v.emplace_back(4);

    for_each(v.begin(), v.end(), [](auto &i){
        cout << i << endl;
    });

    return 0;
}   

