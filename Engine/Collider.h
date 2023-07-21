#pragma once
#include"Trans.h"
#include<list>

using std::list;

class GOBJ;

class Collider
{
public:
	Collider();
	Collider(float len, XMFLOAT3 pos);
	virtual ~Collider();

	float GetRadius();
	XMFLOAT3 GetPos();

	void SetRadius(float len);
	void SetPos(XMFLOAT3 pos);

private:
	float rad_;
	Trans trans;
};