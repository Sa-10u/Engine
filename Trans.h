#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Trans
{
public:
	XMFLOAT3 pos;	//位置
	XMFLOAT3 rot;	//向き
	XMFLOAT3 size;	//拡大率

	//コンストラクタ
	Trans();

	//デストラクタ
	~Trans();

	//各行列の計算
	void Calc();

	//ワールド行列を取得
	XMMATRIX GetWorldMatrix();
	XMMATRIX GetNormalMatrix();

private:
	XMMATRIX matgra;
	XMMATRIX matrot;
	XMMATRIX matsc;

	XMMATRIX mat;
};

