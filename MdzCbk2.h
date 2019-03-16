// MdzCbk2.h: interface for the MdzCbk2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCBK2_H__43F872E2_B13C_4EB4_A8B2_E3358EA0D6CB__INCLUDED_)
#define AFX_MDZCBK2_H__43F872E2_B13C_4EB4_A8B2_E3358EA0D6CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"


#define MDZ_CBK2(Class, lpFunc) \
	new MdzCbk2Template<Class>(lpFunc, this)


class DllExport MdzCbk2  
{
public:
	virtual void Fire(int x, int y) = 0;
    virtual ~MdzCbk2() {}
};

template <class T>
class DllExport MdzCbk2Template : public MdzCbk2  
{
public:
	typedef void (T::*EvProto)(int, int);

	void Fire(int x, int y) {(lpTarget->*lpFunc)(x, y);}

	MdzCbk2Template(EvProto lpFunc, T* lpTarget)
	{
		MEMBER_SET(lpTarget);
		MEMBER_SET(lpFunc);
	}
private:
	EvProto lpFunc;
	T* lpTarget;
};
#endif // !defined(AFX_MDZCBK2_H__43F872E2_B13C_4EB4_A8B2_E3358EA0D6CB__INCLUDED_)
