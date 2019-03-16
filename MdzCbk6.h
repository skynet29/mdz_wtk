// MdzCbk6.h: interface for the MdzCbk6 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCBK6_H__AF08CE10_2E8A_4DFA_AEB9_693E30B90FDA__INCLUDED_)
#define AFX_MDZCBK6_H__AF08CE10_2E8A_4DFA_AEB9_693E30B90FDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

#define MDZ_CBK6(Class, lpFunc) \
	new MdzCbk6Template<Class>(lpFunc, this)

class DllExport MdzCbk6  
{
public:
	MdzCbk6();
	virtual void Fire(UINT) = 0;
	virtual ~MdzCbk6();

};

template <class T>
class DllExport MdzCbk6Template : public MdzCbk6
{
public:
	typedef void (T::*EvProto)(UINT);

	void Fire(UINT iArg1) {(lpTarget->*lpFunc)(iArg1);}

	MdzCbk6Template(EvProto lpFunc, T* lpTarget)
	{
		MEMBER_SET(lpTarget);
		MEMBER_SET(lpFunc);
	}
private:
	EvProto lpFunc;
	T* lpTarget;
};
#endif // !defined(AFX_MDZCBK6_H__AF08CE10_2E8A_4DFA_AEB9_693E30B90FDA__INCLUDED_)
