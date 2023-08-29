#pragma once
#include "D3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace CAM
{
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position);
	void SetPosition(XMFLOAT3 position);
	XMVECTOR GetPosition();

	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target);
	void SetTarget(XMFLOAT3 target);
	XMVECTOR GetTarget();

	void SetFOV(float fov);
	float GetFOV();

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();

	extern XMVECTOR pos_;
	extern XMVECTOR tgt_;
	extern XMMATRIX viewMat_;
	extern XMMATRIX projMat_;
};