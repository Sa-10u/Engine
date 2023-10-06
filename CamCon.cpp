#include "CamCon.h"
#include"Engine/CAM.h"
#include "Engine/Trans.h"
#include"Engine/MACRO.h"
#include "Stage.h"

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
	switch (isSetting_)
	{
	case false: Move();
				Roll();
				SetPrem();
				Shortcut();
				break;

	case true: ToPrem();

	default:return;
	}
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
	
	if(!Input::IsKey(DIK_LCONTROL))
	{
		float tweak = (!Input::IsKey(DIK_LSHIFT)) * 8 +1;
		auto wheel = Input::GetMouseMove().z * 0.001 *tweak;

		CAM::SetPosition(CAM::GetPosition() + way * wheel);
		CAM::SetTarget(CAM::GetTarget() + way * wheel);
	}
	else
	{
		float tweak = (Input::IsKey(DIK_LSHIFT)) * -0.9 + 1;
		auto val = Input::GetMouseMove().z * 0.01 * tweak;
		XMVECTOR vec;
		XMFLOAT3 material = { 0,1,0 };

		vec = XMLoadFloat3(&material);
		vec = XMVector3Normalize(vec);

		CAM::SetPosition(CAM::GetPosition() - vec * val);
		CAM::SetTarget(CAM::GetTarget() - vec * val);
	}
	
	if (Input::IsMouseButton(1) && Input::IsKey(DIK_LALT))
	{
		auto val = Input::GetMouseMove().x * 0.05;

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
		Temp = XMVector3Normalize(Temp);

		CAM::SetPosition(CAM::GetPosition() - Temp * val);
		CAM::SetTarget(CAM::GetTarget() - Temp * val);
	}

	if (Input::IsMouseButton(1) && Input::IsKey(DIK_LALT))
	{
		auto val = -Input::GetMouseMove().y * 0.05;
		XMFLOAT3 fvec = {}; XMStoreFloat3(&fvec, way);
		fvec.y = 0;		auto Temp = XMLoadFloat3(&fvec);
		Temp = XMVector3Normalize(Temp);

		CAM::SetPosition(CAM::GetPosition() - Temp * val);
		CAM::SetTarget(CAM::GetTarget() - Temp * val);
	}

}

void CamCon::Roll()
{
	{
		trans.rot.y += Input::GetMouseMove().x * 0.005  * (Input::IsMouseButton(1)* !Input::IsKey(DIK_LALT));
		trans.rot.x += Input::GetMouseMove().y * -0.005 * (Input::IsMouseButton(1)* !Input::IsKey(DIK_LALT));

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

void CamCon::SetPrem()
{
	if (Input::IsKeyDown(DIK_NUMPAD1))
	{
		isSetting_ = true;
		XMStoreFloat3(&bef_pos,CAM::GetPosition());
		XMStoreFloat3(&bef_tgt, CAM::GetTarget());

		prem_pos = { 6.5,5,-7 };
		prem_tgt = { 6.5,0, 0 };

		count = 10;

		return;
	}

}

void CamCon::Shortcut()
{
	if (Input::IsKey(DIK_LCONTROL) && Input::IsKeyDown(DIK_S))
	{
		Stage* st = dynamic_cast<Stage*>(parent_->FindObject_Child("Stage"));
		st->Q_Save();
	}
}

void CamCon::ToPrem()
{
	if (!(count > 0))
	{
		CAM::SetPosition(prem_pos);

		isSetting_ = false;

		return;
	}
	

	XMFLOAT3 nowpos = (bef_pos * (10 - count) + prem_pos * (count - 10))/10 ;

	count--;

	CAM::SetPosition(nowpos);
}
