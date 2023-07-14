Texture2D	g_texture : register(t0);
SamplerState	g_sampler : register(s0);

//max is 18
#define lights_ 10

cbuffer global
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;
	float4x4	matWV;
	float4		matLGT[30];
	float4		matLGTpos[30];

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

	float4 light = matLGTpos[0];
	light = normalize(light);
	outData.color = clamp(dot(normal, light) , 0 , 1);

	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float len = length(matLGTpos[0].xyz - (mul(inData.capos,matW).xyz));
		
	float4 diffuse[2] = {(matLGT[0]  * g_texture.Sample(g_sampler, inData.uv) * inData.color) / len ,	(difcol * matLGT[0] * inData.color * 3) /len };
	float4 ambient[2] = {matLGT[0] * g_texture.Sample(g_sampler, inData.uv) * float4(0.3, 0.3, 0.3, 1) ,	difcol * matLGT[0] * float4(0.1, 0.1, 0.1, 1) };

	return (diffuse[!istex] )+ ambient[!istex];
}