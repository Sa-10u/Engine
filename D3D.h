#pragma once

namespace D3D
{
	void Initialize(int winW, int winH, HWND hwnd);

	void BeginDraw();

	void EndDraw();

	void Release();


	void Shader_Initialize();
}