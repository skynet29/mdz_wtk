// MdzCbk4.h: interface for the MdzCbk4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCBK4_H__EDB359BA_920C_4534_AD59_FFFF19C106AC__INCLUDED_)
#define AFX_MDZCBK4_H__EDB359BA_920C_4534_AD59_FFFF19C106AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class MdzGraphic;


#define MDZ_CBK4(Class, lpFunc) \
	new MdzCbk4Template<Class>(lpFunc, this)


class DllExport MdzCbk4  
{
public:
	virtual void Fire(MdzGraphic& graphic) = 0;
    virtual ~MdzCbk4() {}
};

template <class T>
class DllExport MdzCbk4Template : public MdzCbk4  
{
public:
	typedef void (T::*EvProto)(MdzGraphic&);

	void Fire(MdzGraphic& graphic) {(lpTarget->*lpFunc)(graphic);}

	MdzCbk4Template(EvProto lpFunc, T* lpTarget)
	{
		MEMBER_SET(lpFunc);
		MEMBER_SET(lpTarget);
	}
private:
	EvProto lpFunc;
	T* lpTarget;
};

#endif // !defined(AFX_MDZCBK4_H__EDB359BA_920C_4534_AD59_FFFF19C106AC__INCLUDED_)
