#include "Collider.h"

Collider::Collider() :rad_(1.0)
{
}

Collider::Collider(float len, XMFLOAT3 pos) :rad_(len)
{
}

Collider::~Collider()
{
}

float Collider::GetRadius()
{
    return rad_;
}

XMFLOAT3 Collider::GetPos()
{
    return XMFLOAT3();
}

void Collider::SetRadius(float len)
{
    rad_ = len;
}

void Collider::SetPos(XMFLOAT3 pos)
{

}