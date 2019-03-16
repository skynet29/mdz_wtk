// MdzCbk3.h: interface for the MdzCbk3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCBK3_H__8B7A3674_6503_4FBC_8C17_14072C3D662C__INCLUDED_)
#define AFX_MDZCBK3_H__8B7A3674_6503_4FBC_8C17_14072C3D662C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzEvent.h"

#define MDZ_CBK3(Class, lpFunc) \
	new MdzCbk3Template<Class>(lpFunc, this)

class DllExport MdzCbk3  
{
public:
	MdzCbk3();
	virtual ~MdzCbk3();
	virtual void Fire(MdzEvent& evt) = 0;

};

template <class T>
class DllExport MdzCbk3Template : public MdzCbk3
{
public:
	typedef void (T::*EvProto) (MdzEvent&);

	void Fire(MdzEvent& evt) {(lpTarget->*lpFunc)(evt);}

	MdzCbk3Template(EvProto lpFunc, T* lpTarget)
	{
		MEMBER_SET(lpFunc);
		MEMBER_SET(lpTarget);
	}
private:
	EvProto lpFunc;
	T* lpTarget;
};

#endif // !defined(AFX_MDZCBK3_H__8B7A3674_6503_4FBC_8C17_14072C3D662C__INCLUDED_)
