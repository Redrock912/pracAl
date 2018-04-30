// ��� ���� ����.
cbuffer CBPerObject
{
	matrix world;		// ���� ���.
	matrix view;		// �� ���.
	matrix projection;	// ���� ���.
};

// ��� ���� - ����Ʈ ����.
cbuffer CBLight
{
	float3 worldLightPosition;
	float3 worldCameraPosition;
};

// ���� �Է� ����ü.
struct VS_INPUT
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
};

Texture2D objTexture;
SamplerState objSampler;

// ���� ��� ����ü.
struct VS_OUTPUT
{	
	float4 pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float3 diffuse : TEXCOORD1;

	float3 viewDir : TEXCOORD2;
	float3 reflection : TEXCOORD3;
};

VS_OUTPUT VS_Main(VS_INPUT input)
{
	VS_OUTPUT output;
	//output.pos = input.pos;

	// ���� ��ȯ.
	// ���� ��ȯ.
	output.pos = mul(input.pos, world);

	// ����Ʈ ���� ���ϱ�.
	float3 lightDir = output.pos.xyz - worldLightPosition;
	// ���� ���ͷ� �����.
	lightDir = normalize(lightDir);

	// �� ���� ���ϱ�
	float3 viewDir = normalize(output.pos.xyz - worldCameraPosition);
	output.viewDir = viewDir;

	// �� ��ȯ.
	output.pos = mul(output.pos, view);
	// ���� ��ȯ.
	output.pos = mul(output.pos, projection);

	// �������� �Է¹��� �ؽ�ó ��ǥ ��ȯ.
	output.texCoord = input.texCoord;

	// ���� ��� ���ϱ�. (�츮 ī�޶� ��ġ�� ��������̱⶧����, �븻�� ���� �������� ���Ѵ�)
	float3 worldNormal 
		= mul(input.normal, (float3x3)world);
	// ���� ���ͷ� �����.
	worldNormal = normalize(worldNormal);

	// ��ǻ�� ��� (dot = ����).
	output.diffuse = dot(-lightDir, worldNormal);

	// �ݻ� ���� ���ϱ�  R = P + 2n(-P . n)
	//output.reflection = reflect(lightDir, worldNormal);

	// R = P + 2n(-P . n) ���� ���̶� ����
	output.reflection = lightDir + 2 * worldNormal * (dot(-lightDir,worldNormal));

	return output;
}

float4 PS_Main(VS_OUTPUT psInput) : SV_TARGET
{
	// 0���� �ڸ���.
	float3 diffuse = saturate(psInput.diffuse);

	// �����⸦ ��ģ ���� �ٽ� ����
	float3 reflection = normalize(psInput.reflection);
	float3 viewDir = normalize(psInput.viewDir);
	float3 specular = 0;

	if (diffuse.x > 0)
	{
		// ���÷��� ���Ϳ� �並 �����Ѵ�. ���� - �� ���ü������Ƿ� �ٽ� saturate���� ���ϰ��� ������. (0-1�� ����)
		specular = saturate(dot(reflection, -viewDir));
		// ���̰� ���� �� ��ġ ���� (���� ����, �� ����)
		specular = pow(specular, 20.0f);
	}


	// �ֺ���.
	float3 ambient = float3(0.1f, 0.1f, 0.1f);

	// diffuse ���� ��
	float3 diffuseColor = float3(1.0f, 0.0f, 0.0f);

	// ���� ����.
	return float4(diffuseColor * diffuse + ambient + specular, 1);
}