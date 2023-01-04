//==============================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//==============================================================================
//
// CATSobErrorMacros.h
//
//==============================================================================
//
// Usage notes: Macros + fonctions de gestion d'erreur
//
//==============================================================================
// October,   2010 : RAQ : Création
//==============================================================================
#ifndef CATSobErrorMacros_H
#define CATSobErrorMacros_H

//IO subdiv
#include "CATSobOStream.h"


#define CheckAndReturnIfBadDiag(iDiag, MethodName)                                                                        \
  if(!IsOK(iDiag))                                                                                                        \
  {                                                                                                                       \
    sobout << "@@@@ Erreur dans " << MethodName << ", Diag = " << ToString(iDiag) << ", Line = " << __LINE__ << sobendl;  \
    return iDiag;                                                                                                         \
  }

#define CheckAndReturnValueIfBadDiag(iDiag, MethodName, ToReturn)                                                         \
  if(!IsOK(iDiag))                                                                                                        \
  {                                                                                                                       \
    sobout << "@@@@ Erreur dans " << MethodName << ", Diag = " << ToString(iDiag) << ", Line = " << __LINE__ << sobendl;  \
    return ToReturn;                                                                                                      \
  }

#define CheckAndReturnIfError(iError, MethodName)                                                                   \
  if(iError)                                                                                                        \
  {                                                                                                                 \
    sobout << "@@@@ Erreur dans " << MethodName << ", Error = " << iError << ", Line = " << __LINE__ << sobendl;    \
    return iError;                                                                                                  \
  }


#define CheckAndWarningIfBadDiag(iDiag, MethodName)                                                                       \
  if(!IsOK(iDiag))                                                                                                        \
  {                                                                                                                       \
    sobout << "@@@@ Warning !!! Erreur dans " << MethodName << ", Diag = " << ToString(iDiag) << ", Line = " << __LINE__ << sobendl;  \
  }


#endif

