// MdzClassFactory.h: interface for the MdzClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCLASSFACTORY_H__EE88271F_905A_49D6_B0C7_259CCD949FE2__INCLUDED_)
#define AFX_MDZCLASSFACTORY_H__EE88271F_905A_49D6_B0C7_259CCD949FE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzString.h"


class DllExport MdzClassFactory  
{
public:
	static LPVOID CreateObject(LPSTR strClassName);
	// Constructor
	MdzClassFactory(LPSTR strClassName);

	// Destructor
	virtual ~MdzClassFactory();

	// Methods
	virtual LPVOID NewObject() = 0;

	// Class method
	static MdzClassFactory*
	GetFactory(LPSTR lpClassName);

protected:
	MdzString strClassName;
private:
	MdzClassFactory* lpNext;
};

template <class T>
class MdzClassFactoryTemplate : public MdzClassFactory
{
public:
	MdzClassFactoryTemplate(LPSTR strClassName) : MdzClassFactory(strClassName) {}

	virtual LPVOID NewObject() {return new T();}
};

#define MDZ_DECLARE_FACTORY(ClassType) \
	static MdzClassFactoryTemplate<ClassType> ClassType##Factory(#ClassType);


#endif // !defined(AFX_MDZCLASSFACTORY_H__EE88271F_905A_49D6_B0C7_259CCD949FE2__INCLUDED_)
