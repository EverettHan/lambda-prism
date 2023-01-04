// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATWireOnSurfaceSimplif
// Class for operator to Simplify a list of EdgeCurves on a surface.
// 
// This operator takes in input a list of connected edgecurve on a surface
// and return a new list of connected EdgeCurves with isoparametric curves
// or plines when possible. The tolerance is by default the resolution.
// 
// The extremity POECs of the wire should move more than 0.5*resolution
//
//========================================================================
//   /12/02     Creation                                      X.Gourdon
// 12/03/20 Q48 Headers for for math versioning
//========================================================================

#ifndef CATWireOnSurfaceSimplif_h
#define CATWireOnSurfaceSimplif_h

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSurLimits.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATEdgeCurve;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATCrvParam;
class CATSoftwareConfiguration;

class EdgeCrvSimplifData;
class ExportedByY30UIUTI CATWireOnSurfaceSimplif : public CATGeoOperator
{
public:
  
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  
  CATWireOnSurfaceSimplif(CATGeoFactory * iFactory,
                              CATSoftwareConfiguration * iConfig,
                             const CATLONG32 iNbCrv,
                             CATEdgeCurve ** iTabECrv,
                             CATPCurve ** iTabPCrv,
                             CATPointOnEdgeCurve ** iStartPOEC,
                             CATPointOnEdgeCurve ** iEndPOEC,
                             CATSurface * iSurface,
                             const CATSurLimits & iSurLim);

  CATWireOnSurfaceSimplif(CATGeoFactory * iFactory,
                             const CATLONG32 iNbCrv,
                             CATEdgeCurve ** iTabECrv,
                             CATPCurve ** iTabPCrv,
                             CATPointOnEdgeCurve ** iStartPOEC,
                             CATPointOnEdgeCurve ** iEndPOEC,
                             CATSurface * iSurface,
                             const CATSurLimits & iSurLim);

  ~CATWireOnSurfaceSimplif();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  //
  // Set methods
  //
  void SetTolerance(double iTolerance);

  //
  // Running the operator
  //
  int RunOperator();

  //
  // Getting the results
  //
  CATLONG32 GetNumberOfCurves();
  void BeginningCurve();
  CATBoolean NextCurve();
  CATEdgeCurve * GetEdgeCurve(CATPCurve *& oPCrv,
                    CATPointOnEdgeCurve *& oStartPOEC,
                    CATPointOnEdgeCurve *& oEndPOEC);
  // return orientation of the simplified EdgeCurve vs wire (+1 or -1).
  // Note : the orientation is related to the returned EdgeCurve, not the PCurve
  int GetOrientationVsWire();
  //
  // Getting associated simplified EdgeCurves and POECs.
  //
  // InputIndex is in 0..iNbCrv-1 and corresponds to the index in the order
  // of the array of EdgeCurves in the constructor or Create function.
  //
  // The returned EdgeCurve is the simplified EdgeCurve; the returned POECs
  // correspond to the images of the initial poecs at position iInputIndex
  // on the New EdgeCurve. oOrientation is +1 or -1.
  //
  CATEdgeCurve * GetCorrespondingNewGeometries(CATLONG32 iInputIndex,
                    int & oOrientation);
                    
  //-----------------------------------------------------------------------
  //- Protected methods
  //-----------------------------------------------------------------------
  
protected:
  CATBoolean TrySimplifySubset(CATLONG32 iIndexStart, CATLONG32 iIndexEnd);
  CATBoolean TrySimplifyWithPLine(double Start2D[2], double End2D[2],
                                  CATLONG32 iIndexStart, CATLONG32 iIndexEnd);

private:

  // Input data
  CATLONG32 _NbInputEdges;
  CATSurface * _Surface;
  CATSurLimits _SurLim;
  EdgeCrvSimplifData * _InputEdge;
  double _Tolerance, _Resolution; // par default, _Tolerance=_Resolution
  
  // Data for output
  CATLONG32 _NbOutputEdges;
  EdgeCrvSimplifData * _OutputEdge;

  // Internal data
  CATLONG32 _IndexCrv;
  CATSoftwareConfiguration * _Config;
};


#endif
