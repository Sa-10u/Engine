#include "child.h"
#include "Engine/DInput.h"
#include "Engine/Model.h"
#include "Engine/SphereCol.h"

child::child(GOBJ* parent) :model_(nullptr), GOBJ(parent, "child"),m_(-1)
{
}

child::~child()
{
}

void child::Initialize()
{
	m_ = Model::Load("Assets/O-DEN.fbx");
	assert(m_ >= 0);

	trans.size = XMFLOAT3{ 0.2,0.2,0.2 };
	trans.rot.y = 3.141592/2;

	Model::SetLightGroup(&m_, &(LightManager->Light_Path1));
	Model::SetShader(&m_, SHADER_TYPE::SHADER_CELL3D);

	SphereCol* col = new SphereCol(2, trans.pos);
	Make_Col(col);
	
}

void child::Update()
{
//	trans.rot.y += 0.2;

//	if (Input::IsKey(DIK_A))	trans.pos.x -= 0.1;
	//if (Input::IsKey(DIK_D))	trans.pos.x += 0.1;

	trans.pos.z += 0.3;

	if (trans.pos.z > 20.0) KillMe();
}

void child::Draw()
{
	Model::Draw(&m_ , &trans , SHADER_TYPE::SHADER_POINT3D);
}

void child::Release()
{
}
