#include <iostream>

using namespace std;
void swap(int& a, int& b)
{
    a += b;
    b = a - b;
    a = a - b;
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << '\n';
}
int partition(int a[], int b, int e)
{
    int& key = a[b];
    int i = 1 + b;
    int j = e - 1;
    while (i < j)
    {
        if (a[i] > a[j])
        {
            swap(a[i], a[j]);
        }
        if (a[i] <= key)
        {
            i++;
        }

        if (a[j] > key)
        {
            j--; 
        }
        
    }

    if (a[i] > key)
    {
        i--;
    }

    if (i != b)
    {
        swap(key, a[i]);
    }

    return i;
}

void quick_sort(int a[], int b, int e)
{
    if (e - b <= 1)
    {
        return; 
    }
    //cout << "..........................." << endl;
    //print_array(&a[b], e-b);
    int key = partition(a, b, e);
    //cout << key << endl;
    //print_array(&a[b], e-b);
    quick_sort(a, b, key);
    quick_sort(a, key + 1, e);
}

int main()
{
    //int arr[] = {6, 2, 95, 7, 4, 9, 5, 8, 1, 5, 6, 8, 7, 9, 7};
    int arr[] = {2, 3};
    int size = sizeof(arr)/sizeof(int);
    quick_sort(arr, 0, size);
    //partition(arr, 0, size);
    print_array(arr, size);
    return 0;
}
