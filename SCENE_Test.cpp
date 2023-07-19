#include "SCENE_Test.h"
#include"Engine/DInput.h"
#include"Engine/SceneManager.h"

SCENE_Test::SCENE_Test(GOBJ* parent,string name) :GOBJ(parent, name)
{
}

SCENE_Test::SCENE_Test(GOBJ* parent):GOBJ(parent,"SCENE_TEST")
{
}

SCENE_Test::~SCENE_Test()
{
}

void SCENE_Test::Initialize()
{
}

void SCENE_Test::Update()
{
	parent_;
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* sm = nullptr;
		sm = dynamic_cast<SceneManager*>(FindObject_ALL("SceneManager"));
		sm->ChangeScene(USID::PLAY);
	}

	for (auto itr : children) {
		itr->UpdateALL();
	}
}

void SCENE_Test::Release()
{
	for (auto itr : children) {

	}
}

void SCENE_Test::Draw()
{
	for (auto itr : children) {
		itr->DrawALL();
	}
}
