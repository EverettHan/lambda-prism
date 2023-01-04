// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessellatePolyID
//
//===================================================================
//
// June 2017    Creation: LVL
//===================================================================
#ifndef CATTessellatePolyID_H
#define CATTessellatePolyID_H

#include "CATCGMTessellateID.h"
#include "CATListOfCATCells.h"
#include "CATBoolean.h"

class ExportedByCATGMModelInterfaces CATTessellatePolyID: public CATCGMTessellateID
{
public:
  CATTessellatePolyID(int iCellTag, int iOrientation);
  CATTessellatePolyID(const CATTessellatePolyID& iRHS);

  ~CATTessellatePolyID();

public:
  CATCGMTessellateID& operator = (const CATCGMTessellateID& iRHS);
	CATTessellatePolyID& operator = (const CATTessellatePolyID& iRHS);
  int operator == (const CATCGMTessellateID& iRHS) const;
  int operator != (const CATCGMTessellateID& iRHS) const;
  int operator < (const CATCGMTessellateID& iRHS) const;

  inline int GetOrientation() const;

protected:
  int _CellTag;
  int _Orientation; // only for contextual comparison, 0 by default
};


inline int CATTessellatePolyID::GetOrientation() const
{
  return _Orientation;
}

#endif // CATTessellatePolyID_H

