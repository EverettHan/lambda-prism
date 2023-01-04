//===========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017                                          
//===========================================================================
#ifndef DSYSysHash_H
#define DSYSysHash_H

#include "CATSysTS.h"
#include "CATSysDataType.h"
#include "CATSysErrorDef.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum DSYSysHashAlgo { MD5=0, SHA1=1, SHA256=2, SHA512=3};
typedef  void* DSYSysHash;

//***************************************************************************** 
//*                                                                           * 
//*                                                                           *
//*****************************************************************************
extern "C" HRESULT ExportedByCATSysTS DSYSysHash_Init ( DSYSysHashAlgo iAlgo, DSYSysHash &oHash);


//***************************************************************************** 
//*                                                                           * 
//*                                                                           *
//*****************************************************************************
extern "C" HRESULT  ExportedByCATSysTS DSYSysHash_Update(DSYSysHash &iHash, unsigned char* iData, unsigned int iLen);


//***************************************************************************** 
//*                                                                           * 
//*                                                                           *
//*****************************************************************************
extern "C" HRESULT  ExportedByCATSysTS DSYSysHash_Final (DSYSysHash &iHash, unsigned char *& oMD, unsigned int &oLen);


//***************************************************************************** 
//*                                                                           * 
//*                                                                           *
//*****************************************************************************
extern "C" HRESULT  ExportedByCATSysTS DSYSysHash_Digest ( DSYSysHashAlgo iAlgo, unsigned char* iData, unsigned int iLen, 
							   unsigned char *& oMD, unsigned int &oLen);

#endif
