//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATHttpCookie                                                            *
//*                                                                           *
//*  Usage Notes:  Client Http V1.0                                           *
//*===========================================================================*
//*  Creation novembre 2003                                       adt         *
//*===========================================================================*
#ifndef CATHTTPCOOKIE_H
#define CATHTTPCOOKIE_H
#include <stdlib.h>
#include <memory.h>

#include "CATSysDataType.h"
#include "DSYSysTrace.h"
#include "JS0HTTP.h"


int ExportedByJS0HTTP CATSysSetCookie(const char *iUrl, const char *iVal, int iFlag = 0);

/*
** SIP: Flags for CATSysGetCookie
*/
#define CATSysGetCookieForAddRequestHeader				1
#define CATSysGetCookieForAddRequestHeaderMultipleLine	2

//For Internal use only
#define CATSysGetCookieCheckIfCookieIsInHashTable		4

int ExportedByJS0HTTP CATSysGetCookie(const char *iUrl, const char *iCookie, char **oVal, DWORD iFlag = 0);


/**************************/
/*DO NOT USE THOSE FEATURE*/
/**************************/
int ExportedByJS0HTTP CATSysBurnCookies();
int ExportedByJS0HTTP CATSysListCookies();
/**************************/
/*DO NOT USE THOSE FEATURE*/
/**************************/




//The Following class CATHttpCookie is not usable outside SystemTS
class CATHttpCookie 
{
public:
	CATHttpCookie();
	CATHttpCookie(const char *iUrl);
	~CATHttpCookie();
  
	static int			Compare(void *iA, void *iB);
	static unsigned int	Hash(void *iA);
    
	unsigned int	_HKey;
	int			_Version;
	int			_NameLen;
	int			_ValueLen;
	int			_PathLen;
	int			_DomainLen;

	char			*_Url;
	char			*_Cookie;
	char			*_Name;
	char			*_Value;
	char			*_Path;
	char			*_Domain;
	bool			_Secured;
	bool			_HttpOnly;
	CATHttpCookie *_Next;
}; 


#endif
