#include "Model.h"

class Data
{
public:
	Fbx* model_;
	Trans trans;
	string filename_;
};
vector<Data*> models_;

int Model::Load(string filename)
{
	Data* data_ = new Data();
	data_->filename_ = filename;
	data_->model_ = nullptr;// new Fbx;
	for (auto& itr : models_) {
		if (itr->filename_ == filename)
		{
			data_->model_ = itr->model_;
			break;
		}
	}

	if (data_->model_ == nullptr)
	{
		data_->model_ = new Fbx();
		data_->model_->Load(filename);
	}
	models_.push_back(data_);

	return (models_.size() - 1);
}

void Model::Draw(int* num)
{
	models_[*num]->model_->Draw(&(models_[*num]->trans)); 
}

void Model::Release()
{
	bool IsRef = false;
	for (int i = 0; i < models_.size(); i++) {

		for (int j = i + 1; j < models_.size(); j++) {

			if (models_[i]->model_ == models_[j]->model_)
			{
				IsRef = true;
				break;
			}
		}

		if (!IsRef)
		{
			SAFE_DELETE(models_[i]->model_);
		}
		SAFE_DELETE(models_[i]);
	}

	models_.clear();
}

void Model::SetTrans(int* model_, Trans* trans)
{
	{
		models_[*model_]->trans = *trans;
	}
}

void Model::Draw(int* model_, Trans* trans , SHADER_TYPE type)
{
	{
		models_[*model_]->model_->SetShaderType(type);
		models_[*model_]->trans = *trans;
		models_[*model_]->model_->Draw(&(models_[*model_]->trans));
	}

}

void Model::SetShader(int* model_, SHADER_TYPE type)
{	
	models_[*model_]->model_->SetShaderType(type);	
}

void Model::SetLightGroup(int* model_, LIGHTMANAGER::LightGroup* grp)
{
	models_[*model_]->model_->SetLightGroup(grp);
}

bool Model::RayCast(int* num, RAYCAST_DATA* data)
{/*
	XMMATRIX inv_wld = XMMatrixInverse(nullptr, models_[*num]->trans.GetWorldMatrix());
	XMVECTOR st = XMLoadFloat3(&data->begin);
	XMVECTOR end = 
	{
	data->begin.x + data->end.x,
	data->begin.y + data->end.y,
	data->begin.z + data->end.z,
	};

	st  = XMVector3TransformCoord(st, inv_wld);
	end = XMVector3TransformCoord(end, inv_wld);

	end = end - st;

	XMStoreFloat3(&data->begin, st);
	XMStoreFloat3(&data->end, end);
	*/

	return models_[*num]->model_->RayCast(data);
}

