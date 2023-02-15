#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define DIV(a,b) (a/b)

int main()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    int a[] = {4,5,6};

    for (auto& i: a)
    {
        std::cout << i << std::endl;
    }

    std::for_each(v.begin(), v.end(), [](int &i){cout << i << endl;});   
    std::for_each(begin(a), end(a), [](int &i){cout << i << endl;});   
    return 0;
}   

