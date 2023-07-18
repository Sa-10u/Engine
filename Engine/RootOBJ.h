#pragma once
#include "GOBJ.h"
#include "../PlayScene.h"

class RootOBJ : public GOBJ
{
public:
	RootOBJ(GOBJ* parent);
	~RootOBJ();

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Release()		override;
	void Disposal()		override;

private:
};

