#ifndef __DSYCASUTILITIES
#define __DSYCASUTILITIES

#define AES128  0
#define AES256  1 
#define RC4256  2
#define BF256   3


#include "CATHttp.h"
#include "CATWTypes.h"


void ExportedByJS0HTTP DSYSysSHA_256 (char * iMessage, int iLen, DWORD *H);


// Hmac with sha1 digest
// Allocation made by callee, deallocation in charge of caller ( delete c++)
int  ExportedByJS0HTTP DSYSysHmac ( const char* key, size_t keylen, 
				    unsigned char* buffer, size_t buflen, 
				    unsigned char *&md, unsigned int &mdlen);


int ExportedByJS0HTTP DSYSysDecrypt (int Algo,  unsigned char *key, unsigned int keysize, 
				     unsigned char *iV, unsigned int iVsize, 
				     unsigned char * iBuff ,unsigned int iBuffLen,
				     unsigned char*& oBuff, unsigned int &oOutputlen, int iPadd=1 ) ; 


int ExportedByJS0HTTP DSYSysCrypt (int Algo,  unsigned char *key, unsigned int keysize,
				   unsigned char *iV, unsigned int iVsize, 
				   unsigned char * iBuff ,unsigned int iBuffLen, 
				   unsigned char*& oBuff, unsigned int &oOutputlen, int iPadd=1); 


#endif
