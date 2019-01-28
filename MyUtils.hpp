#define print(arr, size) \
cout << "[ "; \
for (int i = 0; i < (size); i++) \
{ \
    if (i < (size) - 1) \
    { \
        cout << arr[i] << ", "; \
    } \
    else \
    { \
        cout << arr[i] << " ]" << endl; \
    } \
}

#include <iostream>
using namespace std;

template <class T>
void printArray(T arr, int size)
{
    cout << "[ ";
    for (int i = 0; i < (size); i++)
    {
        if (i < (size) - 1)
        {
            cout << arr[i] << ", ";
        }
        else
        {
            cout << arr[i] << " ]" << endl;
        }
    }
}

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long long   u64;
typedef signed char    i8;
typedef signed short   i16;
typedef signed int     i32; 
typedef float          r32;
typedef double         r64;
typedef long double    r128;
