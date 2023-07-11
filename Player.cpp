#include "Player.h"
#include"Engine/FBX.h"
#include"Engine/DInput.h"


Player::Player(GOBJ* parent):model_(nullptr),GOBJ(parent,"Player")
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	model_ = new Fbx;
	model_->Load("Assets/O-DEN.fbx");
	trans.size.x = 0.5;
	trans.size.y = 0.5;
	trans.size.z = 0.5;

	model_->SetShaderType(SHADER_TYPE::SHADER_CELL3D);
}

void Player::Update()
{
	trans.rot.y += 0.1 ;

	if (Input::IsKey(DIK_A))	KillMe();
	if (Input::IsKey(DIK_W))	PostQuitMessage(0);
}

void Player::Draw()
{
	model_->Draw(&trans, XMFLOAT4(1, 1, 1, 0), XMFLOAT4(0.8, 0, 0, 0));
}

void Player::Release()
{
	model_->Release();
	delete model_;
}
