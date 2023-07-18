#pragma once
#include"../SCENE_Test.h"
#include"../PlayScene.h"
#include "Model.h"

#include "SceneManager.h"

SceneManager::SceneManager(GOBJ* parent, const char* name) : GOBJ(parent, name)
{
	current_ = SID::PLAY;
	next_ = current_;

	Make<SCENE_Test>(this);
}

SceneManager::SceneManager(GOBJ* parent): GOBJ(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
}

void SceneManager::Update()
{
	if (next_ != current_)
	{
		auto scene = children.begin();
		(*scene)->ReleaseALL();
		delete *scene;
		children.clear();

		Model::Release();

		switch (next_)
		{
		case SID::PLAY:	Make<PlayScene>(this);	break;

		case SID::TEST: Make<SCENE_Test>(this);	break;
		}

		current_ = next_;
	}
}

void SceneManager::Release()
{
}

void SceneManager::Draw()
{
}

void SceneManager::ChangeScene(SID next)
{
	next_ = next;
}
