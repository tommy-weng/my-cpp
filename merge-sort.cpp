#include <iostream>
#include <string.h>
using namespace std;

void print(int a[], int size)
{
  for (int i = 0; i < size; i++)
  {
    cout << a[i] << ' '; 
  }
  cout << endl;
}


void merge(int a[], int b, int m,int e)
{
  int temp[100] = {0};

  int p = b;
  int q = m;
  int i = 0;
  while ((p < m) || (q < e)) 
  {
    if ((p < m) && (q < e))
    {
      if (a[p] < a[q])
      {
        temp[i] = a[p];
        p++;
      }
      else
      {
        temp[i] = a[q];
        q++;
      }
    }
    else if (p == m)
    {
      temp[i] = a[q];
      q++;
    }
    else
    {
      temp[i] = a[p];
      p++;
    }

    i++;
  }

  memcpy(a + b, temp, (e - b) * sizeof(int));
}

void merge_sort(int a[], int b, int e)
{
  if ((e - b) <= 1)
  {
    return; 
  }
  int m = (b + e) / 2;
  merge_sort(a, b, m);
  merge_sort(a, m, e);
  merge(a, b, m, e);
}

int main()
{
  int arr[] = {5, 7, 4, 9, 3, 4, 6, 9};

  merge_sort(arr, 0, 8);

  print(arr, sizeof(arr)/sizeof(int));
  return 0;
}
