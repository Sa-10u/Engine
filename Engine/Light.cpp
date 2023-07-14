#include "Light.h"

LIGHTMANAGER* LIGHTMANAGER::inst_ = nullptr;
LIGHTMANAGER* LightManager = LIGHTMANAGER::GetInstance();

Light::Light(GOBJ* parent, const char* name):GOBJ(parent,name),intensity(0),color(XMFLOAT4{0,0,0,0})
{
	trans.parent_ = &parent->trans;
}

Light::Light(const char* name):GOBJ(name), intensity(0), color(XMFLOAT4{ 0,0,0,0 })
{
}

Light::Light():GOBJ(), intensity(0), color(XMFLOAT4{ 0,0,0,0 })
{
}

Light::~Light()
{

}
void Light::Draw()
{
}
int Light::GetType()
{
	return (static_cast<int>(LightType));
}
//--------------------------------------

LIGHTMANAGER::LightGroup::LightGroup() :index_(0)
{
	for (int i = 0; i < LIGHT_AMMOUNT; i++) {
		me[i] = new P_Light();
	}
}

LIGHTMANAGER::LightGroup::~LightGroup()
{
	delete[] me;
}

void LIGHTMANAGER::LightGroup::Release()
{
	for (int i = 0; i < LIGHT_AMMOUNT; i++) {

		me[i]->trans.pos = { 0,0,0 };
		me[i]->color = { 0,0,0,0 };
		me[i]->intensity = 0.0;
	}
}

void LIGHTMANAGER::LightGroup::Make(Light* &lght)
{
	index_ = index_ % LIGHT_AMMOUNT;

	delete me[index_];
	me[index_] = lght;

	delete lght;
	lght = me[index_];

	index_++;
}
//----------------------------

P_Light::P_Light(GOBJ* parent, const char* name):Light(parent,name)
{
	LightType = LIGHT_TYPE::POINT;
}

P_Light::P_Light(const char* name) :Light( name)
{
	LightType = LIGHT_TYPE::POINT;
}

P_Light::P_Light() :Light()
{
	LightType = LIGHT_TYPE::POINT;
}

P_Light::~P_Light()
{
}

void P_Light::Initialize()
{
}

void P_Light::Update()
{
}

void P_Light::Release()
{
	trans.pos = { 0,0,0 };
	color = { 0,0,0,0 };
	intensity = 0.0;
}
void P_Light::Draw()
{
}
//---------------

S_Light::S_Light(GOBJ* parent, const char* name)
{
	LightType = LIGHT_TYPE::SUN;
}

S_Light::S_Light(const char* name)
{
	LightType = LIGHT_TYPE::SUN;
}

S_Light::S_Light()
{
	LightType = LIGHT_TYPE::SUN;
}

S_Light::~S_Light()
{
}

void S_Light::Initialize()
{
}

void S_Light::Update()
{
}

void S_Light::Release()
{
	trans.pos = { 0,0,0 };
	color = { 0,0,0,0 };
	intensity = 0.0;
}
void S_Light::Draw()
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
	delete LIGHTMANAGER::inst_;
	LIGHTMANAGER::inst_ = nullptr;
}

LIGHTMANAGER::LIGHTMANAGER()
{
}

LIGHTMANAGER::~LIGHTMANAGER()
{
}
