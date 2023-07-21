#pragma once
#include"Engine/GOBJ.h"
#include"Engine/Model.h"

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

	void ColProc()		override;

private:

	int m_;
};

