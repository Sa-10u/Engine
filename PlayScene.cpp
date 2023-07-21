#include "PlayScene.h"
#include"Engine/FBX.h"
#include "Player.h"
#include"Enemy.h"

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
	Make<Enemy>(this);
}

void PlayScene::Update()
{
	
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
	
}
