// 상수 버퍼 선언
cbuffer CBPerObject
{
	matrix world;		// 월드 행렬
	matrix view;		// 뷰 행렬
	matrix projection;	// 투영 행렬
};

struct VS_INPUT
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

// 정점 출력 구조체.
struct VS_OUTPUT
{
	float4 pos : SV_POSITION; 
	//float pos: POSITION; 파이프라인에 데이터를 못보냄
	float4 color : COLOR;
};

VS_OUTPUT VS_Main(VS_INPUT input)
{
	VS_OUTPUT output;
	// 공간변환
	//output.pos = pos;

	// 월드 변환
	output.pos = mul(input.pos, world);
	// 뷰 변환
	output.pos = mul(output.pos, view);
	// 투영 변환
	output.pos = mul(output.pos, projection);

	output.color = input.color;

	return output;
}

float4 PS_Main(VS_OUTPUT psInput) : SV_TARGET
{
	//return float4(1.0f, 1.0f, 0.0f, 1.0f);
	return psInput.color.rgba;
}