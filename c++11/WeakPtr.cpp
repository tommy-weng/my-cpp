#include <iostream>
#include <memory>

using namespace std;

class B;

class A
{
public:
    std::shared_ptr<B> pb;
    ~A()
    {
        cout << "A dtor" << endl;
    }
};

class B
{
public:
    std::weak_ptr<A> pa;
    //std::shared_ptr<A> pa;
    ~B()
    {
        cout << "B dtor" << endl;
    }
};

int main() {

    std::weak_ptr<A> wa;
    {
        std::shared_ptr<A> aa = std::make_shared<A>();
        std::shared_ptr<B> bb = std::make_shared<B>();
        aa->pb = bb;
        bb->pa = aa;
        //bb->pa.reset();
        
        wa = bb->pa;
        cout << wa.use_count() << endl;
    }
    
    cout << wa.use_count() << endl;

  return 0;
}
