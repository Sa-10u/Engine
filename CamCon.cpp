#include "CamCon.h"

CamCon::CamCon(GOBJ* parent):GOBJ(parent,"CamCon")
{
}

void CamCon::Initialize()
{
	trans.pos = { 0,3,-10 };
	ray = { 0,0,1.0 ,0};
}

void CamCon::Update()
{
	CAM::SetPosition(trans.pos);
	CAM::SetTarget(ray);

	Move();
}

void CamCon::Draw()
{
}

void CamCon::Release()
{
}

void CamCon::Move()
{
	static XMFLOAT3 temp;

	if (Input::IsKey(DIK_W)) 
	{
		XMStoreFloat3(&temp, ray);

		trans.pos = trans.pos+temp;
		ray = (XMLoadFloat3(&temp));
	}
	if (Input::IsKey(DIK_A))
	{}
	if (Input::IsKey(DIK_S))
	{}
	if (Input::IsKey(DIK_D)) 
	{
	}
}

void CamCon::Roll()
{
}
