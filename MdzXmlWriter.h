// MdzXmlWriter.h: interface for the MdzXmlWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZXMLWRITER_H__D908EEF5_C5A2_4299_90E3_EDF39A90679E__INCLUDED_)
#define AFX_MDZXMLWRITER_H__D908EEF5_C5A2_4299_90E3_EDF39A90679E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include <stdio.h>

class DllExport MdzXmlWriter  
{
public:
	void Close();
	void WriteAttribute(LPSTR strName, LPSTR strValue);
	void WriteEndElement();
	void WriteStartElement(LPSTR strName);
	MdzXmlWriter(LPSTR strFileName);
	virtual ~MdzXmlWriter();
private:
	void WriteIndent();
	FILE* pFile;
	int nLevel;
	BOOL bNeedClose;
	LPSTR stack[30];

};

#endif // !defined(AFX_MDZXMLWRITER_H__D908EEF5_C5A2_4299_90E3_EDF39A90679E__INCLUDED_)
