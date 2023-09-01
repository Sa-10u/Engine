#include "CamCon.h"
#include"Engine/CAM.h"
#include "Engine/Trans.h"

CamCon::CamCon(GOBJ* parent):GOBJ(parent,"CamCon")
{
}

void CamCon::Initialize()
{
	ray = CAM::GetTarget();
	trans.rot.x = -0.4;

	XMFLOAT3 temp = { 6.5,5,-7 };
	CAM::SetPosition(temp);
	CAM::SetTarget(XMLoadFloat3(&temp) + CAM::GetPosition());
}

void CamCon::Update()
{
	Move();
	Roll();
}

void CamCon::Draw()
{
}

void CamCon::Release()
{
}

void CamCon::Move()
{
	XMVECTOR way;
	way = CAM::GetTarget() - CAM::GetPosition();
	way = XMVector3Normalize(way);

	static double pie_ = 3.141592;

	float val = 0.1;

	if (Input::IsKey(DIK_W)) 
	{
		CAM::SetPosition(CAM::GetPosition() + way * val);
		CAM::SetTarget(CAM::GetTarget() + way * val);
	}
	if (Input::IsKey(DIK_A))
	{
		XMMATRIX mat =
		{
		cosf(pie_ / 2), 0,               -sinf(pie_ / 2),  0,
		0,				1,               0,                0,
		sinf(pie_ / 2), 0,               cosf(pie_ / 2) ,  0,
		0,				0,               0,                1
		};
		auto Temp = XMVector3TransformCoord(way, mat);
		XMFLOAT3 fvec;
		XMStoreFloat3(&fvec, Temp);

		fvec.y = 0;
		Temp = XMLoadFloat3(&fvec);
		XMVector3Normalize(Temp);

		CAM::SetPosition(CAM::GetPosition() - Temp * val);
		CAM::SetTarget(CAM::GetTarget() - Temp * val);
	}
	if (Input::IsKey(DIK_S))
	{
		CAM::SetPosition(CAM::GetPosition() - way * val);
		CAM::SetTarget(CAM::GetTarget() - way * val);
	}
	if (Input::IsKey(DIK_D)) 
	{
		XMMATRIX mat =
		{
		cosf(-pie_ / 2), 0,           -sinf(-pie_ / 2),     0,
		0,				 1,           0,					0,
		sinf(-pie_ / 2), 0,           cosf(-pie_ / 2) ,     0,
		0,				 0,           0,					1
		};
		auto Temp = XMVector3TransformCoord(way, mat);
		XMFLOAT3 fvec;
		XMStoreFloat3(&fvec, Temp);

		fvec.y = 0;
		Temp = XMLoadFloat3(&fvec);
		XMVector3Normalize(Temp);

		CAM::SetPosition(CAM::GetPosition() - Temp * val);
		CAM::SetTarget(CAM::GetTarget() - Temp * val);
	}

	if (Input::IsKey(DIK_Q))
	{
		XMVECTOR vec;
		XMFLOAT3 material = { 0,1,0 };

		vec = XMLoadFloat3(&material);
		XMVector3Normalize(vec);

		CAM::SetPosition(CAM::GetPosition() - vec * val);
		CAM::SetTarget(CAM::GetTarget() - vec * val);
	}

	if (Input::IsKey(DIK_E))
	{
		XMVECTOR vec;
		XMFLOAT3 material = { 0,1,0 };

		vec = XMLoadFloat3(&material);
		XMVector3Normalize(vec);

		CAM::SetPosition(CAM::GetPosition() + vec * val);
		CAM::SetTarget(CAM::GetTarget() + vec * val);
	}

	if (Input::IsKey(DIK_Z))
	{
		XMFLOAT3 fvec = {}; XMStoreFloat3(&fvec, way);
		fvec.y = 0;		auto Temp = XMLoadFloat3(&fvec);
		XMVector3Normalize(Temp);

		CAM::SetPosition(CAM::GetPosition() - Temp * val);
		CAM::SetTarget(CAM::GetTarget() - Temp * val);
	}

	if (Input::IsKey(DIK_X))
	{
		XMFLOAT3 fvec = {}; XMStoreFloat3(&fvec, way);
		fvec.y = 0;		auto Temp = XMLoadFloat3(&fvec);
		XMVector3Normalize(Temp);

		CAM::SetPosition(CAM::GetPosition() + Temp * val);
		CAM::SetTarget(CAM::GetTarget() + Temp * val);
	}
}

void CamCon::Roll()
{
	double val = 0.015;

	
	if (Input::IsKey(DIK_LEFTARROW))
	{
		trans.rot.y -= val;

	}
	if (Input::IsKey(DIK_RIGHTARROW))
	{
		trans.rot.y += val;

	}
	
	if (Input::IsKey(DIK_UPARROW))
	{
		trans.rot.x += val;

	}
	if (Input::IsKey(DIK_DOWNARROW))
	{
		trans.rot.x -= val;
	}

	if (trans.rot.x > XMConvertToRadians(89.9f))	trans.rot.x = XMConvertToRadians(89.9);
	if (trans.rot.x < XMConvertToRadians(-89.9f))		trans.rot.x = XMConvertToRadians(-89.9);

	XMMATRIX rot_x = 
	{
	 1 ,          0,					 0,					 0,
	 0,           cosf(trans.rot.x),     -sinf(trans.rot.x),    0,
	 0,           sinf(trans.rot.x),     cosf(trans.rot.x),     0,
	 0,           0,					 0,						1
	};
	XMMATRIX rot_y = 
	{
	cosf(trans.rot.y), 0,               -sinf(trans.rot.y),     0,
	0,				   1,               0,						0,
	sinf(trans.rot.y), 0,               cosf(trans.rot.y) ,     0,
	0,				   0,               0,						1
	};

	XMVECTOR out = XMVector3TransformCoord(ray, rot_x * rot_y);

	CAM::SetTarget(out + CAM::GetPosition());
}
