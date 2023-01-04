// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATOwnedCGM:
// Abstract class for CGM objects that may be owned by one other CGM object.
//=============================================================================
// Usage notes:
//
// This class manages back pointer from the owned object to the owner object.
//=============================================================================
// Sep. 97   Creation                                     R. Rorato
// Jun. 12   Perfo : inline constructor                   F. Dumas
//=============================================================================
#ifndef CATOwnedCGM_H
#define CATOwnedCGM_H

#include "ExportedToCGMV5Interoperability.h"                 
#include "CATGeometryCGM.h"
#include "CATMathInline.h"

//-----------------------------------------------------------------------------
class ExportedToCGMV5Interoperability CATOwnedCGM: public CATGeometryCGM
{

public :

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  INLINE CATOwnedCGM () {};

  //-------------------------------------------------------------------------
  // Owner access
  //-------------------------------------------------------------------------
  CATGeometry* GetOwner () const  ;
  void SetOwner( CATGeometry* Owner ) ;

  //-------------------------------------------------------------------------
  // Event management
  //-------------------------------------------------------------------------
  void IsModified() ;

  //---------------------------------------------------------------------------
  // Object Modeler declaration for IsAKindOf
  //---------------------------------------------------------------------------
  CATCGMDeclareVirtualClass;

private :
  
  //-------------------------------------------------------------------------
  // Back pointer to the Owner
  //-------------------------------------------------------------------------
// CATGeometry* _Owner ;

};
#endif
