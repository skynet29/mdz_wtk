// MdzBaseRegister.cpp: implementation of the MdzBaseRegister class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzBaseRegister.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MDZ_KEY_KIND	HKEY_LOCAL_MACHINE

MdzBaseRegister::MdzBaseRegister()
{

}

MdzBaseRegister::~MdzBaseRegister()
{

}

BOOL MdzBaseRegister::SetDwordValue(LPSTR strPath, LPSTR strName, DWORD dwValue)
{
	HKEY hKey;
	LONG lRet;

	lRet = RegCreateKeyEx(HKEY_LOCAL_MACHINE, strPath, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

	if (lRet != ERROR_SUCCESS)
		return FALSE;

	lRet = RegSetValueEx(hKey, strName, 0, REG_DWORD, (LPBYTE) &dwValue, sizeof(DWORD));

	RegCloseKey (hKey);

	return (lRet == ERROR_SUCCESS);
}

BOOL MdzBaseRegister::GetDwordValue(LPSTR strPath, LPSTR strName, DWORD& dwValue)
{
	HKEY hKey;
	LONG lRet;
	DWORD dwType;
	DWORD dwSize = sizeof(DWORD);

	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, strPath, 0,KEY_READ, &hKey);
	if (lRet != ERROR_SUCCESS)
		return FALSE;

	lRet = RegQueryValueEx(hKey, strName, 0, &dwType, NULL, 0);
	if (lRet != ERROR_SUCCESS || dwType != REG_DWORD)
	{
		RegCloseKey (hKey);
		return FALSE;
	}

	lRet = RegQueryValueEx(hKey, strName, 0, NULL, (LPBYTE) &dwValue, &dwSize);

	RegCloseKey (hKey);

	return (lRet == ERROR_SUCCESS);

}

BOOL MdzBaseRegister::GetStringValue(LPSTR strPath, LPSTR strName, MdzString &strValue)
{
	HKEY hKey;
	LONG lRet;
	DWORD dwType;
	DWORD dwSize;


	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, strPath, 0,KEY_READ, &hKey);
	if (lRet != ERROR_SUCCESS)
		return FALSE;

	lRet = RegQueryValueEx(hKey, strName, 0, &dwType, NULL, 0);
	if (lRet != ERROR_SUCCESS || dwType != REG_SZ)
	{
		RegCloseKey (hKey);
		return FALSE;
	}

	lRet = RegQueryValueEx(hKey, strName, 0, NULL, NULL, &dwSize);
	if (lRet != ERROR_SUCCESS)
	{
		RegCloseKey (hKey);
		return FALSE;
	}

	strValue.Alloc(dwSize);

	lRet = RegQueryValueEx(hKey, strName, 0, NULL, (LPBYTE) (LPSTR) strValue, &dwSize);

	if (lRet != ERROR_SUCCESS)
	{
		RegCloseKey (hKey);
		return FALSE;
	}


	RegCloseKey (hKey);

	return (lRet == ERROR_SUCCESS);

}

BOOL MdzBaseRegister::SetStringValue(LPSTR strPath, LPSTR strName, LPSTR strValue)
{
	HKEY hKey;
	LONG lRet;

	lRet = RegCreateKeyEx(HKEY_LOCAL_MACHINE, strPath, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

	if (lRet != ERROR_SUCCESS)
		return FALSE;

	lRet = RegSetValueEx(hKey, strName, 0, REG_SZ, (LPBYTE) strValue, strlen(strValue));

	RegCloseKey (hKey);

	return (lRet == ERROR_SUCCESS);
}

BOOL MdzBaseRegister::EnumKey(LPSTR strPath, MdzStrVector &vector)
{
	CHAR					szName[_MAX_PATH];
	DWORD					cbName;
	FILETIME				ftLastWriteTime;
	HKEY hKey;
	LONG lRet;
	DWORD dwIndex;

	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, strPath, 0,KEY_READ, &hKey);
	if (lRet != ERROR_SUCCESS)
		return FALSE;

	dwIndex = 0;
	while (1)
	{
		cbName = sizeof(szName);
		lRet = RegEnumKeyEx(hKey, dwIndex++, szName, &cbName, NULL, NULL, NULL, &ftLastWriteTime);
		if (lRet != ERROR_SUCCESS)
			break;
		vector.Add(szName);
	}
	RegCloseKey (hKey);

	return TRUE;
}
