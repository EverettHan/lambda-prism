#ifndef CATCGMUnstreamByInjection_h
#define CATCGMUnstreamByInjection_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//  Pour Prototypage V5R8SP3 de reprise d'abend
//==========================================================================
/*
    CATGeoFactory           *iFactory;
    CATCGMMapCATULONGPTR    *iExpectedMapping = NULL;

    CATCGMUnstreamByInjectionBegin(marqueur,factory) 
    {
       // Lecture de container geometrique par Append  
    }
    CATCGMUnstreamByInjectionEnd(marqueur,iExpectedMapping);
    
    if ( iExpectedMapping ) 
    {
      delete iExpectedMapping;
      iExpectedMapping = NULL;
    }


*/
//
//==========================================================================
#include "YP0LOGRP.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CATCGMNewArray.h"
#include "CATCGMTransaction.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATCGMMapCATULONGPTR;
class CATCGMStream;

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByYP0LOGRP CATCGMUnstreamByInjection : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static CATCGMUnstreamByInjection * Create(CATGeoFactory *iFactory);
  CATCGMNewClassArrayDeclare;   

  CATCGMMapCATULONGPTR * GetMapping(int iJustForAnalysis = 0);

  //------------------------------------------------------------------
  // INTERNAL : Used to make sure that end of Transaction is done
  // in case of exception throw with longjmp ..
  //------------------------------------------------------------------
  virtual void Clean();

  /** @nodoc */
  void SetMapping(CATCGMStream &iReference);

  INLINE  CATGeoFactory *GetFactory();


protected:
  //------------------------------------------------------------------
  // CLIENT : life of one CATCGMUnstreamByInjection Object identify a transaction
  //------------------------------------------------------------------
  CATCGMUnstreamByInjection(CATGeoFactory *iFactory);

  CATGeoFactory           *_Factory;
  CATCGMMapCATULONGPTR    *_Mapping;
  CATBoolean               _MappingRead;
};


#define CATCGMUnstreamByInjectionBegin(marqueur,factory)  \
  CATCGMUnstreamByInjection *volatile marqueur = CATCGMUnstreamByInjection::Create(factory); \
CATTry  \
{  

#define CATCGMUnstreamByInjectionEnd(marqueur,iExpectedMapping)  \
  if ( marqueur ) { iExpectedMapping = marqueur->GetMapping(); marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
  CATRethrow; \
}  \
CATEndTry 

INLINE  CATGeoFactory *CATCGMUnstreamByInjection::GetFactory()
{
  return _Factory;
}


#endif

