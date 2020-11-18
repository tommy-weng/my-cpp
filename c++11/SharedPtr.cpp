#include <iostream>
#include <memory>

using namespace std;

void test1()
{
    //shared_ptr<int> sptr(new int(8));
    shared_ptr<int> sptr = make_shared<int>(8);
    //shared_ptr<int> sptr;
    //shared_ptr<int> sptr2;
    //sptr2 = sptr;
    shared_ptr<int> sptr2(sptr);

    if (sptr)
    {
        cout << "value=" << *sptr << endl;
    }

    cout << "sptr::count=" << sptr.use_count() << endl;
    cout << "sptr2::count=" << sptr2.use_count() << endl;
    sptr.reset();
    cout << "sptr::count=" << sptr.use_count() << endl;
    cout << "sptr2::count=" << sptr2.use_count() << endl;
}

class Data
{
public:
    Data() { cout << "In Data Ctor" <<endl;}
    ~Data() { cout << "In Data Dtor" <<endl;}
};

void deleter(Data* d)
{
    cout << "In deleter" << endl;
    delete[] d;
}

class Deleter
{
public:
    Deleter() { cout << "In Deleter Ctor" << endl;}
    ~Deleter() { cout << "In Deleter Dtor" << endl;}
    void operator ()(Data* d)
    {
        cout << "In Deleter operator()" << endl;
        delete[] d;
    }
};

void test2()
{
    //deleter
    //shared_ptr<Data> sptr(new Data[3], deleter);
    //shared_ptr<Data> sptr(new Data[3], Deleter());
    shared_ptr<Data> sptr(new Data[3], [](Data* d) {
        cout << "In lamda deleter" << endl;
        delete[] d;
    });
    

}

int main()
{
     test2(); 

    return 0;
}   

