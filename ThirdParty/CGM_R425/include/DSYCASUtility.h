#ifndef __DSYCASUTILITY
#define __DSYCASUTILITY

#define AES128  0
#define AES256  1 
#define RC4256  2
#define BF256   3

int DSYDecrypt (int Algo,  unsigned char *key, unsigned int keysize,
		unsigned char *iV, unsigned int iVsize,
		unsigned char * iBuff ,unsigned int iBuffLen,
		unsigned char*& oBuff, unsigned int &oOutputlen, int iPadd=1) ;


int DSYCrypt (int Algo,  unsigned char *key, unsigned int keysize,
	      unsigned char *iV, unsigned int iVsize,
	      unsigned char * iBuff ,unsigned int iBuffLen,
	      unsigned char*& oBuff, unsigned int &oOutputlen, int iPadd=1);


int DSYHmac ( const char* key, size_t keylen, 
	      unsigned char* buffer, size_t buflen, 
	      unsigned char *&md, unsigned int &mdlen);


#endif
