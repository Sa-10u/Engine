#pragma once
#include <list>
#include "Trans.h"

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
	~GOBJ() {};

	virtual void Initialize()	= 0;
	virtual void UpDate()		= 0;
	virtual void Draw()			= 0;
	virtual void Release()		= 0;

	virtual void KillMe();
	virtual void Stop();
	virtual void DelCol();

	virtual list<GOBJ*> GetChildren();
	

public:

	list<GOBJ*>		children;
	Trans			trans;

protected:

	const char*		name_;
	GOBJ*			parent_;
	

	char			state_;
};

