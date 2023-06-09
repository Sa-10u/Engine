#pragma once

template<typename tgt>
inline void SAFE_DELETE(tgt* p)
{
	
	if (! (p == nullptr)) //funcptr
	{
		delete p;
		p = nullptr;
	}
}

template<typename tgt>
inline void SAFE_RELEASE(tgt* p)
{
	
	if (!(p == nullptr))
	{
		p->Release();
		p = nullptr;
	}

}



static void(*Process[2])(bool i) = {};