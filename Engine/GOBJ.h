#pragma once
#include <list>
#include "Trans.h"
#include"MACRO.h"
#include "D3D.h"
#include <string>

using std::list;
using std::string;

enum class OBJ_STATE
{
	KILL = 1,
	STOP = 2,
	COOLLISION = 4,
};

class GOBJ
{
public:

	GOBJ(GOBJ* parent , string name);
	GOBJ(string name);
	GOBJ();
	virtual ~GOBJ() {};


	virtual void Initialize()	= 0;
	virtual void Update()		= 0;
	virtual void Draw()			= 0;
	virtual void Release()		= 0;

	void UpdateALL();
	void DrawALL();
	void ReleaseALL();

	virtual void KillMe();
	virtual void Stop();
	virtual void DelCol();
	virtual void Disposal();

	virtual list<GOBJ*> GetChildren();
	GOBJ* GetParent();

	bool IsDead();
	bool IsDisposal();
	void EndDisposal();
	void EmptyWork();

	void (GOBJ::* IsDoDisposal[2])() = {&GOBJ::EmptyWork ,&GOBJ::Disposal};

	template<class T>
	T* Make(GOBJ* parent)
	{
		T* obj = new T (parent);
		obj->Initialize();
		parent->children.push_back(obj);

		return obj;
	}

	GOBJ*			FindObject_ALL(string name);
	GOBJ*			FindObject_Child(string name);
	list<GOBJ*>		FindObject_Children(string name);
	GOBJ*			GetRootObj();

public:

	list<GOBJ*>		children;
	Trans			trans;

protected:

	string			name_;
	GOBJ*			parent_;

	char			state_;
	static bool		DoDelProc_ ;

private:

	void consfunc1(GOBJ* p);
	void consfunc2(GOBJ* p);

	void(GOBJ::*consfunc[2])(GOBJ* p) = {&GOBJ::consfunc1,&GOBJ::consfunc2};

};

