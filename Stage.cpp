#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GOBJ* parent):GOBJ(parent,"Stage")
{
}

void Stage::Initialize()
{
	string base_ = "assets/";
	string names_[static_cast<int>(BLOCKTYPE::AMMOUNT)] =
	{
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};

	for (int i = 0; i < sizeof(names_) / sizeof(names_[0]); i++) {

		model_[i] = Model::Load(base_ + names_[i]);
		assert(model_[i] != -1);
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			
			Table[x* XSIZE + z] = model_[(x + z) % 5];
		}
	}
	
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			Trans sttrans;
			sttrans.pos = { (float)x,0 ,(float)z };

			Model::Draw(&Table[x*XSIZE + z], &sttrans, SHADER_TYPE::SHADER_2D);
		}
	}
	
}

void Stage::Release()
{
}

void Stage::SetBlockType(int x, int y, BLOCKTYPE type)
{
	Table[x * XSIZE + y] = model_[static_cast<int>(type)];
}

BLOCKTYPE Stage::GetBlockType(int x, int y)
{
	return static_cast<BLOCKTYPE>(Table[x * XSIZE + y]);
}
