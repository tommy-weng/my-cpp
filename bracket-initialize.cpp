// Example program
#include <iostream>
#include <vector>
//#include <initializer_list>

using namespace std;

class MyData
{
public:
    MyData & operator [] (initializer_list<int> list)
    {
        for (auto i = list.begin(); i != list.end(); ++i)
        {
            idx.push_back(*i);
        }
        return *this;
    }
    
    MyData & operator = (int v)
    {
        if (true != idx.empty())
        {
            for (auto i = idx.begin(); i != idx.end(); ++i)
            {
                d.resize((*i > d.size()) ? *i : d.size());
                d[*i - 1] = v;
            }
            
            idx.clear();
        }
        
        return *this;
    }
    
    void print()
    {
        for (auto i = d.begin(); i != d.end(); ++i)
        {
            cout << *i << " ";
        }
        cout << endl;
    }
    
private:
    vector<int> idx;
    vector<int> d;
};

int main()
{
    MyData dd;
    dd[{2, 3, 5}] = 7;
    dd[{1, 4, 5, 8}] = 4;
    dd.print();
}