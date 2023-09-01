#pragma once
#include "Engine/GOBJ.h"

const int XSIZE{ 15 };
const int ZSIZE{ 15 };

enum class BLOCKTYPE
{
	DEFAULT,
	BRICK,
	GRASS,
	SAND,
	WATER,

	AMMOUNT
};

struct Block
{
public:
	BLOCKTYPE blk;
	float height;
};

class Stage : public GOBJ
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GOBJ* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetBlockType(int x, int y, BLOCKTYPE type);
	BLOCKTYPE GetBlockType(int x,int y);
	void SetHeight(int x, int y, int h);
	int GetHeight(int x, int y);

protected:
	int model_[5];
	Block Table[XSIZE * ZSIZE];
};
