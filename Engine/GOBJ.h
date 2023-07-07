#pragma once
#include <list>
#include "Trans.h"
#include"MACRO.h"

using std::list;

enum class OBJ_STATE
{
	KILL = 1,
	STOP = 2,
	COOLLISION = 4,
};

class GOBJ
{
public:

	GOBJ(GOBJ* parent , const char* name);
	GOBJ();
	virtual ~GOBJ() {};

	virtual void Initialize()	= 0;
	virtual void Update()		= 0;
	virtual void Draw()			= 0;
	virtual void Release()		= 0;
	void UpdateALL();
	void DrawALL();

	virtual void KillMe();
	virtual void Stop();
	virtual void DelCol();

	virtual list<GOBJ*> GetChildren();

	template<class T>
	void Make(GOBJ* parent)
	{
		T* obj = new T(this);
		obj->Initialize();
		parent->children.push_back(obj);
	}
	

public:

	list<GOBJ*>		children;
	Trans			trans;

protected:

	const char*		name_;
	GOBJ*			parent_;

	char			state_;
};

