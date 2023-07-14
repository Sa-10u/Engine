#include "Player.h"
#include"Engine/FBX.h"
#include"Engine/DInput.h"
#include"Engine/Model.h"
#include "child.h"

Player::Player(GOBJ* parent):model_(nullptr),GOBJ(parent,"Player")
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	m_ = Model::Load("Assets/O-DEN.fbx");

	trans.size.x = 0.5;
	trans.size.y = 0.5;
	trans.size.z = 0.5;

	Model::SetShader(&m_,SHADER_TYPE::SHADER_CELL3D);

	/*
	child* c1 = Make<child>(this);
	child* c2 = Make<child>(this);

	c1->trans.pos.y = 1;
	c2->trans.pos.y = 1;

	c1->trans.pos.z = 2;
	c2->trans.pos.z = -2;
	*/
}

void Player::Update()
{
	trans.rot.y += 0.1 ;

	if (Input::IsKey(DIK_A))	trans.pos.x -= 0.1;
	if (Input::IsKey(DIK_D))	trans.pos.x += 0.1;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		child *c = Make<child>(parent_);
		c->trans.pos = this->trans.pos;
	}

	if (Input::IsKey(DIK_ESCAPE))	PostQuitMessage(0);
}

void Player::Draw()
{
	Model::Draw(&m_, &trans, SHADER_TYPE::SHADER_CELL3D);
}

void Player::Release()
{
	model_->Release();
	delete model_;
}
