#include<iostream>

using namespace std;

template <typename T>
void pop_sort(T a[], int size)
{
	for (int j = 0; j < size; j++)
	{
		int k = 0;
		for (int i = 0; i < size - j - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				T tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
				k = 1;
			}
		}
		if (0 == k)
		{
			break;	
		}
	}
}

template <typename T>
void sel_sort(T a[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (a[i] > a[j])
			{
				T tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}


int main(void)
{
	int aa[] = {2, 1, 3, 4, 5, 6, 8, 7};
	int size = sizeof(aa)/sizeof(int);
	pop_sort(aa, size);

	for (int i = 0; i < size; i++)
	cout <<  aa[i] << endl;

	return 0;
}
