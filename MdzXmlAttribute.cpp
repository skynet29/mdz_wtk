// MdzXmlAttribute.cpp: implementation of the MdzXmlAttribute class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzXmlAttribute.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzXmlAttribute::MdzXmlAttribute(LPSTR strName, LPSTR strValue)
{
	MEMBER_SET(strName);
	MEMBER_SET(strValue);
}

MdzXmlAttribute::~MdzXmlAttribute()
{

}

char* MdzXmlAttribute::GetValue()
{
	return strValue;
}

MdzString MdzXmlAttribute::GetName()
{
	return strName;
}

void MdzXmlAttribute::SetValue(LPSTR strValue)
{
	MEMBER_SET(strValue);
}