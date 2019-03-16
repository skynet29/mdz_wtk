// MdzCrypto.cpp: implementation of the MdzCrypto class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzCrypto.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern "C" void hmac_md5(LPBYTE text, int text_len, LPBYTE key, int key_len, BYTE digest[16]);

MdzCrypto::MdzCrypto()
{

}

MdzCrypto::~MdzCrypto()
{

}

MdzString MdzCrypto::ComputePublicKey(LPBYTE buffer, UINT bufferLength, MdzString strPrivateKey)
{
	MdzString ret;

	if ((strPrivateKey.GetLength() % 2) != 0)
		return ret;

	UINT keyLength = strPrivateKey.GetLength() / 2;

	LPBYTE Key = new BYTE[strPrivateKey.GetLength() / 2];

	for (UINT i = 0; i < keyLength; i++)
	{
		Key[i] = strPrivateKey.GetSubString(i*2, 2).ToIntHex();
	}

	BYTE digest[16];

	hmac_md5(buffer, bufferLength, Key, keyLength, digest);
	delete [] Key;
	
	for (i = 0; i < 16; i++)
	{
		ret += MdzString::Format("%02X", digest[i]);
	}

	return ret;
}
