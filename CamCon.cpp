#include "CamCon.h"
#include"Engine/CAM.h"
#include "Engine/Trans.h"

CamCon::CamCon(GOBJ* parent):GOBJ(parent,"CamCon")
{
}

void CamCon::Initialize()
{
	trans.pos = { 0,3,-10 };
	ray = { 0,0,1.0 ,0};

	CAM::SetPosition(trans.pos);
	CAM::SetTarget(ray);
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
	XMVECTOR temp;
	temp = CAM::GetTarget() - CAM::GetPosition();
	temp = XMVector3Normalize(temp);

	static double pie_ = 3.141592;

	float val = 0.1;

	if (Input::IsKey(DIK_W)) 
	{
		CAM::SetPosition(CAM::GetPosition() + temp * val);
		CAM::SetTarget(CAM::GetTarget() + temp * val);
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
		auto Temp = XMVector3TransformCoord(temp, mat);
		XMFLOAT3 fvec;
		XMStoreFloat3(&fvec, Temp);

		fvec.y = 0;
		Temp = XMLoadFloat3(&fvec);

		CAM::SetPosition(CAM::GetPosition() - Temp * val);
		CAM::SetTarget(CAM::GetTarget() - Temp * val);
	}
	if (Input::IsKey(DIK_S))
	{
		CAM::SetPosition(CAM::GetPosition() - temp * val);
		CAM::SetTarget(CAM::GetTarget() - temp * val);
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
		auto Temp = XMVector3TransformCoord(temp, mat);
		XMFLOAT3 fvec;
		XMStoreFloat3(&fvec, Temp);

		fvec.y = 0;
		Temp = XMLoadFloat3(&fvec);


		CAM::SetPosition(CAM::GetPosition() - Temp * val);
		CAM::SetTarget(CAM::GetTarget() - Temp * val);
	}

	if (Input::IsKey(DIK_Q))
	{
		XMVECTOR vec;
		XMFLOAT3 material = { 0,1,0 };

		vec = XMLoadFloat3(&material);

		CAM::SetPosition(CAM::GetPosition() - vec * val);
		CAM::SetTarget(CAM::GetTarget() - vec * val);
	}

	if (Input::IsKey(DIK_E))
	{
		XMVECTOR vec;
		XMFLOAT3 material = { 0,1,0 };

		vec = XMLoadFloat3(&material);

		CAM::SetPosition(CAM::GetPosition() + vec * val);
		CAM::SetTarget(CAM::GetTarget() + vec * val);
	}

	if (Input::IsKey(DIK_Z))
	{
		XMFLOAT3 fvec = {}; XMStoreFloat3(&fvec, temp);
		fvec.y = 0;		auto Temp = XMLoadFloat3(&fvec);

		CAM::SetPosition(CAM::GetPosition() - Temp * val);
		CAM::SetTarget(CAM::GetTarget() - Temp * val);
	}

	if (Input::IsKey(DIK_X))
	{
		XMFLOAT3 fvec = {}; XMStoreFloat3(&fvec, temp);
		fvec.y = 0;		auto Temp = XMLoadFloat3(&fvec);

		CAM::SetPosition(CAM::GetPosition() + Temp * val);
		CAM::SetTarget(CAM::GetTarget() + Temp * val);
	}
}

void CamCon::Roll()
{
	XMVECTOR mig = CAM::GetTarget() - CAM::GetPosition();

	XMMATRIX MAT =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	double val = 0.015;

	
	if (Input::IsKey(DIK_LEFTARROW))
	{
		XMMATRIX mat = XMMatrixRotationY(-val);
		MAT = MAT * mat;

	}
	if (Input::IsKey(DIK_RIGHTARROW))
	{
		XMMATRIX mat = XMMatrixRotationY(val);
		MAT = MAT * mat;

	}
	
	if (Input::IsKey(DIK_UPARROW))
	{
		XMMATRIX mat = XMMatrixRotationX(-val);
		MAT = MAT * mat;

	}
	if (Input::IsKey(DIK_DOWNARROW))
	{
		XMMATRIX mat = XMMatrixRotationX(val);
		MAT = MAT * mat;

	}

	auto rot = XMQuaternionRotationMatrix(MAT);
	auto out = XMVector3Rotate(mig, rot);

	CAM::SetTarget(out);
}
