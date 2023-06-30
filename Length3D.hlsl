Texture2D	g_texture : register(t0);
SamplerState	g_sampler : register(s0);

cbuffer global
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;
	float4		matLGT;
	float4		matLGTpos;

	float4 difcol;
	bool istex;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;
	float4 color : COLOR;
	//float Length : :
};

VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	normal = mul(normal, matW);

	float4 light = matLGTpos;

	float vecx = distance(matLGTpos.x , pos.x);
	float vecy = distance(matLGTpos.y, pos.y);
	float vecz = distance(matLGTpos.z, pos.z);

	float len =10.0 - pow(pow(vecx, 2) + pow(vecy, 2) + pow(vecz, 2), 0.5);

	light = normalize(light);
	outData.color = clamp(dot(normal, light) , 0 , 1);
	//outData.Length = len;

	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData ) : SV_Target
{
	float4 diffuse[2] = {matLGT  /*len */ * g_texture.Sample(g_sampler, inData.uv) * inData.color ,difcol * matLGT * inData.color * 3  /*len*/};
	float4 ambient[2] = { matLGT * g_texture.Sample(g_sampler, inData.uv) * float4(0.3, 0.3, 0.3, 0) , difcol * matLGT * float4(0.1, 0.1, 0.1, 0) };

	return diffuse[!istex] + ambient[!istex];
}