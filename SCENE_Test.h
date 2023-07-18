#pragma once
#include"Engine/GOBJ.h"

class SCENE_Test : public GOBJ
{
public:
	SCENE_Test(GOBJ* parent, const char* name);
	SCENE_Test(GOBJ* parent);
	~SCENE_Test();

	void Initialize() override;
	void Update() override;
	void Release() override;
	void Draw() override;
};

