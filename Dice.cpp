#include "Dice.h"

HRESULT Dice::Initialize()
{
	VERTEX vcs[] =
	{
        {XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},
        {XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},
        {XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},
        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},

        {XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},
        {XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) , XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},
        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f,- 1.0f, 0.0f, 0.0f) },
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) , XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},

        {XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },
        {XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },
        {XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) , XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},

        {XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },
        {XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},

        {XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },
        {XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) , XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},
        {XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },
        {XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) , XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},

        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},
        {XMVectorSet(1.0f,  -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },
    };

	int index[] =
	{
         0, 2, 3,  0, 1, 2,     
         4, 6, 7,  4, 5, 6,     
         8,10,11,  8, 9,10,     
        12,14,15, 12,13,14,     
        16,18,19, 16,17,18,     
        20,22,23, 20,21,22,
	};

	HRESULT res;

	res = M_Quad::Initialize(ARRAY_WITH_SIZE(vcs), "Assets/dice.png", ARRAY_WITH_SIZE(index));

	assert(res == S_OK);

	return res;
}
