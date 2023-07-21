#pragma once
#include"LOBJ.h"
#include <array>

using std::array;

class LIGHTMANAGER
{
public:

	struct LightGroup
	{
		array<LOBJ* , LIGHT_AMMOUNT> me;
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
	LightGroup* LIGHTGROUP[1] =
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