#pragma once
#include"GOBJ.h"

enum class SID
{
	PLAY = 0,
	TEST,

	AMMOUNT
};

class SceneManager : public GOBJ
{
public:

	SceneManager(GOBJ* parent, const char* name);
	SceneManager(GOBJ* parent);
	~SceneManager();

	void Initialize() override;
	void Update() override;
	void Release() override;
	void Draw() override;

	void ChangeScene(SID next);

	void (SceneManager::* Changer[2])();

private:

	SID current_;
	SID next_;
};

