#ifndef CATXBoolean_H
#define CATXBoolean_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATAutoFilletCATAutoFilletBuildStatus.h
// 		
//===================================================================
//  Feb 2004  Creation: JHG
//===================================================================

#include "PersistentCell.h"
#include "CATTopRibObject.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "CATListPOfCATCGMDiagnoses.h"
#include "CATMathInline.h"


class ExportedByPersistentCell CATXBoolean
{
public:
  
  CATCGMNewClassArrayDeclare;      // Pool allocation

  INLINE CATBoolean GetValue() const { return _BooleanValue; }

  INLINE CATBoolean operator== (CATXBoolean &iX) const { return iX._BooleanValue == _BooleanValue; }
  INLINE CATBoolean operator!= (CATXBoolean &iX) const { return iX._BooleanValue != _BooleanValue; }
  INLINE CATBoolean operator|| (CATXBoolean &iX) const { return iX._BooleanValue || _BooleanValue; }
  INLINE CATBoolean operator&& (CATXBoolean &iX) const { return iX._BooleanValue && _BooleanValue; }
  INLINE CATBoolean operator! () const { return !_BooleanValue; }
  INLINE operator int () const { return (int)_BooleanValue; }


protected: // strictly forbidden to change any access type
//  CATBoolean operator= (CATXBoolean &iX) { return (_BooleanValue = iX._BooleanValue); }

  INLINE CATXBoolean(CATBoolean iBooleanValue);

  INLINE void SetValue(CATBoolean iBooleanValue) { 
    _BooleanValue = iBooleanValue; }

private:
  CATBoolean _BooleanValue;
};

CATXBoolean::CATXBoolean(CATBoolean iBooleanValue)
{
  SetValue(iBooleanValue);
}


#include "CATXBooleanTrue.h"
#include "CATXBooleanFalse.h"

#endif
