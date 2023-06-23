#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Trans
{
public:
	XMFLOAT3 pos;	//�ʒu
	XMFLOAT3 rot;	//����
	XMFLOAT3 size;	//�g�嗦

	//�R���X�g���N�^
	Trans();

	//�f�X�g���N�^
	~Trans();

	//�e�s��̌v�Z
	void Calc();

	//���[���h�s����擾
	XMMATRIX GetWorldMatrix();
	XMMATRIX GetNormalMatrix();

private:
	XMMATRIX matgra;
	XMMATRIX matrot;
	XMMATRIX matsc;

	XMMATRIX mat;
};

