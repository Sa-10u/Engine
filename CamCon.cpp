#include "CamCon.h"
#include"Engine/CAM.h"
#include "Engine/Trans.h"
#include"Engine/MACRO.h"
#include "Stage.h"

static const float rotX = -0.4f;

CamCon::CamCon(GOBJ* parent):GOBJ(parent,"CamCon"),count_val(10)
{
}

void CamCon::Initialize()
{
	ray = CAM::GetTarget();
	trans.rot.x = rotX;

	XMFLOAT3 temp = { 6.5,5,-7 };
	CAM::SetPosition(temp);
	CAM::SetTarget(XMLoadFloat3(&temp) + CAM::GetPosition());

	Roll();
	XMStoreFloat3(&prem_pos, CAM::GetPosition());
	XMStoreFloat3(&prem_tgt, (CAM::GetTarget()));

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
	prem_tgt;

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
	prem_tgt;
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
		XMStoreFloat3(&bef_tgt,(CAM::GetTarget() ));

		count = 0;

		return;
	}

}

void CamCon::Shortcut()
{
	static Stage* st = dynamic_cast<Stage*>(parent_->FindObject_Child("Stage"));
	if (Input::IsKey(DIK_LCONTROL) )
	{
		
		if (Input::IsKeyDown(DIK_Z))
		{
			st->SetSTG_CMD(st->GetCommand());
		}

		if (Input::IsKeyDown(DIK_R))
		{
			st->SetSTG_CMD(st->ReGetCommand());
		}

		if (Input::IsKeyDown(DIK_S))
		{
			st->Q_Save();
		}
		
	}

}

void CamCon::ToPrem()
{
	if ((count >= count_val))
	{
		trans.pos = XMFLOAT3{ 0,0,0 };
		CAM::SetPosition(prem_pos);

		trans.rot.x = rotX;
		trans.rot.y = 0.0f;
		trans.rot.z = 0.0f;
		CAM::SetTarget(prem_tgt);

		isSetting_ = false;

		return;
	}

	XMFLOAT3 nowpos = ((bef_pos * (count_val - count)) + (prem_pos * (count_val - (count_val - count)))) / count_val;
	CAM::SetPosition(nowpos);

	XMFLOAT3 temp = {};

	XMFLOAT3 nowtgt = ((bef_tgt * (count_val - count)) + (prem_tgt * (count_val - (count_val - count)))) / count_val;
	CAM::SetTarget(nowtgt);
	
	count++;

	
}
