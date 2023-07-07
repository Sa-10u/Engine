#include "PlayScene.h"
#include"Engine/FBX.h"
#include "Player.h"

PlayScene::PlayScene(GOBJ* parent, const char* name):GOBJ(parent,name)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Make<Player>(this);
}

void PlayScene::Update()
{
	for (auto itr : children) {
		itr->UpdateALL();
	}
}

void PlayScene::Draw()
{
	for (auto itr : children) {
		itr->DrawALL();
	}
}

void PlayScene::Release()
{
	for (auto itr : children) {

	}
}
