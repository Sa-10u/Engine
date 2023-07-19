#pragma once
#include"GOBJ.h"

enum class USID
{
	PLAY = 0,
	TEST,

	AMMOUNT
};

class SceneManager : public GOBJ
{
public:

	SceneManager(GOBJ* parent, string name);
	SceneManager(GOBJ* parent);
	~SceneManager();

	void Initialize() override;
	void Update() override;
	void Release() override;
	void Draw() override;

	void ChangeScene(USID next);
	void Changing();

	void (SceneManager::* Changer[2])() = {&GOBJ::EmptyWork , &SceneManager::Changing};

	
	

private:

	USID current_;
	USID next_;
};

