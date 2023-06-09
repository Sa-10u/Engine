#include "Dice.h"

HRESULT Dice::Initialize()
{
	VERTEX vcs[] =
	{
		{XMVectorSet(1,0,0,0) , XMVectorSet(0,0,0,0)},
		{XMVectorSet(1,1,0,0) , XMVectorSet(0.25,0,0,0)},
		{XMVectorSet(0,1,0,0) , XMVectorSet(0.25,0.5,0,0)},		//1*
		{XMVectorSet(0,0,0,0) , XMVectorSet(0,0.5,0,0)},

		{XMVectorSet(1,1,1,0) , XMVectorSet(0.5,0,0,0)},		//2*
		{XMVectorSet(0,1,1,0) , XMVectorSet(0.5,0.5,0,0)},

		{XMVectorSet(1,0,1,0) , XMVectorSet(0.75,0,0,0)},
		{XMVectorSet(0,0,1,0) , XMVectorSet(0.75,0.5,0,0)},		//3*

		{XMVectorSet(1,0,0,0) , XMVectorSet(1,0,0,0)},
		{XMVectorSet(0,0,0,0) , XMVectorSet(1,0.5,0,0)},		//4*

		{XMVectorSet(0,0,0,0) , XMVectorSet(0,1,0,0)},			//5
		{XMVectorSet(0,0,0,0) , XMVectorSet(0.25,1,0,0)},

		{XMVectorSet(0,0,1,0) , XMVectorSet(0.5,1,0,0)},		//6
	
	};

	int index[] =
	{
	
	};

	M_Quad::Initialize(vcs, "Assets/dice.png",index );
}
