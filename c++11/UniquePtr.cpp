#include <iostream>
#include <memory>

using namespace std;

class Data
{
public:
    Data()  { cout << "In ctor" << endl; }
    ~Data() { cout << "In dtor" << endl; }
};


int main()
{
    //unique_ptr<Data> uptr = make_unique<Data>();
    Data* data = new Data();
    unique_ptr<Data> uptr(data);
    //uptr.reset();  // will delete raw point and empty uptr
    //Data* p1 = uptr.release();  // will not delete raw point, just release and empty uptr
    //if (p1)
    //{
    //    cout << "p1 is not empty" << endl;
    //}
    Data* p2 = uptr.get();
    if (not p2)
    {
        cout << "p2 is empty" << endl;
    }

    unique_ptr<Data> uptr2(move(uptr));


    return 0;
}   

