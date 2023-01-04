// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATSecondOrderConvecity :
// Class to know the second order convexity of an EdgeCurve
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
// Mar. 01  Creation                          X. Gourdon
//=============================================================================

#ifndef CATSecondOrderConvexity_H
#define CATSecondOrderConvexity_H 

/* useless code
#include "Y30UIUTI.h"

#include "CATGeoOperator.h"

class CATSurface;
class CATPCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATSecondOrderConvexity : public CATGeoOperator
{
public:
  // Constructor.
  //
  // OriVsFace1 or OriVsFace2 takes their value in {-1,+1}
  CATSecondOrderConvexity(CATGeoFactory * iFactory,
    CATSurface * iSurf1, CATSurface * iSurf2,
    int OriVsFace1, int OriVsFace2,
    CATPCurve * iPCrv1, CATPCurve * iPCrv2, CATEdgeCurve * iECrv,
    CATPointOnEdgeCurve * iPOECStart, CATPointOnEdgeCurve * iPOECEnd);

  CATSecondOrderConvexity(CATGeoFactory * iFactory,CATSoftwareConfiguration * iConfig,
    CATSurface * iSurf1, CATSurface * iSurf2,
    int OriVsFace1, int OriVsFace2,
    CATPCurve * iPCrv1, CATPCurve * iPCrv2, CATEdgeCurve * iECrv,
    CATPointOnEdgeCurve * iPOECStart, CATPointOnEdgeCurve * iPOECEnd);

  ~CATSecondOrderConvexity();

  // Set the tool maximum radius (permits to have a tolerance for 
  // the flat convexity). The default is the geometric infinite.
  void SetMaxToolRadius(double iMaxToolRadius);

  int RunOperator();

	enum CATConvexity { Concav=-1, Flat=0, Convex=1, Unknown } ;

  CATSecondOrderConvexity::CATConvexity GetConvexity();

  // private methods
private:
  CATSecondOrderConvexity::CATConvexity ComputeConvexity(int iIndex);

private:
  // input data
  CATSurface * _Surf[2];
  int _OriVsFace[2];
  CATPCurve * _PCrv[2];
  CATEdgeCurve * _ECrv;
  CATPointOnEdgeCurve * _POECStart, * _POECEnd;
  double _ToolMaxRadius;
  CATSoftwareConfiguration * _Config;

  // output data
  CATSecondOrderConvexity::CATConvexity _Convexity;
};
*/

#endif
