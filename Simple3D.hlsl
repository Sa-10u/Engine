Texture2D	g_texture : register(t0);	
SamplerState	g_sampler : register(s0);

cbuffer global
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;
	float4		matLGT;

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
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD ,float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	normal = mul(normal, matW);

	float4 light = float4(0, 0.5, -0.7, 0);
	light = normalize(light); 
	outData.color = clamp(dot(normal, light), 0, 1);

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 diffuse[2] = {matLGT * g_texture.Sample(g_sampler, inData.uv) * inData.color , difcol};
	float4 ambient[2] = { matLGT * g_texture.Sample(g_sampler, inData.uv) * float4(0.3, 0.3, 0.3, 0) , difcol };

	return diffuse[istex] + ambient[istex];
}