#include "GOBJ.h"
bool GOBJ::DoDelProc_ = false;



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

void GOBJ::ReleaseALL()
{
	for (auto itr : children) {

		itr->ReleaseALL();
		
		
	}
	
	this->Release();
	this->GetParent()->children.remove(this);
}

void GOBJ::KillMe()
{
	state_ |= static_cast<int>(OBJ_STATE::KILL);
	GOBJ::DoDelProc_ = true;
}

void GOBJ::Stop()
{
	state_ |= static_cast<int>(OBJ_STATE::STOP);
}

void GOBJ::DelCol()
{
}

void GOBJ::Disposal()
{
	for (auto itr = children.begin(); itr != children.end(); true ) {
		(*itr)->Disposal();
		
		if ((*itr)->IsDead())
		{
			(*itr)->ReleaseALL();
		}
		else
		{
			itr++;
		}
	}
}

list<GOBJ*> GOBJ::GetChildren()
{
	return children;
}

GOBJ* GOBJ::GetParent()
{
	return parent_;
}

bool GOBJ::IsDead()
{
	return (state_ & static_cast<int>(OBJ_STATE::KILL));
}

bool GOBJ::IsDisposal()
{
	return DoDelProc_;
}

void GOBJ::EndDisposal()
{
	DoDelProc_ = false;
}

void GOBJ::EmptyWork()
{
	//Empty
}
