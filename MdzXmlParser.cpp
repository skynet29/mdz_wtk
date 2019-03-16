// MdzXmlParser.cpp: implementation of the MdzXmlParser class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzXmlParser.h"
#include "MdzXmlElement.h"
#include "MdzXmlAttribute.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzXmlParser::MdzXmlParser()
{
	pFile = NULL;
}

MdzXmlParser::~MdzXmlParser()
{
	if (pFile)
		fclose(pFile);
}

MdzXmlElement* MdzXmlParser::Parse()
{
	if (!pFile)
		return NULL;

	MdzString buffer;
	char buff[2];
	int idx = 0;
	BOOL bInTag = FALSE;
	char& c = buff[0];
	int nLevel = 0;
	MdzXmlElement* pRoot, *pElt;
	pRoot = pElt = OnNewElement("Root");
	buff[1] = 0;	
	BOOL bInQuote = FALSE;

	while ((c = fgetc(pFile))!= EOF)
	{
		if (bInTag)
		{
			if (c == '>' && !bInQuote)
			{
				bInTag = FALSE;
				//buffer[idx] = 0;
				if (!buffer.GetSubString(0, 1).Equals("/"))
				{
					int length = buffer.GetLength() - 1;
					if (buffer.GetSubString(length, 1).Equals("/"))
					{
						MdzXmlElement* pNewElt = ParseParameters(buffer.GetSubString(0, length));
						pElt->AddChild(pNewElt);
					}
					else
					{
						MdzXmlElement* pNewElt = ParseParameters(buffer);
						pElt->AddChild(pNewElt);
						pElt = pNewElt;
					}
				}
				else
					pElt = pElt->GetParent();

				idx = 0;
				buffer = "";
			}
			else
			{
				buffer += buff; 
				//buffer[idx++] = c;
				if (c == '"')
					bInQuote = (bInQuote == FALSE);
			}
		}
		else if (c == '<')
			bInTag = TRUE;
	}
	return pRoot;
}

MdzXmlElement* MdzXmlParser::ParseParameters(LPSTR pBuff)
{

	/*
	LPSTR strName = strtok(pBuff, " ");
	MdzXmlElement* pElt = new MdzXmlElement(strName);


	LPSTR strParamName;
	while ((strParamName = strtok(NULL, "=")))
	{
		LPSTR strValue = strtok(NULL, "\"");
		while (*strParamName == ' ') strParamName++;
		pElt->AddAttribute(new MdzXmlAttribute(strParamName, (strValue) ? strValue : ""));
	}
	*/
	LPSTR strName = pBuff;
	LPSTR strParam = strchr(strName, ' ');
	if (strParam)
		*strParam++ = 0;

	MdzXmlElement* pElt = OnNewElement(strName);

	while (strParam && *strParam != 0)
	{
		if (*strParam == ' ') strParam++;

		LPSTR strParamName = strParam;
		LPSTR strParamValue = strstr(strParamName, "=\"");
		if (strParamValue)
		{
			*strParamValue = 0;
			strParamValue +=2;
		}
		strParam = strchr(strParamValue, '"');
		if (strParam)
			*strParam++ = 0;

		pElt->AddAttribute(new MdzXmlAttribute(strParamName, strParamValue));

	}






	return pElt;
}

BOOL MdzXmlParser::Open(LPSTR strFileName)
{
	pFile = fopen(strFileName, "r");
	return (pFile != NULL);
}

MdzXmlElement* MdzXmlParser::OnNewElement(LPSTR strName)
{
	return new MdzXmlElement(strName);
}
