#pragma once
#include"Trans.h"
#include"Collider.h"

class SphereCol : public Collider
{
public:
	SphereCol();
	SphereCol(float len ,XMFLOAT3 pos);
	~SphereCol();
};