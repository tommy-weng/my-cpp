#include <iostream>
#include "MyUtils.hpp" 

using namespace std;

u32 binarySearchRoundDown(const u32 arr[], const u32 size, const u32 key)
{
  if ((key <= arr[0]) || (0 == size))
  {
    return 0;
  }
  if (key >= arr[size - 1])
  {
    return size - 1;
  }

  for (u32 low = 0, high = size - 1; low <= high;)
  {
    u32 mid = (low + high) / 2;
    if (key < arr[mid])
    {
      high = mid - 1;
      if (key >= arr[high])
      {
        return high;
      }
    }
    else if (key > arr[mid])
    {
      low = mid + 1;
      if (key < arr[low])
      {
        return mid;
      }
      else if (key == arr[low])
      {
        return low;
      }
    }
    else
    {
      return mid;
    }
  }
  return 0;
}

int main()
{
  u32 arr[] = {1, 3, 5, 7, 9, 15};
  
  cout << binarySearchRoundDown(arr, sizeof(arr)/sizeof(int), 16) << endl;
  
  return 0;
}


