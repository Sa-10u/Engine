#pragma once
#include"../SCENE_Test.h"
#include "Model.h"

#include "SceneManager.h"

SceneManager::SceneManager(GOBJ* parent, string name) : GOBJ(parent, name)
{

}

SceneManager::SceneManager(GOBJ* parent): GOBJ(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	current_ = USID::TEST;
	next_ = current_;

	Make<SCENE_Test>(this);
}

void SceneManager::Update()
{
	(this->*Changer[static_cast<bool>(static_cast<int>(current_) - static_cast<int>(next_))])();
}

void SceneManager::Release()
{
}

void SceneManager::Draw()
{
}

void SceneManager::ChangeScene(USID next)
{
 	next_ = next;
}

void SceneManager::Changing()
{
	auto scene = children.begin();
	(*scene)->ReleaseALL();
	delete* scene;
	children.clear();

	Model::Release();

	switch (next_)
	{

	case USID::TEST:	Make<SCENE_Test>(this);	break;
	}

	current_ = next_;
}
