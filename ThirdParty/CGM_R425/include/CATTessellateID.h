// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessellateID
//
//===================================================================
//
// June 2013  Creation: TPG
//===================================================================
#ifndef CATTessellateID_H
#define CATTessellateID_H

#include "CATCGMTessellateID.h"
#include "CATCGMTessellateParam.h"

class ExportedByCATGMModelInterfaces CATTessellateID: public CATCGMTessellateID
{
public:
  CATTessellateID(CATCGMTessellateParam& iTessellateParam, CATULONG32 iNbDelta);
  CATTessellateID(const CATTessellateID& iRHS);

  ~CATTessellateID();

public:
  inline CATULONG32 GetDelta() const;
  //void SetOrientation(int iOrientation); // only for contextual comparison; -1 or 1; 0 by default
  CATCGMTessellateID& operator = (const CATCGMTessellateID& iRHS);
	CATTessellateID& operator = (const CATTessellateID& iRHS);
  int operator == (const CATCGMTessellateID& iRHS) const;
  int operator != (const CATCGMTessellateID& iRHS) const;
  int operator < (const CATCGMTessellateID& iRHS) const;
	inline CATCGMTessellateParam& GetTessellateParam();

protected:
	CATCGMTessellateParam _TessellateParam;
  CATULONG32 _NbDelta;
  int _Orientation; // only for contextual comparison, 0 by default
};

inline CATULONG32 CATTessellateID::GetDelta() const
{
  return _NbDelta;
}

inline CATCGMTessellateParam& CATTessellateID::GetTessellateParam() 
{
  return _TessellateParam;
}
#endif // CATTessellateID_H

