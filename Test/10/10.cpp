#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>

using namespace std;

char Infix[] = "2 + 4 * ( 4 - 2 ) - 3";
char Operators[] = "+-/*()";
int OperatorPriority[] = { 1, 1, 2, 2, -1, -1 };

stack<char*> PostFixStack;

int IsOperator(char ch)
{
	for (int i = 0; i < (int)strlen(Operators); ++i)
	{
		if (ch == Operators[i])
		{
			return i; // ������ �迭 ��ġ
		}
	}

	return -1; //�����ڰ� �ƴϸ� -1
}

//�迭 ��ġ�� ���� ������ �켱���� ��������
int GetPriority(char* Operator)
{
	return OperatorPriority[IsOperator(Operator[0])];
}


///
//1. ����ǥ����� ó�� �� ������ �б�
//2 - 1 ����(�ǿ�����) ���
//2 - 2 ������(+-*/ ) ���� Push
//2 - 2 - 1 ���� �������� �켱������ ����� �������� �켱�������� ���ų� ������ �� ������(POP) ���
//2 - 2 - 2 ���� ��ȣ��('(') ������ Push
//2 - 2 - 3 �ݴ� ��ȣ��(')') ������ ���� ��ȣ�� ���ö� ���� POP �ϰ� �ݴ� ��ȣ, ���� ��ȣ�� ����
//3 ����ǥ��� ���� �� �о����� ���ÿ� �ִ°� �� ������ ���
//4. ���ÿ� �� ������ ��� ���
char* OperatorProcess(char* Operator, char* Cursor)
{
	if ((PostFixStack.size() == 0) || Operator[0] == '(') //ù �����ڸ� ������ Ǫ��
	{
		PostFixStack.push(Operator);
	}
	else //ù �����ڰ� �ƴϸ� 
	{
		char* Top = PostFixStack.top(); //�� �� ������ Ȯ��
										 //���� ó�� �ϴ� �������� �켱�������� ���ų� ������ ���
		while (!(PostFixStack.size() == 0) && GetPriority(Top) >= GetPriority(Operator))
		{
			PostFixStack.pop(); // �׳� ������, �̹� �� ���� �����ڴ� �˰� ����.
			if (Top[0] == '(')
			{
				break;
			}
			//printf("%s ", Top);
			sprintf(Cursor, "%s ", Top);
			Cursor += (strlen(Top) + 1);

			if (!(PostFixStack.size() == 0))
			{
				Top = PostFixStack.top(); //������ �� ������ ã�ƿ���
			}
		}
		//���� ó�� �ϴ� ������ Ǫ��
		if (Operator[0] != ')')
		{
			PostFixStack.push(Operator);
		}
	}

	return Cursor;
}

char* ConvertPostFix(char* InfixNotation)
{

	//���� ����� ��������� ���� �迭
	char* PostFixString = new char[strlen(InfixNotation) + 1];
	//���� ��� ���� ��ġ Ŀ��
	char* Cursor = PostFixString;

	//���� ǥ��� �߶� �о� ����(�Ľ�)
	char* token = strtok(InfixNotation, " ");
	while (token != NULL)
	{
		if (token[0] >= '0' && token[0] <= '9') // ���� �϶� ó��, ���
		{
			//printf("%s ", token);
			sprintf(Cursor, "%s ", token);
			Cursor += (strlen(token) + 1);
		}
		else if (IsOperator(token[0]) != -1) //������ ó��, ���ÿ� Ǫ��(����)
		{
			Cursor = OperatorProcess(token, Cursor);
		}


		token = strtok(NULL, " ");
	}

	//���ÿ� ���� �ִ� ������ ��� ���
	while (!(PostFixStack.size() == 0))
	{
		char* Pop = PostFixStack.top();
		PostFixStack.pop();
		sprintf(Cursor, "%s ", Pop);
		Cursor += (strlen(Pop) + 1);
	}

	//���ڿ� �� �ڴ� '\0'
	sprintf(Cursor, "\0");

	return PostFixString;
}

double PostFixCalculate(char* PostFixString)
{
	stack<char*> PostFixCal;
	

	//����ǥ��� �Ľ�
	char* token = strtok(PostFixString, " ");
	while (token != NULL)
	{
		if (token[0] >= '0' && token[0] <= '9') // ���� �϶� ó��
		{
			PostFixCal.push(token); //���ڴ� ������ ���ÿ� Ǫ��
		}
		else if (IsOperator(token[0]) != -1) //������ ó��
		{
			char* second = PostFixCal.top(); //���� �ι�° ������
			PostFixCal.pop();
			char* first = PostFixCal.top(); //���� ù��° ������
			PostFixCal.pop();

											//���� ó��
			double result = 0;
			switch (token[0])
			{
			case '+':
				result = atof(first) + atof(second);
				break;
			case '-':
				result = atof(first) - atof(second);
				break;
			case '/':
				result = atof(first) / atof(second);
				break;
			case '*':
				result = atof(first) * atof(second);
				break;
			}
			//���� ��� ���� Ǫ��
			char* temp = new char[10];
			sprintf(temp, "%f", result);
			PostFixCal.push(temp);
		}

		token = strtok(NULL, " ");
	}

	//�������� ����� ����� ���
	char* Final = PostFixCal.top();
	PostFixCal.pop();
	

	return atof(Final);
}


int main()
{
	
	char* PostFixString = ConvertPostFix(Infix);
	printf("%f\n", PostFixCalculate(PostFixString));

	return 0;
}