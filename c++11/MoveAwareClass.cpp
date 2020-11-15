#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <bitset>
#include <tuple>
#include <algorithm>

using namespace std;

void foo(int& a)
{
    cout << "int& a" << endl;
}

void foo(int&& a)
{
    cout << "int&& a" << endl;
}

class Data
{
public:
    Data()
    {
        data_ = new char[100];
        len_ = 99;
        cout << "default ctor" << endl;
    }

    Data(const Data& data)
    :len_(data.len_)
    {
        data_ = new char[100];
        memcpy(data_, data.data_, data.len_);
        cout << "Copy ctor" << endl;
    }

    Data(Data&& data)
    :data_(data.data_), len_(data.len_)
    {
        data.data_ = nullptr;
        cout << "Move ctor" << endl;
    }

    Data& operator=(Data& data)
    {
        cout << "Copy asign" << endl;
        if (data_)
        {
            cout << "Copy asign delete" << endl; 
            delete data_;
        }

        data_ = new char[100];
        len_ = data.len_;
        memcpy(data_, data.data_, data.len_);
        return *this;
    }
    Data& operator=(Data&& data)
    {
        cout << "Move asign" << endl;
        if (data_)
        {
            cout << "Move asign delete" << endl;
            delete data_;
        }

        data_ = data.data_;
        len_ = data.len_;
        data.data_ = nullptr;
        data.len_ = 0;
        
        return *this;
    }

    ~Data()
    {
        cout << "dtor" << endl;
        if (data_)
        {
            cout << "delete" << endl;
            delete data_;
        }

    }
private:
    char* data_;
    size_t len_;

};

int main()
{
    vector<Data> v;
    
    Data dd;
    v.push_back(move(dd));
    return 0;
}   

