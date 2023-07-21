Texture2D	g_texture : register(t0);
SamplerState	g_sampler : register(s0);
//max is 18
#define lights_ 10

cbuffer global
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;
	float4x4	matWV;
	float4		matLGT[lights_];
	float4		matLGTpos[lights_];

	float4 difcol;
	bool istex;
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float2 uv	: TEXCOORD;
	float4 color: COLOR;
	float4 capos: POSITION;
};

VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	outData.capos = pos;
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	normal = mul(normal, matW);
	outData.color = float4( 0,0,0,0 );

	float4 light[lights_];
	for (int i = 0; i < lights_; i++) {
		light[i] = matLGTpos[i];
		light[i] = normalize(light[i]);
	}
	
	for (int i = 0; i < lights_; i++) {
		outData.color += clamp(dot(normal, light[i]), 0, 1);
	}

	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 colors = (0,0,0,0);//
	int lenALL = 0;

	for (int i = 0; i < lights_; i++) {
		float len = (10) - length(matLGTpos[i].xyz - (mul(inData.capos, matW).xyz));
		len = clamp(len, 0, (10));

		lenALL += len;
		
	}

	lenALL = clamp(lenALL, 0, 2);

	float4 diffuse[2][3] = { {g_texture.Sample(g_sampler, inData.uv) * float4(0.3,0.3,0.3,1),	g_texture.Sample(g_sampler, inData.uv) * float4(0.8,0.5,0.5,1) ,g_texture.Sample(g_sampler, inData.uv) * float4(1,1,1,1)} , { difcol * float4(0,0,0,1),  difcol * float4(0.8,0.5,0.5,1),  difcol * float4(1,1,1,1)} };


	return diffuse[!istex][2 - lenALL];
}