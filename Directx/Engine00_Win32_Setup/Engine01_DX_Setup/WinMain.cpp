#include <Windows.h> // ������ ������
#include "Engine.h"


int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE previnstance, // ����� �Ⱦ���
	LPSTR lpCmdLine, // �ܼ�â���� parameter �ѱ�� �뵵
	int nCmdline) // ������â�� ���� parameter
{
	//�׽�Ʈ �뵵
	//MessageBox(NULL, "�׽�Ʈ â ����","�ƾ�", MB_OK); // �պκ��� ������ �ڵ� ���� ����. ������ parameter�� go to definition���� �� ���� �͵� Ȯ�� ����.

	// Engine �ν��Ͻ� ����
	Engine engine(hinstance);

	//�ʱ�ȭ
	if (engine.Init() == false)
	{
		return 0;
	}

	//���� ����
	return engine.Run();
}