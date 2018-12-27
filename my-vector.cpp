#include <iostream>
#include <vector>
//#include <algorithm>

using namespace std;

template <typename T>
class A
{
    public:
        typedef T *my_iter_t;

        A():pos(0), count(0)
        {
            m_p = new T[SIZE];	
        };

        void push(T v)
        {
            m_p[pos++] = v;

            if (0 == pos % SIZE)
            {
                count = pos / SIZE + 1;	
                temp = new T[SIZE * count];
                memcpy(temp, m_p, sizeof(T) * SIZE * (count -1));
                delete [] m_p;
                m_p = temp;
            }
        }

        int size(void)
        {
            return pos;	
        }
        my_iter_t begin(void)
        {
            if (pos > 0)
                return &m_p[0];
        }
        my_iter_t end(void)
        {
            if (pos > 0)
                return &m_p[pos-1];	
        }

        friend int &operator [](A<int> & a, int index);

    private:

        T *m_p;
        T *temp;
        int pos;
        int count;
        static const int SIZE = 10;
};
int &operator [](A<int> & a, int index)
{
    return a.m_p[index];	
}

A<int> v;

int arr[] = {272,363,44,55, 33, 44, 23};

int main(void)
{
    for (int i = 0; i < 100; i++)
    {
        v.push(3*i +5);
    }
    A<int>::my_iter_t it;

    cout << v[1]<< endl;
    return 0;
}
