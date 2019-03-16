// MdzCrypto.h: interface for the MdzCrypto class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCRYPTO_H__3ECFACE7_9214_4DA3_91F1_75280293F012__INCLUDED_)
#define AFX_MDZCRYPTO_H__3ECFACE7_9214_4DA3_91F1_75280293F012__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzString.h"	// Added by ClassView

class DllExport MdzCrypto  
{
public:
	static MdzString
	ComputePublicKey(LPBYTE buffer, UINT bufferLength, MdzString strPrivateKey);

private:
	MdzCrypto();
	virtual ~MdzCrypto();

};

#endif // !defined(AFX_MDZCRYPTO_H__3ECFACE7_9214_4DA3_91F1_75280293F012__INCLUDED_)
