#ifndef CATCrvParamPrivate_h
#define CATCrvParamPrivate_h
//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATCrvParamPrivate : parameter on a curve of type CATCurve
//
// DESCRIPTION : this object is used by the curves to build some CrvParam from
// the position of the points
// 
//=============================================================================
//
// Inheritance :
//      - CATCrvParam
//        - CATCrvParamPrivate
//
//=============================================================================
//
// History
//
// Jun. 97  Simon Royer (sro)        Creation 
//
//=============================================================================

#include "YP00IMPL.h"

#include "CATCrvParam.h"

class CATCurve;
class CATParamData;

class ExportedByYP00IMPL CATCrvParamPrivate : public CATCrvParam
{
 public:
// Copy constructor
  CATCrvParamPrivate (const CATCrvParam & iParam);

// Builds a CrvParam pointing on an interface of CATCurve, with an arc number
// an a position on the arc (see the class CATParamData).
// The object uses the KnotVector of the CATCurve if it exists, else the curve
// is considered as monoarc.
  CATCrvParamPrivate (const CATParamData &iPosition,
		      const CATCurve * iCurve);

// Setting and getting the curve the CrvParam belongs
  const CATCurve * GetCurve() const;
  void SetCurve(const CATCurve * curve);
};

#endif
