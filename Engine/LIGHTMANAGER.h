#pragma once
#include"LOBJ.h"

enum 
{
	Light_Path1 = 0,

	Light_Group_Ammount 
};

class LIGHTMANAGER
{
public:

	struct LightGroup
	{
		LOBJ* me[LIGHT_AMMOUNT];
		LightGroup();
		~LightGroup();
		void Release();
		void Make(LOBJ*& lght);

	private:
		int index_;
	};

	LightGroup Light_Path1;

public:
	//--- Light Resources
	LightGroup* LIGHTGROUP[Light_Group_Ammount] =
	{
		&Light_Path1,
	};

	//---

	static LIGHTMANAGER* GetInstance();
	void Release();

private:

	LIGHTMANAGER();
	~LIGHTMANAGER();

	static LIGHTMANAGER* inst_;
};

extern LIGHTMANAGER* LightManager;