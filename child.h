#pragma once
#include "Engine/GOBJ.h"
#include "Engine/Fbx.h"
#include "Engine/SphereCol.h"

class child : public GOBJ
{
public:
	child(GOBJ* parent);
	child() = delete ;
	virtual ~child();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

private:

	Fbx* model_;
	int m_;
	Collider* col;

	void OnCol();
};

