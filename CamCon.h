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

	XMVECTOR ray;
};

