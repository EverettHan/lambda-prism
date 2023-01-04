/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATAssociation: Data of the attribute used in CATTransformation
// 
//=============================================================================
// Usage notes:
//
// 
// 
//
//=============================================================================
// Abstract Class     : No
// Inline Functions   : No
//=============================================================================
// Oct. 97   Creation                                 ILY (I. Levy)
// F4Z     le 05/09/19   RI667948 , addref of copied object during multi copy/paste
//=============================================================================
#ifndef CATASSOCIATION_H
#define CATASSOCIATION_H

//Windows compatibility
#include "YP00IMPL.h"

//TRANSFO libraries 
#include "CATTransfoManagerDefines.h" 

//Other libraries
#include "CATCGMNewArray.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "CATBoolean.h"

class CATMathTransformation2D;
class CATMathTransformation1D;
class CATICGMObject;
class CATCrvLimits;
class CATCrvParam;
class CATSurLimits;
class CATSurParam;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATAssociation
{
public:
  CATCGMNewClassArrayDeclare;

  enum CATInputType {InEntry, NotInEntry};

  //---------------------------------------------------------------------------
  //- Constructor
  //---------------------------------------------------------------------------
  CATAssociation (CATICGMObject* iIn                   ,
		  CATICGMObject* iOut  = 0             ,
		  CATInputType   iType = InEntry       ,
		  CATULONG32   iCount = 0            ,
		  short          iInvariance = 2       ,
		  short          iInvarianceOfLinks = 2);

  //---------------------------------------------------------------------------
  //- Destructor
  //---------------------------------------------------------------------------
  virtual ~CATAssociation();

  //---------------------------------------------------------------------------
  //-GetOut: returns Out
  //---------------------------------------------------------------------------
  INLINE CATICGMObject* GetOut() const;

  //---------------------------------------------------------------------------
  //-GetIn: returns In
  //---------------------------------------------------------------------------
  INLINE CATICGMObject* GetIn() const;

  //---------------------------------------------------------------------------
  //-GetCount: returns Count
  //---------------------------------------------------------------------------
  INLINE CATULONG32 GetCount() const;

  //---------------------------------------------------------------------------
  //-GetUseCount: returns UseCount
  //---------------------------------------------------------------------------
  INLINE CATULONG32 GetUseCount() const;
  
  //---------------------------------------------------------------------------
  //-CATInputType: returns the InputType
  //---------------------------------------------------------------------------
  INLINE CATInputType GetInputType() const; 
  
  //---------------------------------------------------------------------------
  //- GetTransfoUV: returns the 2D Transformation
  //---------------------------------------------------------------------------
  virtual void GetTransfoUV(CATMathTransformation2D* &oTransfo2D) const;
  
  //---------------------------------------------------------------------------
  //-GetTransfoW: returns the 1D Transformation
  //---------------------------------------------------------------------------
  virtual void GetTransfoW(CATMathTransformation1D* &oTransfo1D) const;

  //---------------------------------------------------------------------------
  //-SetOut: changes Out
  //---------------------------------------------------------------------------
  void SetOut(CATICGMObject* iOut);

  //---------------------------------------------------------------------------
  //-SetInputType: changes InputType
  //---------------------------------------------------------------------------
  INLINE void SetInputType(CATInputType iType);

  //---------------------------------------------------------------------------
  //-SetUnderMultiCopy: changes IsUnderMultiCopyPasteTransaction
  //---------------------------------------------------------------------------
  void SetUnderMultiCopy(CATBoolean IsUnderMultiCopyPasteTransaction);

  //---------------------------------------------------------------------------
  //-IncreaseCount: Increases Count of 1
  //---------------------------------------------------------------------------
  void IncreaseCount();

  //---------------------------------------------------------------------------
  //-IncreaseCount: Decreases Count of 1
  //---------------------------------------------------------------------------
  void DecreaseCount();

  //---------------------------------------------------------------------------
  //-GetInvariance: returns value of Invariant 
  //---------------------------------------------------------------------------
  INLINE short GetInvariance() const;

  //---------------------------------------------------------------------------
  //-SetInvariance: changes value of Invariant (0 or 1)
  //---------------------------------------------------------------------------
  void SetInvariance(short i) ;

  //---------------------------------------------------------------------------
  //-GetInvarianceOfLinks: returns value of InvariantLink 
  //---------------------------------------------------------------------------
  short GetInvarianceOfLinks() const;

