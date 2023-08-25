#include "Enemy.h"
#include"Engine/LIGHTMANAGER.h"
#include "Engine/SphereCol.h"

Enemy::Enemy(GOBJ* parent):GOBJ(parent,"Enemy"),m_(-1)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	m_ = Model::Load("Assets/O-DEN.fbx");
	trans.rot.y = 90;
	trans.size = XMFLOAT3(0.5, 0.5, 0.5);
	trans.pos.z = 6;

	col = new SphereCol(3, trans.pos, this);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetLightGroup(&m_, &(LightManager->Light_Path1));
	Model::Draw(&m_,&trans,SHADER_TYPE::SHADER_3D);
}

void Enemy::Release()
{
}
