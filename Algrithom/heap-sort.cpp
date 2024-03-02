#include <iostream>
#include <string.h>
#include "MyUtils.hpp"

using namespace std;

void big_head(int arr[], int b, int e)
{
    for (int i = e - 1; i >= 0; i--)
    {
        int lpos = 2 * i + 1;
        int rpos = 2 * i + 2;
        int& curr = arr[i];
        if (lpos < e)
        {
            int& left = arr[lpos];
            if (left > curr)
            {
                swap(curr, left);
            }
        }
        if (rpos < e)
        {
            int& right = arr[rpos];
            if (right > curr)
            {
                swap(curr, right);
            }
        }
    }
}

void heap(int arr[], int b, int e)
{
    for (int i = e; i > 0; i--)
    {
        big_head(arr, b, i);
        swap(arr[b], arr[i - 1]); 
    }
}

int main()
{
    int arr[] =     {5, 7, 4, 9, 3, 4, 6, 9, 0};
    int size = sizeof(arr)/sizeof(int);
    print(arr, size);
    heap(arr, 0, size);
    print(arr, size);
    return  0;
}

        
