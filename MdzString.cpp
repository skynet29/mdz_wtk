// MdzString.cpp: implementation of the MdzString class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzString.h"
#include "MdzStream.h"
#include "MdzVector.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MDZ_STRING_MAGIC		0x53545247

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



MdzString::MdzString()
{
	lpData = new char[1];
	lpData[0] = 0;
}

MdzString::~MdzString()
{
	delete [] lpData;
}

void MdzString::Clone(LPSTR lpStr)
{
	lpData = new char[strlen(lpStr) + 1];
	strcpy(lpData, lpStr);
}

MdzString::MdzString(LPSTR lpStr)
{
//	assert(lpStr != NULL);

	Clone(lpStr);
}

MdzString::MdzString(const MdzString &str)
{
	Clone(str.lpData);
}

void MdzString::operator =(const MdzString &str)
{
	if ( this != &str )
	{
		delete [] lpData;
		Clone(str.lpData);			
	}
}

MdzString::operator LPSTR()
{
	return (lpData);
}

int MdzString::GetLength() const
{
	return strlen(lpData);
}








BOOL MdzString::Equals(LPSTR lpStr)
{

	return ( Compare(lpStr) == 0 );
}

MdzString MdzString::Format(LPSTR fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char buffer[1024];
	vsprintf(buffer, fmt, args);
	va_end(args);
	return MdzString(buffer);
}

void MdzString::Dump()
{
	printf("%s\n", lpData);
}

void MdzString::operator +=(const MdzString &str)
{
	LPSTR lpTemp =  new char[GetLength() + str.GetLength() + 1];
	strcpy(lpTemp, lpData);
	strcat(lpTemp, str.lpData);
	delete [] lpData;
	lpData = lpTemp;
}

void MdzString::Alloc(UINT iSize)
{
	delete [] lpData;
	lpData = new char[iSize];
}



DllExport MdzString operator+(MdzString& str1, MdzString& str2)
{
	MdzString ret;
	ret.Alloc(str1.GetLength() + str2.GetLength() + 1);
	strcpy(ret, str1);
	strcat(ret, str2);

	return ret;
}

MdzString MdzString::GetSubString(int iStartIdx, int iLength)
{
	MdzString ret;

	if (lpData)
	{
		int iMaxlength = GetLength() - iStartIdx;
		
		if (iLength < 0)
			iLength = iMaxlength;
		else
			iLength = min(iLength, iMaxlength);

		if (iMaxlength > 0)
		{
			ret.Alloc(iLength + 1);
			char* dest = (LPSTR) ret;
			memcpy(dest, lpData + iStartIdx, iLength);
			dest[iLength] = 0;
		}
	}
	return ret;
}

int MdzString::ToInt()
{
	return atoi(lpData);
}

MdzString MdzString::Load(UINT iResId, HMODULE hModule)
{
	char buffer[1024];
	LoadString((hModule) ? hModule : GetModuleHandle(NULL),
		iResId, buffer, sizeof(buffer));
	return MdzString(buffer);
}

int MdzString::GetIndexOf(LPSTR str, int iStartIdx)
{
	if (!lpData)
		return -1;

	char* lpTemp = strstr(&lpData[iStartIdx], str);

	if (!lpTemp)
		return -1;

	return (lpTemp - lpData);
}

MdzString MdzString::ExtractFileName()
{
	MdzString ret;

	if (lpData)
	{
		LPSTR lpTemp = strrchr(lpData, '\\');

		if (lpTemp)
			ret = lpTemp + 1;
	}

	return ret;
}

int MdzString::ToIntHex()
{
	return strtol(lpData, NULL, 16);
}

MdzString MdzString::ToUpper()
{
	MdzString ret = lpData;
	strupr(ret);
	return ret;
}

MdzString MdzString::ToLower()
{
	MdzString ret = lpData;
	strlwr(ret);
	return ret;

}

MdzString MdzString::ExtractPath()
{
	MdzString ret;

	if (lpData)
	{
		LPSTR lpTemp = strrchr(lpData, '\\');

		if (lpTemp)
		{
			*lpTemp = 0;
			ret = lpData;
			*lpTemp = '\\';
		}
	}

	return ret;

}

UCHAR MdzString::GetCharAt(UINT iIndex)
{
	return lpData[iIndex];
}

UCHAR MdzString::operator[](UINT iIndex)
{
	return lpData[iIndex];
}

int MdzString::Compare(LPSTR lpStr)
{
	return strcmp(lpData, lpStr);
}

void MdzString::Tokenize(LPSTR strToken, MdzStrVector &vector)
{
	if (!lpData)
		return;

	LPSTR strDup = strdup(lpData);

	LPSTR strTemp = strtok(strDup, strToken);
	while (strTemp)
	{
		vector.Add(strTemp);
		strTemp = strtok(NULL, strToken);
	}
	free(strDup);
}
