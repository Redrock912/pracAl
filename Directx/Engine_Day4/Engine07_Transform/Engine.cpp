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
// 회전 각도 저장용, dx에서는 회전축이 변하지 않으므로 누적시켜서 계산하고 싶다면 따로 변수를 저장해야 된다
float rot = 0.0f;

void Engine::Update()
{
	// 회전 각도 변경
	rot += 0.00005; 
	if (rot > 3.14f*2.0f)
		rot = 0.0f;

	// 회전 행렬
	XMMATRIX rotation = XMMatrixRotationY(rot);
	// 이동 행렬
	XMMATRIX translation = XMMatrixTranslation(3.0f, 1.0f, 0.0f);
	// 스케일 행렬
	XMMATRIX scale = XMMatrixScaling(3.0f, 1.5f, 1.0f);
	
	world = XMMatrixIdentity();
	world = scale* rotation * translation;  // SRT 교환법칙이 성립안됨 S * R * T 로 
	
	//world *= rotation;

	// 셰이더 상수버퍼에 전달할 데이터 설정
	CBPerObject cbData;
	cbData.world = XMMatrixTranspose(world);
	cbData.view = XMMatrixTranspose(view);
	cbData.projection = XMMatrixTranspose(projection);

	// 상수 버퍼 내용 갱신
	pDeviceContext->UpdateSubresource(cbBuffer, 0, 0, &cbData, 0, 0); 

	// 파이프라인 바인딩
	pDeviceContext->VSSetConstantBuffers(0, 1, &cbBuffer);
}

void Engine::Render()
{
	// 배경 지우기. (백버퍼 지우기).
	float color[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	// 정점 그리기.
	//pDeviceContext->Draw(3, 0);
    //	pDeviceContext->DrawIndexed(6, 0, 0); // 몇개를 읽을지, 어디서부터 읽을지
	pDeviceContext->DrawIndexed(nIndices, 0, 0);

	// 버퍼 교체. (백버퍼 <-> 프론트버퍼).
	pSwapChain->Present(0, 0);
}
