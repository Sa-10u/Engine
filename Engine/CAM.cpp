#include "CAM.h"

namespace CAM
{
	XMVECTOR pos_;
	XMVECTOR tgt_;
	XMMATRIX viewMat_;
	XMMATRIX projMat_;
}

void CAM::Initialize()
{
	pos_ = { 0,3,-10,0 };
	tgt_ = { 0,0,1,0 };

	viewMat_= XMMatrixLookAtLH(pos_, tgt_, XMVectorSet(0, 1, 0, 0));	//ÉrÉÖÅ[çsóÒ
	projMat_ = XMMatrixPerspectiveFovLH(XM_PI / 4, 800.0f / 600.0f, 0.1f, 100.0f);
}

void CAM::Update()
{
	viewMat_ = XMMatrixLookAtLH(pos_, tgt_, XMVectorSet(0, 1, 0, 0));
}

void CAM::SetPosition(XMVECTOR position)
{
	pos_ = position;
}

void CAM::SetPosition(XMFLOAT3 position)
{
	SetPosition(XMLoadFloat3(&position));
}

XMVECTOR CAM::GetPosition()
{
	return pos_;
}

void CAM::SetTarget(XMVECTOR target)
{
	tgt_ = target;
}

void CAM::SetTarget(XMFLOAT3 target)
{
	SetTarget(XMLoadFloat3(&target));
}

XMVECTOR CAM::GetTarget()
{
	return tgt_;
}

void CAM::SetFOV(float fov)
{
}

float CAM::GetFOV()
{
	return 0.0f;
}

XMMATRIX CAM::GetViewMatrix()
{
	return viewMat_;
}

XMMATRIX CAM::GetProjectionMatrix()
{
	return projMat_;
}
