//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATContextExtrapol:
//   Function used to extrapol one of the support of a given fillet at a given
//   Point and Tangent.
//   The point and the tangent are in dimension 4 or more. The two first 
//   coordinate are one the first surface and the the third and fourth are
//   on the second surface support.

//=============================================================================
// Usage notes:
//=============================================================================
// Sep. 98     Creation                                       P. Sebah
//=============================================================================
#ifndef CATContextExtrapol_h
#define CATContextExtrapol_h

#include "Y30UIUTI.h"

enum CATContextExtrapolDiagnostic { NoSurfaceExtrapolated=1, FirstSurfaceExtrapolated, 
SecondSurfaceExtrapolated, ThirdSurfaceExtrapolated, FirstSecondSurfaceExtrapolated, 
FirstThirdSurfaceExtrapolated, SecondThirdSurfaceExtrapolated, InsideBothSurface,
EdgeCurveExtrapolated, SurfaceExtrapolated, FirstEdgeCurveExtrapolated, SecondEdgeCurveExtrapolated};


ExportedByY30UIUTI CATContextExtrapolDiagnostic
CATContextExtrapol (CATGeoFactory *iFactory, 
										CATSurface *ioSurf1, const CATSurLimits &iDomSurf1, const CATSurLimits &iDomMaxSurf1, 
										CATSurface *ioSurf2, const CATSurLimits &iDomSurf2, const CATSurLimits &iDomMaxSurf2, 
										const double *iPoint, double *ioTangentPoint, CATSoftwareConfiguration * iConfig);


ExportedByY30UIUTI CATContextExtrapolDiagnostic
CATContextExtrapol (CATGeoFactory *iFactory, 
										CATSurface *ioSurf, const CATSurLimits &iDomSurf, const CATSurLimits &iDomMaxSurf, 
										CATCurve *ioEdgeCurve, const CATCrvLimits &iDomEC, const CATCrvLimits &iDomMaxEC, 
										const double *iPoint, double *ioTangentPoint, CATSoftwareConfiguration * iConfig);

ExportedByY30UIUTI CATContextExtrapolDiagnostic 
CATContextExtrapol (	CATGeoFactory *iFactory,
                    CATSurface *ioSurf1, const CATSurLimits &iDom1, const CATSurLimits & iDom1Max,
                    CATSurface *ioSurf2, const CATSurLimits &iDom2, const CATSurLimits & iDom2Max,
                    CATSurface *ioSurf3, const CATSurLimits &iDom3, const CATSurLimits & iDom3Max,
                    const double *iPoint, double *ioTangentPoint, CATSoftwareConfiguration * iConfig);

// FCX 06.2002 : Fillet Keep-Keep
ExportedByY30UIUTI CATContextExtrapolDiagnostic
CATContextExtrapol (CATGeoFactory *iFactory, 
										CATCurve *ioEdgeCurve1, const CATCrvLimits &iDomEC1, const CATCrvLimits &iDomMaxEC1, 
										CATCurve *ioEdgeCurve2, const CATCrvLimits &iDomEC2, const CATCrvLimits &iDomMaxEC2, 
										const double *iPoint, double *ioTangentPoint, CATSoftwareConfiguration * iConfig);


ExportedByY30UIUTI double DistancePointDomain (const double u, const double v, 
                                               const double tu, const double tv, 
                                               const double umin, const double vmin,
                                               const double umax, const double vmax,
                                               const CATTolerance & nTol);
#endif
