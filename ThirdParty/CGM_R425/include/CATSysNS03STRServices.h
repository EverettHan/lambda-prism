//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2004                                         *
//*===========================================================================*
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation juin 2004                                                       *
//*===========================================================================*
#ifndef __CATSYSNS03STRSERVICES
#define __CATSYSNS03STRSERVICES

#include "CATSysTS.h"
#include "CATWTypes.h"

class CATUnicodeString;

int  ExportedByCATSysTS  DSYSysCmpUnicodeStrings(CATUnicodeString * iUnicodeString1,
						 CATUnicodeString * iUnicodeString2);
int  ExportedByCATSysTS  DSYSysCompareUnicodeStrings(CATUnicodeString & iString1,
						     CATUnicodeString & iString2);

#endif
