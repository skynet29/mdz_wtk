// MdzXmlElement.cpp: implementation of the MdzXmlElement class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzXmlElement.h"
#include "MdzXmlAttribute.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzXmlElement::MdzXmlElement(LPSTR strName)
{
	MEMBER_SET(strName);
	pParent = NULL;
}

MdzXmlElement::MdzXmlElement()
{
	pParent = NULL;
}

void MdzXmlElement::SetName(LPSTR strName)
{
	MEMBER_SET(strName);
}

MdzXmlElement::~MdzXmlElement()
{
	childs.RemoveAll(TRUE);
	attributes.RemoveAll(TRUE);
}

void MdzXmlElement::AddChild(MdzXmlElement *pElt)
{
	childs.Add(pElt);
	pElt->pParent = this;
}

MdzXmlElement* MdzXmlElement::GetParent()
{
	return pParent;
}

UINT MdzXmlElement::GetChildCount()
{
	return childs.GetCount();
}

MdzXmlElement* MdzXmlElement::GetChildAt(UINT iIndex)
{
	return &childs[iIndex];
}

void MdzXmlElement::AddAttribute(MdzXmlAttribute *pAttribute)
{
	attributes.Add(pAttribute);
}

MdzXmlAttribute* MdzXmlElement::GetAttribute(LPSTR strName)
{
	for(UINT i=0; i < attributes.GetCount(); i++)
	{
		MdzXmlAttribute* attr = &attributes[i];
		if (attr->GetName().Equals(strName))
			return attr;
	}
	return NULL;
}

char* MdzXmlElement::GetAttributeValue(LPSTR strName)
{
	MdzXmlAttribute* attr = GetAttribute(strName);
	return (attr != NULL) ? attr->GetValue() : NULL;
}


MdzString MdzXmlElement::GetName()
{
	return strName;
}

UINT MdzXmlElement::GetPosition()
{
	UINT iPos = 0;
	MdzXmlElement* pElt = GetParent();
	while (pElt)
	{
		iPos++;
		pElt = pElt->GetParent();
	}
	return iPos;

}

UINT MdzXmlElement::GetAttributeCount()
{
	return attributes.GetCount();
}

MdzXmlAttribute* MdzXmlElement::GetAttributeAt(UINT iIndex)
{
	return &attributes[iIndex];
}

MdzXmlElement* MdzXmlElement::GetChildByName(LPSTR strName)
{
	for(int i = 0; i < (int)childs.GetCount(); i++)
	{
		if (childs[i].GetName().Equals(strName))
			return &childs[i];
	}
	return NULL;
}
