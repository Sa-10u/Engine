#pragma once
#include "D3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace CAM
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position);
	void SetPosition(XMFLOAT3 position);
	XMVECTOR GetPosition();

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target);
	void SetTarget(XMFLOAT3 target);
	XMVECTOR GetTarget();

	void SetFOV(float fov);
	float GetFOV();

	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();

	extern XMVECTOR pos_;
	extern XMVECTOR tgt_;
	extern XMMATRIX viewMat_;
	extern XMMATRIX projMat_;
};