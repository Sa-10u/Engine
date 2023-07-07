#pragma once
#include"Engine/GOBJ.h"
class Fbx;

class Player : public GOBJ
{
public:

	Player() = delete;
	Player(GOBJ* parent );
	~Player();

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Release()		override;

private:

	Fbx* model_;

};

