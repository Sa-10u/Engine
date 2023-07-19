#pragma once
#include "Engine/GOBJ.h"

class Fbx;

class PlayScene	: public GOBJ
{
public: 
	PlayScene();
	PlayScene(GOBJ* parent,string name);
	PlayScene(GOBJ* parent);
	~PlayScene();

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Release()		override;

private:

};

