#include "GOBJ.h"

GOBJ::GOBJ(GOBJ* parent, const char* name):name_(name),parent_(parent),state_(0)
{
}

GOBJ::GOBJ():parent_(this),name_(nullptr),state_(NULL)
{
}

void GOBJ::UpdateALL()
{
	Update();
	for (auto itr : children) {

		itr->UpdateALL();
	}
}

void GOBJ::DrawALL()
{
	Draw();
	for (auto itr : children) {

		itr->DrawALL();
	}
}

void GOBJ::KillMe()
{
	state_ |= static_cast<int>(OBJ_STATE::KILL);
}

void GOBJ::Stop()
{
	state_ |= static_cast<int>(OBJ_STATE::STOP);
}

void GOBJ::DelCol()
{
}

list<GOBJ*> GOBJ::GetChildren()
{
	return list<GOBJ*>();
}
