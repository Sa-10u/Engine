#include "child.h"
#include "Engine/DInput.h"

child::child(GOBJ* parent) :model_(nullptr), GOBJ(parent, "child")
{
}

child::~child()
{
}

void child::Initialize()
{
	model_ = new Fbx();
	model_->Load("Assets/O-DEN.fbx");

	trans.size = XMFLOAT3{ 0.2,0.2,0.2 };
	trans.pos.x = 2.5;
}

void child::Update()
{
	trans.rot.y += 0.2;

	if (Input::IsKey(DIK_A))	trans.pos.x -= 0.1;
	if (Input::IsKey(DIK_D))	trans.pos.x += 0.1;
}

void child::Draw()
{
	model_->Draw(&trans, XMFLOAT4(1, 1, 1, 0), XMFLOAT4(0.8, 0, 0, 0));
}

void child::Release()
{
}
