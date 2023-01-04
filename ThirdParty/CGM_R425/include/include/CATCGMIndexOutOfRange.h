/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 2001
// Pour emission d'un message d'erreur associe a un indicage hors rang
//
//==========================================================================
#ifndef CATCGMIndexOutOfRange_H
#define CATCGMIndexOutOfRange_H

#include <stdlib.h>
#include <stddef.h>
#include "CATMathematics.h"
#include "CATErrorMacros.h"
#include "CATCGMBuildDebug.h"
#include "CATCGMThrow.h"
#include "CATBoolean.h"

// diagnostic d'indicage hors limites
ExportedByCATMathematics CATError * CATCGMIndexOutOfRangeError(int idx,int iMinIn,int iMaxOut); 

// Pour levee d'anomalie sur indicage hors limites
#define CATCGMIndexOutOfRange(idx,iMinIn,iMaxOut) \
   CATCGMThrow( CATCGMIndexOutOfRangeError(idx,iMinIn,iMaxOut) )

// Pour controle integree d'un indicage 
#define CATCGMValidateRange(idx,iMinIn,iMaxOut)  \
  if ( (idx < iMinIn) || (idx >= iMaxOut)  ) \
    CATCGMIndexOutOfRange(idx,iMinIn,iMaxOut)

#endif

