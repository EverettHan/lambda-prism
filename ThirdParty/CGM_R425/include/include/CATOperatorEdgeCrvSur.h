
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATIntersectionEgdeCurveSur :
// Interface class for intersection of an EdgeCurve with a Surface
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Nov. 97  Creation                          P. Sebah & X. Gourdon
//=============================================================================

#ifndef CATOperatorEdgeCrvSur_H 
#define CATOperatorEdgeCrvSur_H 

/* useless code 
#include "CATMathDef.h"
#include "CATIntersectionSign.h"
#include "CATCGMOperator.h"

class CATEdgeCurve; 
class CATSurface;
class CATPointOnEdgeCurve; 
class CATMergedCurve; 
class CATCurve;
class CATCrvLimits;
class CATSurLimits;
class CATSurParam;

// DG
// class CATOperatorEdgeCrvSur 
#include "Y30C3XGG.h"
class ExportedByY30C3XGG CATOperatorEdgeCrvSur  : public CATCGMOperator
{
  public:
    
    CATOperatorEdgeCrvSur(CATGeoFactory * factory);
    virtual ~CATOperatorEdgeCrvSur();
    virtual void SetLimits(const CATCrvLimits &iLimitsCrv) = 0; 
    virtual void SetLimits(const CATSurLimits &iLimitsSur) = 0; 

    virtual CATIntersectionSign  GetSignature() const = 0;
//
//  Getting the isolated solutions between the edgecurve and the surface
//
    virtual CATLONG32                  GetNumberOfPoints() const = 0;
    virtual void                  BeginningPoint() = 0;
    virtual CATBoolean            NextPoint() = 0;
    virtual CATPointOnEdgeCurve * GetPointOnEdgeCurve() = 0;
    virtual void                  GetSurfaceParam (const CATCurve * iCrv, 
						   CATSurParam & oParam) const = 0;
//
//  Getting the merged curves solutions between the edge curve and the surface
//
    virtual CATLONG32             GetNumberOfCurves() const = 0;  
    virtual void             BeginningCurve() = 0;
    virtual CATBoolean       NextCurve() = 0;
    virtual CATMergedCurve * GetMergedCurve(CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd) = 0;   
};
*/
#endif
