#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class A
{
};

template<typename T>
class D
{
public:
    void operator ()(T*)
    {
        cout << "class delete" << endl;
    }    
};

template <typename T>
void del(T*)
{
    cout << "fun delele" << endl;
}

int main()
{
    A aa;
    std::unique_ptr<A, D<A>> pC{nullptr}; // deletor with class
    std::unique_ptr<A, void(*)(A*)> pF{nullptr, del<A>}; //deletor with function

    pC.reset(&aa);
    pF.reset(&aa);

    return 0;
}   

