Texture2D	g_texture : register(t0);
SamplerState	g_sampler : register(s0);

cbuffer global
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;
	float4x4	matWV;
	float4		matLGT;
	float4		matLGTpos;

	float4 difcol;
	bool istex;
};
