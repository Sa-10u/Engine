#pragma once
#include"Trans.h"
#include"Collider.h"

class SphereCol : public Collider
{
public:
	SphereCol(GOBJ* parent);
	SphereCol(float len ,XMFLOAT3 pos,GOBJ* parent);
	~SphereCol();

	bool IsHit(GOBJ* tgt)	override;
};