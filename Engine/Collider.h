#pragma once
#include"Trans.h"
#include<list>

using std::list;

class GOBJ;

class Collider
{
public:
	Collider(GOBJ* parent);
	Collider(float len, XMFLOAT3 pos ,GOBJ* parent);
	virtual ~Collider();

	float GetRadius();
	XMFLOAT3 GetPos();
	GOBJ* GetParent();

	void SetRadius(float len);
	void SetPos(XMFLOAT3 pos);
	void SetParent(GOBJ* p);

	virtual bool IsHit(GOBJ* tgt) = 0;

	void SetFunc(void(GOBJ::* rum)());
	void OnCol(GOBJ* tgt, void (GOBJ::*rum)());

	static list<Collider*> cols;

protected:
	float rad_;
	Trans trans;
	void(GOBJ::* func)();
	GOBJ* parent_;
};