#pragma once
#include <list>
#include "Trans.h"
#include"MACRO.h"
#include "D3D.h"
#include "GOBJ.h"

using std::list;

enum class LIGHT_TYPE
{
	SUN = 0,
	POINT = 1,
	

	AMMOUNT,
};

class Light : public GOBJ
{
public:

	Light(GOBJ* parent, const char* name);
	Light(const char* name);
	Light();
	virtual ~Light() ;


	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void Draw() override;
	virtual void Release() = 0;

	virtual void Stop();
	void DelCol();

public:

	Trans			trans;
	XMFLOAT4		color;
	float			intensity;

protected:
	int				LightType;

};

//-------

class LIGHTMANAGER
{
public:
	list<Light*> LightPath1;
	LIGHTMANAGER* GetInstance();

private:

	LIGHTMANAGER* inst;
};