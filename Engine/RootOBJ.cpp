#include "RootOBJ.h"

RootOBJ::RootOBJ()
{
}

RootOBJ::~RootOBJ()
{
}

void RootOBJ::Initialize()
{
	PlayScene* p_plscn;
	p_plscn = new PlayScene;

	scene_.push_back(p_plscn);
}

void RootOBJ::UpDate()
{
}

void RootOBJ::Draw()
{
}

void RootOBJ::Release()
{
}
