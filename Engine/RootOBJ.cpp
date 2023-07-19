#include "RootOBJ.h"
#include "SceneManager.h"

RootOBJ::RootOBJ(GOBJ* parent):GOBJ(parent ,"RootOBJ")
{
}

RootOBJ::~RootOBJ()
{
}

void RootOBJ::Initialize()
{
	Make<SceneManager>(this);
}

void RootOBJ::Update()
{

}

void RootOBJ::Draw()
{

}

void RootOBJ::Release()
{
	for (auto itr : children) {

		itr->ReleaseALL();
	}
}

void RootOBJ::Disposal()
{
	for (auto itr : children) {

		itr->Disposal();
	}
}




