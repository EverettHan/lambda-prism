#ifndef CATCGAMeasureContext_H
#define CATCGAMeasureContext_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    For general solution concerning GM diagnostic inside an applicative product
*       with some major PCS criteria as memory (working set , virtual size)
* 
*    This Multiple purpose analysis can be extended,
*      this support is tightly linked with some reccurent CoreDump incident
*         misunderstood concerning  origin of memory consumption
*         badly managed when request of allocations begin to fail
* 
*    Meaningfull report avec provided with activation of following environement variable
*         CATCGAMeasure=Home=E:\tmp,PCS   (Cache option should be omitted)
*/
//------------------------------------------------------------ 
// area(s) of data
//------------------------------------------------------------ 
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATMathInline.h"
#include "CATCGMKernel.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"

class CATCGMItfName;
class CATCGAMeasureNode;
 
// Stack Node
class ExportedByCATCGMKernel CATCGAMeasureContext
{
public :

  CATCGMNewClassArrayDeclare;  

  const unsigned int          _Domain; // simplified CATCGAMeasureCSI_Domain_ (Second argument (const char * iDataDomain) of CATCGAMeasureNode
  const CATUnicodeString      _Type;   //   First argument (const char * iKindOfOperation) of CATCGAMeasureNode   
  const CATUnicodeString      _Name;   // customised instance of CATCGAMeasureCSI_Domain_Feat   (Second argument (CATCGMItfName  *  _WorkingFeature) of CATCGAMeasureNode   
  const CATUINTPTR            _Key;  

  CATLONG64     _CumulatedDepths; 
  CATLONG64     _NumberOfDepths; 
  CATLONG64     _StartCounter; 

  INLINE CATCGAMeasureContext() : _Domain(0), _Key(0), _CumulatedDepths(0), _NumberOfDepths(0), _StartCounter(0)
  {}

  // Cf CATCGAMeasure
  INLINE  CATCGAMeasureContext(const char * iOperation, const char * iOperationDomain, CATCGMItfName    *  iWorkingFeature ) 
    : _Domain(0), _Key(0), _CumulatedDepths(0), _NumberOfDepths(0), _StartCounter(0)
  {  Set(iOperation,iOperationDomain,NULL,iWorkingFeature); }

  INLINE ~CATCGAMeasureContext() 
  { }

  void Set(const char * iOperation, const char * iOperationDomain, CATCGAMeasureNode *iMeasureNode, CATCGMItfName    *  iWorkingFeature );

  INLINE CATBoolean operator == (const CATCGAMeasureContext & iOther) const ;
  INLINE CATBoolean operator != (const CATCGAMeasureContext & iOther) const ;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  INLINE CATCGAMeasureContext(const CATCGAMeasureContext &iCopy);
  INLINE CATCGAMeasureContext& operator=(const CATCGAMeasureContext &iCopy);

private :


  static CATBoolean NameAutoCompletion( CATCGMItfName  *  iWorkingFeature,    CATUnicodeString * iType, CATUnicodeString * iName);

};

 extern "C" { typedef CATBoolean CATCGAContextAutoCompletion( CATCGMItfName  *  iWorkingFeature,    CATUnicodeString * iType, CATUnicodeString * iName); }  

/** --------------------------------------------------------------------------------
* Constructor by Copie
* -------------------------------------------------------------------------------- **/
INLINE CATCGAMeasureContext::CATCGAMeasureContext(const CATCGAMeasureContext &iOther) 
: _Domain(iOther._Domain),_Type(iOther._Type), _Name(iOther._Name), _Key(iOther._Key)
, _CumulatedDepths(iOther._CumulatedDepths), _NumberOfDepths(iOther._NumberOfDepths), _StartCounter(iOther._StartCounter)  
{
}

/** --------------------------------------------------------------------------------
* Constructor by Copie
* -------------------------------------------------------------------------------- **/
INLINE CATCGAMeasureContext& CATCGAMeasureContext::operator=(const CATCGAMeasureContext &iOther)
{
  if (&iOther == this)  return *this;

  *((CATUnicodeString *)&_Type) = iOther._Type;
  *((CATUnicodeString *)&_Name) = iOther._Name;
  *((unsigned int *)&_Domain) = iOther._Domain;
  *((CATUINTPTR *)&_Key) = iOther._Key;
  *((CATLONG64 *)&_CumulatedDepths) = iOther._CumulatedDepths;
  *((CATLONG64 *)&_NumberOfDepths)  = iOther._NumberOfDepths;
  *((CATLONG64 *)&_StartCounter)    = iOther._StartCounter;

  return *this;
}


INLINE CATBoolean CATCGAMeasureContext::operator == (const CATCGAMeasureContext & iOther) const 
{
  if (this == &iOther) return TRUE; 
  if ( _Key    != iOther._Key    ) return FALSE;
  if ( _Domain != iOther._Domain ) return FALSE;
  if ( +2 != _Name.Compare(iOther._Name) ) return FALSE;
  if ( +2 != _Type.Compare(iOther._Type) ) return FALSE;
  return TRUE;
}

INLINE CATBoolean CATCGAMeasureContext::operator != (const CATCGAMeasureContext & iOther) const 
{
  if (this == &iOther) return FALSE; 
  if ( _Key    != iOther._Key    ) return TRUE;
  if ( _Domain != iOther._Domain ) return TRUE;
  if ( +2 != _Name.Compare(iOther._Name) ) return TRUE;
  if ( +2 != _Type.Compare(iOther._Type) ) return TRUE;
  return FALSE;
}

#endif
