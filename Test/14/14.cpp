#include <iostream>
using namespace std;


int BSearch(int* data, int begin, int end, int target)
{
	if (begin > end)
	{
		return -1;
	}
	else
	{
		int middle = (begin + end) / 2;
		if (data[middle] == target)
		{
			return middle;
		}
		else if (data[middle] > target)
		{
			return BSearch(data, begin, middle -1 , target);
		}
		else
		{
			return BSearch(data, middle+1,end, target);
		}
	}
}


int main()
{

	int data[10] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << BSearch(data, 0, 9, 4) << endl;
	return 0;
	
}
