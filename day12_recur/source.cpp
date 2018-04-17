#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<int> a;

int add(int num)
{
	int sum = 0;
	for (int i = 1; i <= num; i++)
	{
		sum += i;
	}
	return sum;
}

int AddRecur(int num)
{
	if (num == 1)
		return 1;

	return num + AddRecur(num - 1);
}

int NormalArraySum(int* data, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += data[i];
	}

	return sum;
}

int ArraySumRecur(int* data, int size)
{
	if (size == 0)
	{
		return 0;
	}
	return data[size-1]+ ArraySumRecur(data, size-1);
}

int IterStringLength(string str)
{
	int i = 0;
	while (str.substr(i) != "\0")
	{
		i++;
	}

	return i;
}

int RecurStringLength(string str)
{
	if (str.empty())
		return 0;
	
	//str.pop_back();
	//return 1 + RecurStringLength(str);

	return 1 + RecurStringLength(str.substr(1));
}

void IterReveresePrint(string str) 
{
	for (int i = str.length()-1; i >= 0; --i)
	{
		//cout << str[i];
		cout << str.substr(i, 1);
	}
	cout << endl;
}


void RecurReversePrint(string str)
{
	//if (str.length() != 0)
	//{
	//	cout << str.back(); 
	//	str.pop_back(); 
	//	RecurReversePrint(str);
	//}
	//else
	//{
	//	cout << endl;
	//}

	if (str.length() == 0)
	{
		cout << endl;
		return;
	}

	RecurReversePrint(str.substr(1)); // cout ���� ���� �����Ƿ�, ����ؼ� ���������� Ž���ϰ� ���������� �������ʴ�� ó����(������ ��) �� ��µȴ�.
	cout << str[0];
}

//2���� ���
stack<int> Binary;
void IterBinaryPrint(int n)
{
	int bin = n;
	
	while (bin / 2 != 0)
	{
		Binary.push(bin % 2);
		bin /= 2;

	}
	Binary.push(bin % 2);

	while (!Binary.empty())
	{

		cout << Binary.top();
		Binary.pop();
	}
	cout << endl;

	// ������ ������� ���� ���, �Ųٷ� ������ִ� ���� �Լ��� ����.
}

void RecurBinaryPrint(int n)
{
	if (n == 0)
	{
		return;
	}
	RecurBinaryPrint(n / 2);
	cout << n % 2;
}

//���丮�� ���

int IterFactorial(int n)
{
	int sum = 1;
	for (int i = 1; i <= n; i++)
	{
		sum *= i;
	}

	return sum;
}

int RecurFactorial(int n)
{
	if (n == 0)
		return 1;
	return n * RecurFactorial(n - 1);
}

// �迭 Ž��

int IterArraySearch(int* data,int n, int target)
{
	for (int i = 0; i < n; i++)
	{
		if (data[i] == target)
		{
			return i;
		}
	}

}

int RecurArraySearch(int* data, int n, int target)
{
	if (target == data[n])
	{
		return n;
	}
	else if(n>=1)
	{
		RecurArraySearch(data, n - 1, target);
	}
	//else
	//{
	//	cout << "No Answer" << endl;
	//	return -1;
	//}
}

int RecurArraySearch2(int* data, int begin, int end, int target)
{
	if (begin > end)
		return -1;

	if (data[begin] == target)
		return begin;

	RecurArraySearch2(data, begin + 1, end, target);
}

int RecurArraySearch3(int* data, int begin, int end, int target)  // �̰� ���� �ȵ��־ �������, ��� 2�� �ٸ��� ����.
{
	if (begin > end)
		return -1;

	int middle = (begin + end) / 2;
	if (data[middle] == target)
	{
		return middle;
	}
	int index = RecurArraySearch3(data, begin, middle - 1, target);
	if (index != -1) // �� �κп��� ������ �״�� ���
	{
		return index;
	}
	else // �տ� ���ٸ� �ڷ� �˻�
	{
		RecurArraySearch3(data, middle + 1, end, target);
	}


}

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
	//cout << add(10) << endl;
	//cout << AddRecur(10) << endl;

	//cout << NormalArraySum(data,10) << endl;
	//cout << ArraySumRecur(data, 10) << endl;

	//string str = "Hello asdf";
	//cout << str.substr(3) << endl;

	//cout << IterStringLength(str) << endl;
	//cout << RecurStringLength(str) << endl;
	//RecurReversePrint(str);
	//IterReveresePrint(str);

	int num = 9;

	IterBinaryPrint(num);
	RecurBinaryPrint(num);
	cout << endl;
	cout << IterFactorial(num) << endl;
	cout << RecurFactorial(num) << endl;

	cout << IterArraySearch(data, 10, 6) << endl;
	cout << RecurArraySearch(data, 10, 2) << endl;
	cout << RecurArraySearch2(data, 0, 9, 11) << endl;
	cout << RecurArraySearch3(data, 0, 9, 8) << endl;
	cout << BSearch(data, 0, 9, 4) << endl;
	return 0;
	
}