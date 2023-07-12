#include "Light.h"

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
{/*empty*/ }


void Light::Stop()
{
	intensity = 0.0;
}

void Light::DelCol()
{
}



