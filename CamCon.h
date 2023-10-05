#pragma once
#include "Engine/GOBJ.h"
#include "Engine/CAM.h"
#include "Engine/DInput.h"

class CamCon : public GOBJ
{
public:
	CamCon(GOBJ* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void Move();
	void Roll();
	void SetPrem();

	void Shortcut();

	XMVECTOR ray;

	private:

	bool isSetting_;

	XMFLOAT3 prem_tgt;
	XMFLOAT3 prem_pos;

	XMFLOAT3 bef_tgt;
	XMFLOAT3 bef_pos;

	int count;

	void ToPrem();
};

