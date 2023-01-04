#ifndef CATIPGMCanonicalProjectionCrvSur_h_
#define CATIPGMCanonicalProjectionCrvSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATMathPlane;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurface;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCanonicalProjectionCrvSur;

//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMCanonicalProjectionCrvSur: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCanonicalProjectionCrvSur();

  virtual void SetLimits(const CATCrvLimits &iLimits) = 0;

  virtual void SetSupports(CATSurface *iSurf1, CATSurface *iSurf2) = 0;

  //-----------------------------------------------------------------
  //- Iterator
  //-----------------------------------------------------------------
  virtual CATBoolean NextCurve() = 0;

  virtual CATPCurve *GetPCurve() = 0;

  virtual CATCurve *GetCurve() = 0;

  virtual CATLONG32 GetOrientation() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCanonicalProjectionCrvSur(); // -> delete can't be called
};

#endif /* CATIPGMCanonicalProjectionCrvSur_h_ */
