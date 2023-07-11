#pragma once
#include "FBX.h"
#include"GOBJ.h"

class Light : public GOBJ
{
public:

	Light();
	~Light();


	virtual void Release() = 0;
	
};

