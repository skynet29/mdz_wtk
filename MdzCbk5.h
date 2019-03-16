// MdzCbk5.h: interface for the MdzCbk5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCBK5_H__71571AFF_E302_4D4A_AC99_00B9DC73AF29__INCLUDED_)
#define AFX_MDZCBK5_H__71571AFF_E302_4D4A_AC99_00B9DC73AF29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

#define MDZ_CBK5(Class, lpFunc) \
	new MdzCbk5Template<Class>(lpFunc, this)

class DllExport MdzCbk5  
{
public:
	MdzCbk5();
	virtual ~MdzCbk5();
	virtual BOOL Fire() = 0;

};

template <class T>
class DllExport MdzCbk5Template : public MdzCbk5  
{
public:
	typedef BOOL (T::*EvProto)();

	BOOL Fire() {return (lpTarget->*lpFunc)();}

	MdzCbk5Template(EvProto lpFunc, T* lpTarget)
	{
		MEMBER_SET(lpFunc);
		MEMBER_SET(lpTarget);
	}
private:
	EvProto lpFunc;
	T* lpTarget;
};

#endif // !defined(AFX_MDZCBK5_H__71571AFF_E302_4D4A_AC99_00B9DC73AF29__INCLUDED_)
