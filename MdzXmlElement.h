// MdzXmlElement.h: interface for the MdzXmlElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZXMLELEMENT_H__96AAF796_2EE5_4C95_9C72_178FD7BB4353__INCLUDED_)
#define AFX_MDZXMLELEMENT_H__96AAF796_2EE5_4C95_9C72_178FD7BB4353__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzVector.h"
#include "MdzString.h"

class MdzXmlAttribute;

class DllExport MdzXmlElement  : public MdzObject 
{
public:
	MdzXmlElement(LPSTR strName);
	MdzXmlElement();
	virtual ~MdzXmlElement();

	MdzXmlElement* GetChildByName(LPSTR strName);
	MdzXmlAttribute* GetAttributeAt(UINT iIndex);
	MdzXmlAttribute* GetAttribute(LPSTR strName);
	char* GetAttributeValue(LPSTR strName);
	UINT GetAttributeCount();
	UINT GetPosition();
	MdzString GetName();
	MdzXmlElement* GetChildAt(UINT iIndex);
	UINT GetChildCount();
	MdzXmlElement* GetParent();

	void SetName(LPSTR strName);


	void AddAttribute(MdzXmlAttribute* pAttribute);
	void AddChild(MdzXmlElement* pElt);
private:
	MdzVectorT<MdzXmlElement> childs;
	MdzVectorT<MdzXmlAttribute> attributes;
	MdzXmlElement* pParent;
	MdzString strName;
};

#endif // !defined(AFX_MDZXMLELEMENT_H__96AAF796_2EE5_4C95_9C72_178FD7BB4353__INCLUDED_)
