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

		{XMVectorSet(0,0,1,0) , XMVectorSet(0,1,0,0)},			//5
		{XMVectorSet(0,0,1,0) , XMVectorSet(0.25,1,0,0)},

		{XMVectorSet(0,0,1,0) , XMVectorSet(0.5,1,0,0)},		//6
	
	};

	int index[] =
	{
		0,1,2, 0,2,3, 1,4,5, 1,5,2, 7,6,4, 5,7,4, 6,8,9, 6,9,7, 3,2,11, 3,11,10 ,2,5,12, 2,12,11
	};

	HRESULT res;

	res = M_Quad::Initialize(ARRAY_WITH_SIZE(vcs), "Assets/dice.png", ARRAY_WITH_SIZE(index));

	assert(res == S_OK);

	return res;
}
