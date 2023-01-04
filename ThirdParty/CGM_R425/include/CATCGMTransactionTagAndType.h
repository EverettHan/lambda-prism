#ifndef CATCGMTransactionTagAndType_h
#define CATCGMTransactionTagAndType_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//  Pour Prototypage V5R8SP3 de reprise d'abend
//==========================================================================
/*
       //  Before , no active(event publish) breakpoints


     CATULONG32  iTag = GetPersistentTag();

     CATCGMTransactionTagAndTypeBegin(marqueur,CATFaceType,iTag) 
     {

        // Running execution where breakpoints are active

     }
     CATCGMTransactionTagAndTypeCATCatch(marqueur,error) 
     // {

     // }
     CATCGMTransactionTagAndTypeEndTry();


       //  After , no active(event publish) breakpoints
     
*/
//
//==========================================================================
#include "YP0LOGRP.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CATCGMNewArray.h"
#include "CATCGMTransaction.h"
#include "CATMathInline.h"
#include "CATGeometryType.h"

class CATGeoFactory;
class CATCGMMapCATULONGPTR;
class CATCGMStream;

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByYP0LOGRP CATCGMTransactionTagAndType : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static INLINE CATCGMTransactionTagAndType * Create(unsigned int iCATGeometricType, CATULONG32 iTag);
  CATCGMNewClassArrayDeclare;   

  //------------------------------------------------------------------
  // INTERNAL :  for comparison with SetUp
  //------------------------------------------------------------------
  virtual CATBoolean IsTransactionFilteredByTagAndType();

protected:
  //------------------------------------------------------------------
  // CLIENT : life of one CATCGMTransactionTagAndType Object identify a transaction
  //------------------------------------------------------------------
  INLINE  CATCGMTransactionTagAndType(unsigned int iCATGeometricType, CATULONG32 iTag);
};


INLINE CATCGMTransactionTagAndType *CATCGMTransactionTagAndType::Create(unsigned int iCATGeometricType, CATULONG32 iTag)
{
  return new CATCGMTransactionTagAndType(iCATGeometricType,iTag);
}

INLINE  CATCGMTransactionTagAndType::CATCGMTransactionTagAndType(unsigned int iCATGeometricType, CATULONG32 iTag)  
: CATCGMTransaction(CatCGMFilterBreakpointsByTagAndType,FALSE,iCATGeometricType,iTag)
{}




#define CATCGMTransactionTagAndTypeBegin(marqueur,iCATGeometricType,iTag)  \
  CATCGMTransactionTagAndType *volatile marqueur = CATCGMTransactionTagAndType::Create(iCATGeometricType,iTag); \
CATTry  \
{  


#define CATCGMTransactionTagAndTypeCATCatch(marqueur,error)  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; }  
  

#define CATCGMTransactionTagAndTypeEnd(marqueur)  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
  CATRethrow; \
}  \
CATEndTry 
 


#define CATCGMTransactionTagAndTypeEndTry()  \
}  \
CATEndTry 


#endif

