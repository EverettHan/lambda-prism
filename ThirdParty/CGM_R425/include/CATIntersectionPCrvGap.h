#ifndef CATINTERSECTIONPCRVGAP_H
#define CATINTERSECTIONPCRVGAP_H

// COPYRIGHT DASSAULT SYSTEMES 1999


#include "Y30C1XMM.h"

#include "CATCrvLimits.h"
#include "CATSkillValue.h"

#include "CATConst2D.h"
#include "CATIntersectionPCrvPCrvSign.h"
#include "CATGeoFactory.h"
#include "CATCGMVirtual.h"

// #define CATGAP

class CATMathFunctionX;
class CATSurParam;

class CATPCurve;
class CATEdgeCurve;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATInclusionPtPCrv;

class CATIntersectionPCrvGapPoint;

class ExportedByY30C1XMM CATIntersectionPCrvGap  : public CATCGMVirtual
{
 private:
//- Private Data
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration *_Config;
  // Data about the curve.
  const CATPCurve * pcurve;
  const CATEdgeCurve * _ECrv;
  CATCrvLimits _limit;
  const CATPointOnEdgeCurve * _PoecS, * _PoecE;

  // Data about the gap.
  const CATSurParam * p0, * p1;

  // Tolerence for extremities.
  double TolExtremity;

  // Data about the solution points.
  CATIntersectionPCrvGapPoint *points;
  CATIntersectionPCrvGapPoint *indexpoint;
  CATLONG32 numpoint;

//- Private Methods
  void TestGapExtremities(const CATCrvParam & iStart, const CATCrvParam & iEnd, const CATMathVector2D & iVec);
  void TestPCrvExtremities();
  void IntersectGapArc(const CATLONG32 arc);
  void StorePoint(CATCrvParam & par,
		  const CATSurParam * point,
		  const CATIntersectionPCrvPCrvSign sign,
		  const CATIntersectionPCrvPCrvCrossing cross,
		  const CATPointPositionOnCurve ext);
  void DestroyResults();

 public:
//- Constructor
   CATIntersectionPCrvGap (CATGeoFactory * Factory,
        CATSoftwareConfiguration *iConfig,
			  const CATPCurve * Pcurve,
			  const CATSurParam * P0,
			  const CATSurParam * P1);
  CATIntersectionPCrvGap (CATGeoFactory * Factory,
        CATSoftwareConfiguration *iConfig,
			  const CATPCurve * Pcurve,
			  const CATCrvLimits & Limit1,
			  const CATSurParam * P0,
			  const CATSurParam * P1);

  CATIntersectionPCrvGap (CATGeoFactory * Factory,
        CATSoftwareConfiguration *iConfig,
                          const CATEdgeCurve * iECrv,
			  const CATPCurve * Pcurve,
			  const CATPointOnEdgeCurve * iStartPoec,
                          const CATPointOnEdgeCurve * iEndPoec,
			  const CATSurParam * P0,
			  const CATSurParam * P1);

//- Destructor
  ~CATIntersectionPCrvGap();

//- Public methods
  void Run();
  void SetExtremityTol(const double tol/* = CATTolZero*/); //IEY //07-09-07 //Hard coded tolerance migration

  void BeginningPoint();
  CATLONG32  NextPoint();
  CATLONG32  GetNumberOfPoints();
  CATPointOnCurve * GetPointOnCurve();
  CATPointPositionOnCurve GetPointPositionOnCurve();
  const CATSurParam * GetSurParam();
  CATIntersectionPCrvPCrvSign GetPointSignature(const CATPCurve * Pcurve);
  CATIntersectionPCrvPCrvSign GetPointSignature(const CATSurParam * P);
  CATIntersectionPCrvPCrvCrossing GetPointCrossing(const CATPCurve * Pcurve);
  CATIntersectionPCrvPCrvCrossing GetPointCrossing(const CATSurParam * P);

  // public methods on CATPointOnEdgeCurve

  CATPointOnEdgeCurve * GetPointOnEdgeCurve();
  CATIntersectionPCrvPCrvSign GetPointSignature(const CATEdgeCurve * Pcurve);
  CATIntersectionPCrvPCrvCrossing GetPointCrossing(const CATEdgeCurve * Pcurve);

};

ExportedByY30C1XMM CATIntersectionPCrvGap*
CATCreateIntersection (CATGeoFactory * Factory,
                       CATSoftwareConfiguration *iConfig,
                       const CATPCurve * Pcurve,
                       const CATSurParam * P0,
                       const CATSurParam * P1,
                       const CATSkillValue skill = BASIC);

ExportedByY30C1XMM CATIntersectionPCrvGap*
CATCreateIntersection (CATGeoFactory * Factory,
                       CATSoftwareConfiguration *iConfig,
                       const CATPCurve * Pcurve,
                       const CATCrvLimits & Limit,
                       const CATSurParam * P0,
                       const CATSurParam * P1,
                       const CATSkillValue skill = BASIC);

ExportedByY30C1XMM CATIntersectionPCrvGap*
CATCreateIntersection (CATGeoFactory * Factory,
                       CATSoftwareConfiguration *iConfig,
                       const CATPointOnCurve * Start,
                       const CATPointOnCurve * End,
                       const CATSurParam * P0,
                       const CATSurParam * P1,
                       const CATSkillValue skill = BASIC);

ExportedByY30C1XMM CATIntersectionPCrvGap*
CATCreateIntersection (CATGeoFactory * Factory,
                       CATSoftwareConfiguration *iConfig,
                       const CATPointOnEdgeCurve * Start,
                       const CATPointOnEdgeCurve * End,
                       const CATPCurve * iPCrv,
                       const CATSurParam * P0,
                       const CATSurParam * P1,
                       const CATSkillValue skill = BASIC);

ExportedByY30C1XMM void Remove(CATIntersectionPCrvGap * Intersection);

#endif
