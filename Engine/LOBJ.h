#pragma once
#include <array>
#include "Trans.h"
#include"MACRO.h"
#include "D3D.h"
#include "GOBJ.h"

using std::array;

enum class LIGHT_TYPE
{
	SUN = 0,
	POINT = 1,
	

	AMMOUNT,
};

class LOBJ 
{
public:

	LOBJ(LOBJ* parent, string name);
	LOBJ(string name);
	LOBJ(LOBJ* parent);
	LOBJ();
	virtual ~LOBJ() ;


	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
	virtual void Draw();

	int GetType();

public:

	Trans			trans;
	XMFLOAT4		color;
	float			intensity;

protected:
	LIGHT_TYPE			LightType;
	LOBJ* parent;
	string name;

};

class S_LOBJ : public LOBJ
{
public:
	S_LOBJ(LOBJ* parent,string name);
	S_LOBJ(string name);
	S_LOBJ();
	~S_LOBJ();

	void Initialize() override;
	virtual void Update() override;
	void Release() override;
	virtual void Draw() override;
};

class P_LOBJ : public LOBJ
{
public:
	P_LOBJ(LOBJ* parent,string name);
	P_LOBJ(string name);
	P_LOBJ();
	~P_LOBJ();

	void Initialize() override;
	virtual void Update() override;
	void Release() override;
	virtual void Draw() override;
};

//-------
