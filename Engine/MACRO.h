#pragma once
#include<DirectXMath.h>
#include <cmath>
using namespace DirectX;

template<typename tgt>
inline void SAFE_DELETE(tgt* &p)
{
	
	if ( (p != nullptr)) 
	{
		delete p;
		p = nullptr;
	}
}

template<typename tgt>
inline void SAFE_RELEASE(tgt* &p)
{
	
	if ((p != nullptr))
	{
		p->Release();
		p = nullptr;
	}
	
}

#define ARRAY_WITH_SIZE(vx)  vx , static_cast<int>(sizeof(vx))

constexpr int LIGHT_AMMOUNT = 10;


inline XMFLOAT3 operator+ (const XMFLOAT3& th ,const XMFLOAT3& se)
{
	return XMFLOAT3(th.x + se.x, th.y + se.y, th.z + se.z);
}

inline XMFLOAT3 operator- (const XMFLOAT3& th, const XMFLOAT3& se)
{
	return XMFLOAT3(th.x - se.x, th.y - se.y, th.z - se.z);
}

inline double Pow_Length(const XMFLOAT3& th, const XMFLOAT3& se)
{
	return (pow(th.x - se.x, 2) + pow(th.y - se.y, 2) + pow(th.z - se.z, 2));
}