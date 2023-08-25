#pragma once
#include"Engine/GOBJ.h"
#include"Engine/Model.h"
#include"Engine/Collider.h"

class Enemy : public GOBJ
{
public:

	Enemy() = delete;
	Enemy(GOBJ* parent);
	~Enemy();

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Release()		override;

private:

	int m_;
	Collider* col;
};

