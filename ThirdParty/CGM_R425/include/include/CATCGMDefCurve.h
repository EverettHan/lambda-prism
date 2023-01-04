// COPYRIGHT DASSAULT SYSTEMES 1999
#ifndef CATCGMDefCurve_H
#define CATCGMDefCurve_H
//=============================================================================
//
// Base class designed to handle the curve definition 
// of a geometry based on another geomtery
//
//=============================================================================

#include "YP00IMPL.h"                    
#include "CATCGMDefGeometry.h"

class CATCrvLimits;

class ExportedByYP00IMPL CATCGMDefCurve : public CATCGMDefGeometry
{
public:

  CATCGMDefCurve();
  virtual ~CATCGMDefCurve();
  
  /** @nodoc */
  virtual void PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery );
};

#endif
