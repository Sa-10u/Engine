#pragma once

#include <DirectXMath.h>
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

	bool IsMouseButton(int code);
	bool IsMouseButtonDown(int code);
	bool IsMouseButtonUp(int code);

	XMFLOAT3 GetMousePosition();
	XMFLOAT3 GetMouseMove();

	void SetMousePosition(XMFLOAT3 pos);
	void SetMousePosition(int x ,int y);
};

