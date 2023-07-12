#pragma once
#include <string>
#include <vector>
#include"FBX.h"
#include"Trans.h"

using namespace std;

namespace Model
{
	class Data
	{
	public:
		Fbx* model_;
		Trans trans;
		string filename_;
	};
	vector<Data*> models_;


	int Load(string filename)
	{
		for (auto itr : models_) {

			if (itr->filename_ == filename)
			{
				return itr->model_;
			}
		}
	}
}