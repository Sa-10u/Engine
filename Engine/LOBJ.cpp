#include "LOBJ.h"
#include"LIGHTMANAGER.h"

LIGHTMANAGER* LIGHTMANAGER::inst_ = nullptr;
LIGHTMANAGER* LightManager = LIGHTMANAGER::GetInstance();

LOBJ::LOBJ(LOBJ* parent, string name):parent(parent),name(name), intensity(0), color(XMFLOAT4{0,0,0,0})
{
	trans.parent_ = &parent->trans;
}

LOBJ::LOBJ(string name) :parent(nullptr), name(name), intensity(0), color(XMFLOAT4{ 0,0,0,0 })
{
}

LOBJ::LOBJ(LOBJ* parent)
{
}

LOBJ::LOBJ():parent(nullptr),name(" "), intensity(0), color(XMFLOAT4{0,0,0,0})
{
}

LOBJ::~LOBJ()
{

}
void LOBJ::Draw()
{
}
int LOBJ::GetType()
{
	return (static_cast<int>(LightType));
}
//--------------------------------------

LIGHTMANAGER::LightGroup::LightGroup() :index_(0)
{
	for (int i = 0; i < LIGHT_AMMOUNT; i++) {
		me[i] = new P_LOBJ();
	}
}

LIGHTMANAGER::LightGroup::~LightGroup()
{
	delete[] me;
}

void LIGHTMANAGER::LightGroup::Release()
{
	delete[] me;

	for (int i = 0; i < LIGHT_AMMOUNT; i++) {

		me[i] = nullptr;
	}
}

void LIGHTMANAGER::LightGroup::Make(LOBJ* &lght)
{
	for (int i = 0; i < LIGHT_AMMOUNT; i++) {



	}
}
//----------------------------

P_LOBJ::P_LOBJ(LOBJ* parent, string name):LOBJ(parent,name)
{
	LightType = LIGHT_TYPE::POINT;
}

P_LOBJ::P_LOBJ(string name) :LOBJ( name)
{
	LightType = LIGHT_TYPE::POINT;
}

P_LOBJ::P_LOBJ() :LOBJ()
{
	LightType = LIGHT_TYPE::POINT;
}

P_LOBJ::~P_LOBJ()
{
}

void P_LOBJ::Initialize()
{
}

void P_LOBJ::Update()
{
}

void P_LOBJ::Release()
{
	trans.pos = { 0,0,0 };
	color = { 0,0,0,0 };
	intensity = 0.0;
}
void P_LOBJ::Draw()
{
}
//---------------

S_LOBJ::S_LOBJ(LOBJ* parent, string name)
{
	LightType = LIGHT_TYPE::SUN;
}

S_LOBJ::S_LOBJ(string name)
{
	LightType = LIGHT_TYPE::SUN;
}

S_LOBJ::S_LOBJ()
{
	LightType = LIGHT_TYPE::SUN;
}

S_LOBJ::~S_LOBJ()
{
}

void S_LOBJ::Initialize()
{
}

void S_LOBJ::Update()
{
}

void S_LOBJ::Release()
{
	trans.pos = { 0,0,0 };
	color = { 0,0,0,0 };
	intensity = 0.0;
}
void S_LOBJ::Draw()
{
}
//------------

LIGHTMANAGER* LIGHTMANAGER::GetInstance()
{
	if (LIGHTMANAGER::inst_ == nullptr)	inst_ = new LIGHTMANAGER;

	return inst_;
}

void LIGHTMANAGER::Release()
{
	for (int i = 0; i < sizeof(LIGHTGROUP) / sizeof(LightGroup); i++) {
	
		delete[] LIGHTGROUP[i]->me;
	}
	delete[] LIGHTGROUP;

	delete LIGHTMANAGER::inst_;
	LIGHTMANAGER::inst_ = nullptr;
}

LIGHTMANAGER::LIGHTMANAGER()
{
}

LIGHTMANAGER::~LIGHTMANAGER()
{
}
