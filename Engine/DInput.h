#pragma once

#include<dInput.h>
#include "MACRO.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dInput8.lib")

namespace Input
{
	HRESULT Initialize(HWND hwnd);
	void Update();
	bool IsKey(int code);
	bool IsKeyDown(int code);
	bool IsKeyUp(int code);
	void Release();
};

