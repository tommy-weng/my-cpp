#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

template <int... Us>
class A
{
public:
    A()
    {
        cout << "Origin" << endl;
    }

    template <int... Vs>
    A& push()
    {
        (v.push_back(Us),...);
        (v.push_back(Vs),...);
        return *this;
    }
    void print()
    {
        for_each(v.begin(), v.end(), [](auto& i){
            cout << i << endl;
        });
    }
private:
    std::vector<int> v;
};

int main()
{

    A<1,2,3,4>{}.push<5,6>().print();
    return 0;
}   

