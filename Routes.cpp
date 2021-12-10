#include <iostream>

using namespace std;
using std::cout;
using std::endl;


template <int I>
auto tommy()
{
    // Do whatever you want
    return I;
}

template <int... ids>
struct Routes
{
    static void test(const int v)
    {
        cout << "default" << endl;
    }
};

template <int id, int... ids>
struct Routes<id, ids...>
{
    static void test(const int v)
    {
        if (v == id)
        {
            cout << tommy<id>() << endl;
        }
        else
        {
            Routes<ids...>::test(v);
        }
    }
};

int main()
{
    int v = 5;

    Routes<1,2,3,4>::test(v);

    return 0;
}
