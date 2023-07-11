#include "RootOBJ.h"

RootOBJ::RootOBJ()
{
}

RootOBJ::~RootOBJ()
{
}

void RootOBJ::Initialize()
{
	PlayScene* p_plscn;
	p_plscn = new PlayScene(this,"PlayScene");
	p_plscn->Initialize();

	scene_.push_back(p_plscn);
}

void RootOBJ::Update()
{
	for (auto itr : scene_) {

		itr->Update();
	}
}

void RootOBJ::Draw()
{
	for (auto itr : scene_) {

		itr->Draw();
	}
}

void RootOBJ::Release()
{
	for (auto itr : scene_) {

		itr->ReleaseALL();
	}
}

void RootOBJ::Disposal()
{
	for (auto itr : scene_) {

		itr->Disposal();
	}
}




