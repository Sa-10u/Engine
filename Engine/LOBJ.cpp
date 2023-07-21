#include "LOBJ.h"
#include"LIGHTMANAGER.h"

LIGHTMANAGER* LIGHTMANAGER::inst_ = nullptr;
LIGHTMANAGER* LightManager = LIGHTMANAGER::GetInstance();

LOBJ::LOBJ( string name):name(name), intensity(0), color(XMFLOAT4{0,0,0,0}),selfpointer_(nullptr)
{
	
}

LOBJ::LOBJ():name("LOBJ"), intensity(0), color(XMFLOAT4{0,0,0,0}), selfpointer_(nullptr)
{
}

LOBJ::~LOBJ()
{	
}

void LOBJ::Release()
{
	delete selfpointer_;
	selfpointer_ = nullptr;
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
		me[i] = nullptr;
	}
}

LIGHTMANAGER::LightGroup::~LightGroup()
{
}

void LIGHTMANAGER::LightGroup::Release()
{
	for (auto itr : me) {

		if(itr != nullptr)		itr->Release();
	};

}

void LIGHTMANAGER::LightGroup::Make(LOBJ* &lght)
{
	for (auto itr : me) {
		//////
	}
}
//----------------------------

P_LOBJ::P_LOBJ( string name ):LOBJ(name)
{
	LightType = LIGHT_TYPE::POINT;
}

P_LOBJ::~P_LOBJ()
{
}

P_LOBJ* P_LOBJ::Make_Light()
{
	return nullptr;
}

void P_LOBJ::Initialize()
{
}

P_LOBJ::P_LOBJ():LOBJ("P_LOBJ")
{
}

void P_LOBJ::Update()
{
}

void P_LOBJ::Draw()
{
}
//---------------

S_LOBJ::S_LOBJ( string name):LOBJ(name)
{
	LightType = LIGHT_TYPE::SUN;
}



S_LOBJ::~S_LOBJ()
{
}

LOBJ* S_LOBJ::Make_Light()
{
	return nullptr;
}

void S_LOBJ::Initialize()
{
}

void S_LOBJ::Update()
{
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
	
		LIGHTGROUP[i]->Release();
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
