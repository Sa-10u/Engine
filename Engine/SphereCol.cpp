#include "SphereCol.h"

inline double Pow_Length(const XMFLOAT3& th, const XMFLOAT3& se)
{
	return (pow(th.x - se.x, 2) + pow(th.y - se.y, 2) + pow(th.z - se.z, 2));
}

SphereCol::SphereCol(GOBJ* parent):Collider(parent)
{
}

SphereCol::SphereCol(float len, XMFLOAT3 pos , GOBJ* parent):Collider(len,pos ,parent)
{
}

SphereCol::~SphereCol()
{
}

bool SphereCol::IsHit(GOBJ* tgt)
{
	for (auto itr : cols) {
		if (itr->GetParent() == tgt)
		{

			float len = Pow_Length(this->trans.pos, itr->GetPos());

			if (len <= pow(this->GetRadius() + itr->GetRadius(), 2))
			{
				return true;
			}
		}
	}

	return false;
}
