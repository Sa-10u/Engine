#pragma once
#include "CONSTANT_BUFFER.h"
#include "D3D.h"
#include <DirectXMath.h>
#include "MACRO.h"
#include "CAM.h"
#include "Texture.h"
#include "M_Quad.h"

class Dice : public M_Quad
{
public:
	HRESULT Initialize();
};

