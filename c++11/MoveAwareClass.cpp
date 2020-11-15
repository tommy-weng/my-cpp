#include <iostream>
#include <string>
#include <cstring>
#include <vector>


using namespace std;

class MyString
{
public:
    MyString()
    {
        data_ = new char[100];
        len_ = 99;
        cout << "default ctor" << endl;
    }

    MyString(const MyString& str)
    :len_(str.len_)
    {
        data_ = new char[100];
        memcpy(data_, str.data_, str.len_);
        cout << "Copy ctor" << endl;
    }

    MyString(MyString&& str) noexcept
    :data_(str.data_), len_(str.len_)
    {
        str.data_ = nullptr;
        cout << "Move ctor" << endl;
    }

    MyString& operator=(MyString& str)
    {
        cout << "Copy asign" << endl;
        if (data_)
        {
            cout << "Copy asign delete" << endl; 
            delete data_;
        }

        data_ = new char[100];
        len_ = str.len_;
        memcpy(data_, str.data_, str.len_);
        return *this;
    }
    MyString& operator=(MyString&& str) noexcept
    {
        cout << "Move asign" << endl;
        if (data_)
        {
            cout << "Move asign delete" << endl;
            delete data_;
        }

        data_ = str.data_;
        len_ = str.len_;
        str.data_ = nullptr;
        str.len_ = 0;
        
        return *this;
    }

    ~MyString()
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
    vector<MyString> v;
    
    MyString dd;
    v.push_back(move(dd));
    return 0;
}   

