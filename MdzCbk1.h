// MdzCbk1.h: interface for the MdzCbk1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCBK1_H__7CBE212F_7FDA_4209_A70B_90F8C3E74288__INCLUDED_)
#define AFX_MDZCBK1_H__7CBE212F_7FDA_4209_A70B_90F8C3E74288__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"


#define MDZ_CBK1(Class, lpFunc) \
	new MdzCbk1Template<Class>(lpFunc, this)

#define MDZ_ARGCBK1(Class, lpArg, lpFunc) \
	new MdzCbk1TemplateEx<Class>(lpFunc, lpArg, this)

class DllExport MdzCbk1
{
public:
	virtual void Fire() = 0;
    virtual ~MdzCbk1() {}
};

template <class T>
class DllExport MdzCbk1Template : public MdzCbk1
{
public:
	typedef void (T::*EvProto) ();

	void Fire() {(lpTarget->*lpFunc)();}

	MdzCbk1Template(EvProto lpFunc, T* lpTarget)
	{
		MEMBER_SET(lpFunc);
		MEMBER_SET(lpTarget);
	}
private:
	EvProto lpFunc;
	T* lpTarget;
};

template <class T>
class DllExport MdzCbk1TemplateEx : public MdzCbk1
{
public:
	typedef void (T::*EvProto) (LPVOID);

	void Fire() {(lpTarget->*lpFunc)(lpArg);}

	MdzCbk1TemplateEx(EvProto lpFunc, LPVOID lpArg, T* lpTarget)
	{
		MEMBER_SET(lpFunc);
		MEMBER_SET(lpTarget);
		MEMBER_SET(lpArg);
	}
private:
	EvProto lpFunc;
	T* lpTarget;
	LPVOID lpArg;
};

#endif // !defined(AFX_MDZCBK1_H__7CBE212F_7FDA_4209_A70B_90F8C3E74288__INCLUDED_)
