#pragma once

#include "Trans.h"
#include"MACRO.h"
#include "D3D.h"
#include "GOBJ.h"



enum class LIGHT_TYPE
{
	NONE = 0,
	SUN = 1,
	POINT ,
	

	AMMOUNT,
};

class LOBJ 
{
public:

	virtual LOBJ* Make_Light() = 0;
	virtual LOBJ* Make_Light(string name) = 0;	//virtual friend LOBJ* Make_Light(LOBJ* inst) <- [inst is nullptr ->new LOBJ]


	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void Release();
	virtual void Draw();

	int GetType();

public:
	LOBJ(string name);
	LOBJ();
	virtual ~LOBJ();

	Trans			trans;
	XMFLOAT4		color;
	float			intensity;

protected:
	LIGHT_TYPE			LightType;
	string name;

	LOBJ* selfpointer_;

private:

};

class S_LOBJ : public LOBJ
{
public:
	LOBJ* Make_Light() override;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	S_LOBJ(string name);
	S_LOBJ();
	~S_LOBJ();
};

class P_LOBJ : public LOBJ
{
public:
	P_LOBJ* Make_Light() override;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	P_LOBJ(string name);
	P_LOBJ();
	~P_LOBJ();
};

//-------
