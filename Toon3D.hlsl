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
	float4 capos: POSITION;
};

VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	outData.capos = pos;
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	normal = mul(normal, matW);

	float4 light = matLGTpos;
	light = normalize(light);
	outData.color = clamp(dot(normal, light), 0, 1);

	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float len = length(matLGTpos.xyz - (mul(inData.capos,matW).xyz));
	len = clamp(len,0,2.5);
	len = 2.5 - len;
	len = (int)(len *3);

	float4 diffuse[2] = {(matLGT * g_texture.Sample(g_sampler, inData.uv) * inData.color*len) ,	(difcol * matLGT * inData.color * 3 * len)};
	float4 ambient[2] = {matLGT * g_texture.Sample(g_sampler, inData.uv) * float4(0.3, 0.3, 0.3, 0) ,	difcol * matLGT * float4(0.1, 0.1, 0.1, 0) };

	return diffuse[!istex] + ambient[!istex];
}