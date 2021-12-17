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
struct Router
{
    static void test(const int v)
    {
        cout << "default" << endl;
    }
};

template <int id, int... ids>
struct Router<id, ids...>
{
    static void test(const int v)
    {
        if (v == id)
        {
            cout << tommy<id>() << endl;
        }
        else
        {
            Router<ids...>::test(v);
        }
    }
};

int main()
{
    int v = 5;

    Router<1,2,3,4>::test(v);

    return 0;
}
