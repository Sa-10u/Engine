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

class Light : public GOBJ
{
public:

	Light(GOBJ* parent, const char* name);
	Light(const char* name);
	Light();
	virtual ~Light() ;


	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
	virtual void Draw() override;

	int GetType();

public:

	Trans			trans;
	XMFLOAT4		color;
	float			intensity;

protected:
	LIGHT_TYPE			LightType;

};

class S_Light : public Light
{
public:
	S_Light(GOBJ* parent, const char* name);
	S_Light(const char* name);
	S_Light();
	~S_Light();

	void Initialize() override;
	virtual void Update() override;
	void Release() override;
	virtual void Draw() override;
};

class P_Light : public Light
{
public:
	P_Light(GOBJ* parent, const char* name);
	P_Light(const char* name);
	P_Light();
	~P_Light();

	void Initialize() override;
	virtual void Update() override;
	void Release() override;
	virtual void Draw() override;
};

//-------

class LIGHTMANAGER
{
public:

	struct LightGroup
	{
		Light* me[LIGHT_AMMOUNT];
		LightGroup();
		~LightGroup();
		void Release();
		void Make(Light* &lght);

	private:
		int index_;
	};

public:
	//--- Light Resources
	LightGroup LightPath1;
	
	//---

	static LIGHTMANAGER* GetInstance();
	void Release();

private:

	LIGHTMANAGER();
	~LIGHTMANAGER();

	static LIGHTMANAGER* inst_;
};

extern LIGHTMANAGER* LightManager;