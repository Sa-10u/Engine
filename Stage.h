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
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GOBJ* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetBlockType(int x, int y, BLOCKTYPE type);
	BLOCKTYPE GetBlockType(int x,int y);
	void SetHeight(int x, int y, int h);
	int GetHeight(int x, int y);

protected:
	int model_[5];
	Block Table[XSIZE * ZSIZE];
};
