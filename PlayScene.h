#pragma once
#include "Engine/GOBJ.h"

class Fbx;

class PlayScene	: public GOBJ
{
public: 
	PlayScene()= delete;
	PlayScene(GOBJ* parent,const char* name);
	PlayScene(GOBJ* parent);
	~PlayScene();

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Release()		override;

private:

};

