#include "PlayScene.h"
#include"Engine/FBX.h"
#include "Player.h"

PlayScene::PlayScene()
{
}

PlayScene::PlayScene(GOBJ* parent, string name):GOBJ(parent,name)
{
}

PlayScene::PlayScene(GOBJ* parent) :GOBJ(parent,"PlayScene")
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
