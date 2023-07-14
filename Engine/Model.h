#pragma once
#include <string>
#include <vector>
#include"FBX.h"
#include"Trans.h"

using namespace std;

namespace Model
{
	int Load(string filename);

	void Draw(int* model_);

	void Release();

	void SetTrans(int* model_, Trans* trans);

	void Draw(int* model_, Trans* trans , SHADER_TYPE type);
	
	void SetShader(int* model_, SHADER_TYPE type);

	void SetLightGroup(int* model_, LIGHTMANAGER::LightGroup* grp);

}