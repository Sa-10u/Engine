#include "Collider.h"

Collider::Collider(GOBJ* parent) :rad_(1.0),parent_(parent)
{
    cols.push_back(this);
}

Collider::Collider(float len, XMFLOAT3 pos,GOBJ* parent) :rad_(len),parent_(parent)
{
    trans.pos = pos;

    cols.push_back(this);
}

Collider::~Collider()
{
    cols.remove(this);
}

float Collider::GetRadius()
{
    return rad_;
}

XMFLOAT3 Collider::GetPos()
{
    return trans.pos;
}

GOBJ* Collider::GetParent()
{
    return parent_;
}

void Collider::SetRadius(float len)
{
    rad_ = len;
}

void Collider::SetPos(XMFLOAT3 pos)
{
    trans.pos = pos;
}

void Collider::SetParent(GOBJ* p)
{
    parent_ = p;
}

void Collider::SetFunc(void (*rum)())
{
    func = rum;
}

void Collider::OnCol(GOBJ* tgt)
{
    if (this->IsHit(tgt))
    {
        return;
    }
    
}

void Collider::OnCol(GOBJ* tgt, void rum())
{
    SetFunc(rum);

    if (IsHit(tgt))
    {
        return;
    }

}