  //---------------------------------------------------------------------------
  //-SetInvarianceOfLinks: changes value of InvariantLink (0 or 1)
  //---------------------------------------------------------------------------
  void SetInvarianceOfLinks(short i) ;

  //---------------------------------------------------------------------------
  //-GetModification: returns value of Modification
  //---------------------------------------------------------------------------
  short GetModification() const;

  //---------------------------------------------------------------------------
  //-SetModification: changes value of Modification (0 or 1)
  //---------------------------------------------------------------------------
  void SetModification(short i) ;

  //---------------------------------------------------------------------------
  //-SetTransfoUV: changes TransfoUV
  //---------------------------------------------------------------------------
  virtual void SetTransfoUV(CATMathTransformation2D & iTransfo2D) ;

  //---------------------------------------------------------------------------
  //-SetTransfoW: changes TransfoW
  //---------------------------------------------------------------------------
  virtual void SetTransfoW(CATMathTransformation1D & iTransfo1D) ;

  //---------------------------------------------------------------------------
  //-GetBoxUV: returns the BoxUV
  //---------------------------------------------------------------------------
  virtual void GetBoxUV(CATSurLimits * &oBox) const;

  //---------------------------------------------------------------------------
  //-GetBoxW: returns the BoxW
  //---------------------------------------------------------------------------
  virtual void GetBoxW(CATCrvLimits * &oBox) const;

  //---------------------------------------------------------------------------
  //-AddToBoxUV: Add iBox or iParam to _BoxUV
  //---------------------------------------------------------------------------
  virtual void AddToBoxUV(CATSurLimits & iBox);
  virtual void AddToBoxUV(CATSurParam  & iParam);

  //---------------------------------------------------------------------------
  //-AddToBoxW: Add iBox or iParam to _BoxW
  //---------------------------------------------------------------------------
  virtual void AddToBoxW(CATCrvLimits & iBox);
  virtual void AddToBoxW(CATCrvParam  & iParam);

  //---------------------------------------------------------------------------
  //-AddReference() - ReleaseReference mechanisms for Multi Copy Paste
  //---------------------------------------------------------------------------
  virtual void AddReferenceForMultiCopy();
  virtual unsigned ReleaseForMultiCopy();

  //---------------------------------------------------------------------------
  //-Reset: Reset output data
  //---------------------------------------------------------------------------
  virtual void Reset(CATResetType iType = CATTransfoManager_ResetStd);

  /** @nodoc @nocgmitf */
  INLINE void AssignInvarianceOfLinks(short iInvarianceOfLinks) {_InvarianceOfLinks = iInvarianceOfLinks;}

private:
  
  CATICGMObject* _In ;  
  CATICGMObject* _Out ;
  CATInputType   _Type ;
  CATULONG32     _UseCount ; //UseCount of the object
  CATULONG32     _Count ; //CurrentCount of the TransfoManager
  short          _Invariance ;
  short          _InvarianceOfLinks ;
  short          _Modification ;
  short          _OutGivenInEntry;
  CATBoolean     _IsUnderMultiCopyPasteTransaction;
  CATBoolean     _OutputRef;
  CATBoolean     _IncDone; //to avoid multiple add ref 
  //for Invariance : 2 means invariance has not been calculated
  //                 1 means object is invariant
  //                 0 means object is not invariant
};
//-----------------------------------------------------------------------------
//                            INLINE
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
INLINE CATICGMObject* CATAssociation::GetIn() const
//-----------------------------------------------------------------------------
{
  return (_In) ;
}
//-----------------------------------------------------------------------------
INLINE CATICGMObject* CATAssociation::GetOut() const
//-----------------------------------------------------------------------------
{
  return (_Out) ;
}
//-----------------------------------------------------------------------------
INLINE CATULONG32  CATAssociation::GetCount() const
//-----------------------------------------------------------------------------
{
  return (_Count) ;
}
//-----------------------------------------------------------------------------
INLINE CATULONG32  CATAssociation::GetUseCount() const
//-----------------------------------------------------------------------------
{
  return (_UseCount) ;
}
//-----------------------------------------------------------------------------
INLINE CATAssociation::CATInputType CATAssociation::GetInputType() const
//-----------------------------------------------------------------------------
{
  return (_Type) ;
}
//-----------------------------------------------------------------------------
INLINE short CATAssociation::GetInvariance() const
//-----------------------------------------------------------------------------
{
  return (_Invariance) ;
}
//-----------------------------------------------------------------------------
INLINE void CATAssociation::SetInputType(CATInputType iType)
//-----------------------------------------------------------------------------
{
  _Type = iType;
}

#endif











