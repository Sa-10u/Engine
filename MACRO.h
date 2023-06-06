#pragma once

template<typename tgt>
inline void SAFE_DELETE(tgt* p)
{
	delete p;
	if (! (p = nullptr)) //funcptr
	{
		p = nullptr;
	}
}

template<typename tgt>
inline void SAFE_RELEASE(tgt* p)
{
	p->Release();
	if (!(p = nullptr))
	{
		p = nullptr;
	}

}



static void(*Process[2])(bool i) = {};