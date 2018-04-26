#include "Engine.h"
#include <d3d11.h>

Engine::Engine(HINSTANCE hinstance) 
	: DXApp(hinstance)
{

}

Engine::~Engine()
{
	
}

bool Engine::Init()
{
	if (DXApp::Init() == false)
		return false;

	return true;
}
// ȸ�� ���� �����, dx������ ȸ������ ������ �����Ƿ� �������Ѽ� ����ϰ� �ʹٸ� ���� ������ �����ؾ� �ȴ�
float rot = 0.0f;

void Engine::Update()
{
	// ȸ�� ���� ����
	rot += 0.00005; 
	if (rot > 3.14f*2.0f)
		rot = 0.0f;

	// ȸ�� ���
	XMMATRIX rotation = XMMatrixRotationY(rot);
	// �̵� ���
	XMMATRIX translation = XMMatrixTranslation(3.0f, 1.0f, 0.0f);
	// ������ ���
	XMMATRIX scale = XMMatrixScaling(3.0f, 1.5f, 1.0f);
	
	world = XMMatrixIdentity();
	world = scale* rotation * translation;  // SRT ��ȯ��Ģ�� �����ȵ� S * R * T �� 
	
	//world *= rotation;

	// ���̴� ������ۿ� ������ ������ ����
	CBPerObject cbData;
	cbData.world = XMMatrixTranspose(world);
	cbData.view = XMMatrixTranspose(view);
	cbData.projection = XMMatrixTranspose(projection);

	// ��� ���� ���� ����
	pDeviceContext->UpdateSubresource(cbBuffer, 0, 0, &cbData, 0, 0); 

	// ���������� ���ε�
	pDeviceContext->VSSetConstantBuffers(0, 1, &cbBuffer);
}

void Engine::Render()
{
	// ��� �����. (����� �����).
	float color[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// ���� �׸���.
	//pDeviceContext->Draw(3, 0);
    //	pDeviceContext->DrawIndexed(6, 0, 0); // ��� ������, ��𼭺��� ������
	pDeviceContext->DrawIndexed(nIndices, 0, 0);

	// ���� ��ü. (����� <-> ����Ʈ����).
	pSwapChain->Present(0, 0);
}
