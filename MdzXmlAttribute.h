// MdzXmlAttribute.h: interface for the MdzXmlAttribute class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZXMLATTRIBUTE_H__AB8B58DE_DE15_4F9E_B746_14DE155E5A89__INCLUDED_)
#define AFX_MDZXMLATTRIBUTE_H__AB8B58DE_DE15_4F9E_B746_14DE155E5A89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzString.h"

class DllExport MdzXmlAttribute : public MdzObject 
{
public:
	MdzString GetName();
	char* GetValue();
	void SetValue(LPSTR strValue);

	MdzXmlAttribute(LPSTR strName, LPSTR strValue);
	virtual ~MdzXmlAttribute();
private:
	MdzString strName;
	MdzString strValue;
};

#endif // !defined(AFX_MDZXMLATTRIBUTE_H__AB8B58DE_DE15_4F9E_B746_14DE155E5A89__INCLUDED_)
