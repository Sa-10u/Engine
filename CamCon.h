#pragma once
#include "Engine/GOBJ.h"
#include "Engine/CAM.h"
#include "Engine/DInput.h"

class CamCon : public GOBJ
{
public:
	CamCon(GOBJ* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Move();
	void Roll();

	XMVECTOR ray;
};

