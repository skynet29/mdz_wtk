// MdzXmlParser.h: interface for the MdzXmlParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZXMLPARSER_H__5750A470_EFC4_4904_8E11_77BE8727E72F__INCLUDED_)
#define AFX_MDZXMLPARSER_H__5750A470_EFC4_4904_8E11_77BE8727E72F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include <stdio.h>

class MdzXmlElement;

class DllExport MdzXmlParser  
{
public:
	BOOL Open(LPSTR strFileName);
	MdzXmlElement* Parse();
	MdzXmlParser();
	virtual ~MdzXmlParser();
private:
	MdzXmlElement* ParseParameters(LPSTR pBuff);
	FILE* pFile;
protected:
	virtual MdzXmlElement* OnNewElement(LPSTR strName);

};

#endif // !defined(AFX_MDZXMLPARSER_H__5750A470_EFC4_4904_8E11_77BE8727E72F__INCLUDED_)
