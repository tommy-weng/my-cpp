#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

int binarySearch(std::vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (target < nums.at(mid))
        {
            right = mid - 1;
        }
        else if (target > nums.at(mid))
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

int binarySearch_left(std::vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left < right)
    {
        int mid = (left + right) / 2;
        if (target <= nums.at(mid))
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return right;
}

int binarySearch_right(std::vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left < right)
    {
        int mid = (left + right + 1) / 2; // +1 is to avoid infinite loop
        if (target >= nums.at(mid))
        {
            left = mid;
        }
        else
        {
            right = mid - 1;
        }
    }

    return right;
}

int main()
{
    std::vector<int> v{ 1, 2, 3, 3, 3, 4, 5};

    cout << binarySearch(v, 3) << endl;
    cout << binarySearch_left(v, 3) << endl;
    cout << binarySearch_right(v, 3) << endl;

    return 0;
}   

