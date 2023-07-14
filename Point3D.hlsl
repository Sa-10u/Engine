Texture2D	g_texture : register(t0);
SamplerState	g_sampler : register(s0);

//max is 18
#define lights_ 10

cbuffer global
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;
	float4x4	matWV;
	float4		matLGT[30];
	float4		matLGTpos[30];

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
	float4 color : COLOR;
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

	float4 light = matLGTpos[0];
	light = normalize(light);
	outData.color = clamp(dot(normal, light) , 0 , 1);

	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float len = length(matLGTpos[0].xyz - (mul(inData.capos,matW).xyz));
		
	float4 diffuse[2] = {(matLGT[0]  * g_texture.Sample(g_sampler, inData.uv) * inData.color) / len ,	(difcol * matLGT[0] * inData.color * 3) /len };
	float4 ambient[2] = {matLGT[0] * g_texture.Sample(g_sampler, inData.uv) * float4(0.3, 0.3, 0.3, 1) ,	difcol * matLGT[0] * float4(0.1, 0.1, 0.1, 1) };

	return (diffuse[!istex] )+ ambient[!istex];
}