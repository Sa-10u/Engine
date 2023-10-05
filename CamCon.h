#pragma once
#include "Engine/GOBJ.h"
#include "Engine/CAM.h"
#include "Engine/DInput.h"

class CamCon : public GOBJ
{
public:
	CamCon(GOBJ* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
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

