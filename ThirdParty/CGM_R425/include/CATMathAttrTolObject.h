// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathAttrTolObject
// Class used to define the set of tolerance (Big Scale)
//
//=============================================================================
//
// Usage notes:

//=============================================================================


#ifndef CATMathAttrTolObject_H
#define CATMathAttrTolObject_H

#include "YN000FUN.h"
#include "CATMathAttribute.h"
#include "CATTolerance.h"

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathAttrTolObject : public CATMathAttribute
{
  public:
//--------------
//  Constructors
//---------------
  
CATMathAttrTolObject (const CATTolerance &iTolObject);
//--------------
//  Destructors
//---------------
~CATMathAttrTolObject();
//---------------
//  Other Methods
//---------------
CATMathAttrId GetType() const;
CATBoolean IsExclusive() const;

const CATTolerance &GetTolObject () const;


private:
  const CATTolerance &_TolObject;
  
};

#endif
