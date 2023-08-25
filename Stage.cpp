#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GOBJ* parent):GOBJ(parent,"Stage"),model_(-1)
{
}

void Stage::Initialize()
{
	model_ = Model::Load("Assets/BoxDefault.fbx");
	assert(model_ != -1);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int x = 0; x < 10; x++) {
		for (int z = 0; z < 10; z++) {
			Trans sttrans;
			sttrans.pos = { (float)x,0 ,(float)z };

			Model::Draw(&model_, &sttrans, SHADER_TYPE::SHADER_2D);
		}
	}
	
}

void Stage::Release()
{
}
