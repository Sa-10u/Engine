#include "GOBJ.h"
#include "Collider.h"
#include "SphereCol.h"
#include<cmath>

using std::pow;

bool GOBJ::DoDelProc_ = false;

GOBJ::GOBJ(GOBJ* parent, string name):name_(name),parent_(parent),state_(0), col_(nullptr)
{
	//if(parent != nullptr)	this->trans.parent_ = &(parent->trans);
	(this->*consfunc[static_cast<bool>(parent)])(parent);
}

GOBJ::GOBJ(string name):name_(name),state_(NULL),parent_(nullptr), col_(nullptr)
{
	trans.parent_ = nullptr;
}

GOBJ::GOBJ() :parent_(nullptr), name_(" "), state_(NULL),col_(nullptr)
{
	trans.parent_ = nullptr;
}

void GOBJ::Make_Col(Collider* col)
{
	col_ = col;
}

void GOBJ::Culc(GOBJ* tgt)
{
	if (tgt->col_ == nullptr || tgt->col_ == this->col_)	return;
	float len = Pow_Length(this->trans.pos, tgt->trans.pos);

	if (len <= pow(this->col_->GetRadius() + tgt->col_->GetRadius(),2))
	{
		ColProc();
	}
}

void GOBJ::ColProc()
{
}

void GOBJ::UpdateALL()
{
	Update();
	Culc_ALL(GetRootObj());

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
	for (auto itr = children.begin(); itr != children.end();itr++) {

		(*itr)->ReleaseALL();
		SAFE_DELETE(*itr);
	}
	
	this->Release();
	children.clear();

}

void GOBJ::Culc_ALL(GOBJ* tgt)
{

	if (this->col_ == nullptr)		return;

	if(tgt->col_ != this->col_)		Culc(tgt);

	for (auto itr : tgt->children) {

		Culc_ALL(itr);
	}
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
			SAFE_DELETE(*itr);
			itr = children.erase(itr); //itr++ is error !

		}
		else
		{
			itr++;
		}
	}
}

GOBJ* GOBJ::FindObject_ALL(string name)
{
	GOBJ* obj = nullptr;
	obj = GetRootObj();

	return obj->FindObject_Child(name);
}

GOBJ* GOBJ::FindObject_Child(string name)
{
	if (name == this->name_)
	{
		return this;
	}

	for (auto itr : children) {

		return itr->FindObject_Child(name);
	}

	return nullptr;
}

list<GOBJ*> GOBJ::FindObject_Children(string name)
{
	list<GOBJ*> cluster;

	if (name == this->name_)
	{
		cluster.push_back(this);
	}

	for (auto itr : children) {

		itr->FindObject_Children(name);
	}

	return cluster;
}

GOBJ* GOBJ::GetRootObj()
{
	if (this->parent_ == nullptr)	return this;

	return parent_->GetRootObj();
}

void GOBJ::consfunc1(GOBJ* p)
{
	this->trans.parent_ = nullptr;
}

void GOBJ::consfunc2(GOBJ* p)
{
	this->trans.parent_ = &(p->trans);
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
