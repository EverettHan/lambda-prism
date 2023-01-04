// COPYRIGHT DASSAULT SYSTEMES 1999
#ifndef CATCGMDefSurface_H
#define CATCGMDefSurface_H
//=============================================================================
//
// Base class designed to handle the Surface definition 
// of a geometry based on another geomtery
//
//=============================================================================

#include "YP00IMPL.h"                    
#include "CATCGMDefGeometry.h"

class CATSurLimits;

class ExportedByYP00IMPL CATCGMDefSurface : public CATCGMDefGeometry
{
public:

  CATCGMDefSurface();
  virtual ~CATCGMDefSurface();
  
  /** @nodoc */
  virtual void PropagateQuery(CATICGMUnknown *iFrom, const CATSurLimits & iLimits, CATCGMQueryManager &iQuery );
};

#endif
