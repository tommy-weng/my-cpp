#include <iostream>

using namespace std;

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << '\n';
}


void quick_sort(int a[], int low, int high)
{
    if (low < high)
    {
        int key = a[low];
        int i = low;
        int j = high;
        while (i < j)
        {
            while (i < j and a[j] >= key) j--;
            if (i < j) a[i++] = a[j];
            while (i < j and a[i] <= key) i++;
            if (i < j) a[j--] = a[i];
        }
        a[i] = key;
        quick_sort(a, low, i - 1);
        quick_sort(a, i + 1, high);
    }
}

int main()
{

    int arr[] = {6, 2, 95, 7, 4, 9, 5, 8, 0, 5, 6, 8, 7, 9, 7};
    int size = sizeof(arr)/sizeof(int);
    quick_sort(arr, 0, size - 1);
    print_array(arr, size);
    return 0;
}
