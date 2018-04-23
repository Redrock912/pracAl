#include <iostream>
using namespace std;

void quicksort(int* data,int begin,int end)
{
	if (begin < end)
	{
		int pivot = begin;

		int min = begin ;
		for (int max = begin+1; max <= end; ++max)
		{
			if (data[pivot] > data[max])
			{
				min++;
				swap(data[min], data[max]);
			}
		}
		swap(data[pivot], data[min]);
		
		pivot = min;
		quicksort(data, begin, pivot - 1);
		quicksort(data, pivot + 1, end);
	}
}

int main()
{
	int data[] = { 10,3,64,7,11,36,34,17,29,24 };

	for (int i = 0; i < 10; i++)
	{
		cout << data[i] << ",";
	}
	cout << endl;

	quicksort(data, 0, 9);

	for (int i = 0; i < 10; i++)
	{
		cout << data[i] << ",";
	}
	cout << endl;

	return 0;
}