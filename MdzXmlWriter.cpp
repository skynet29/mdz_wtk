// MdzXmlWriter.cpp: implementation of the MdzXmlWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzXmlWriter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzXmlWriter::MdzXmlWriter(LPSTR strFileName)
{
	pFile = fopen(strFileName, "w");
	nLevel = 0;
	bNeedClose = FALSE;
}

MdzXmlWriter::~MdzXmlWriter()
{
	fclose(pFile);
}

void MdzXmlWriter::WriteStartElement(LPSTR strName)
{
		if (bNeedClose) 
			fprintf(pFile, ">\n");
		WriteIndent();
		fprintf(pFile, "<%s", strName); 
		stack[nLevel++] = strdup(strName);
		bNeedClose = TRUE;

}

void MdzXmlWriter::WriteIndent()
{
	for(int i=0; i < nLevel; i++) fprintf(pFile, "\t");

}

void MdzXmlWriter::WriteEndElement()
{
		if (bNeedClose) 
			fprintf(pFile, ">\n");
		bNeedClose = FALSE;
		LPSTR strName = stack[--nLevel];
		WriteIndent();
		fprintf(pFile, "</%s>\n", strName);
		free(strName);

}

void MdzXmlWriter::WriteAttribute(LPSTR strName, LPSTR strValue)
{
		fprintf(pFile, " %s=\"%s\"", strName, strValue); 
}

void MdzXmlWriter::Close()
{
	fclose(pFile);
}
