#ifndef CATPGMUtilSurSurGen_h_
#define CATPGMUtilSurSurGen_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATIntersectionSign.h"

#include "CATGeoOpArchiTEMP.h"

#ifndef NULL
#define NULL 0
#endif

class CATCircle;
class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATFilletSurface;
class CATGenericFillet;
class CATGeoFactory;
class CATLine;
class CATMathBox;
class CATMathDirection2D;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATMathImplicitSystem;
class CATMathInterval;
class CATMathIntervalND;
class CATMathLine2D;
class CATMathPlane;
class CATMathPoint;
class CATMathPoint2D;
class CATMathSetOfPointsND;
class CATMathVector;
class CATNurbsSurface;
struct CATPipeData;
class CATPlane;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATSweepSurface;
class CATTolerance;
class CATEdgeCurve;
class CATPCurve;
class CATCone;
class CATSphere;

//
// Test if the two limited surfaces iSurface0 and iSurface1 may intersect at iTol
// and if the result is intersecting a given box iSearchBox.
// 
// Method for canonical surfaces, planes and offset surfaces.
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMIsSurfaceIntersecting(
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface0,
  CATSurLimits *iLimitOn0,
  CATSurface *iSurface1,
  CATSurLimits *iLimitOn1,
  CATMathBox &iSearchBox,
  double iTol);

//
// Test if the two limited surfaces iSurface0 and iSurface1 may intersect at iTol
// and if the result is intersecting a given box iSearchBox. 
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMIsCanonicalIntersecting(
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface0,
  CATSurLimits *iLimitOn0,
  CATMathBox &iSurfBox0,
  CATSurface *iSurface1,
  CATSurLimits *iLimitOn1,
  CATMathBox &iSurfBox1,
  CATMathBox &iSearchBox,
  double iTol);

//
// Test if the implicit surface iSurface0 is intersecting the limited surface 
// iSurface1 and if the result is intersecting a given box iSearchBox.
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMIsFirstImplicitIntersecting(
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface0,
  CATSurface *iSurface1,
  CATSurLimits *iLimitOn,
  CATMathBox &iSurfBox1,
  CATMathBox &iSearchBox,
  double iTol);

//
// Test if iSurface0 is a ProcOffset of iSurface1, in which case we assume their
// intersection is empty. Also Offset of GenericFillet
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMIsFirstProcOffsetIntersecting(
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurf0,
  CATSurface *iRep0,
  CATSurLimits &iLim0,
  CATSurface *iSurf1,
  CATSurface *iRep1,
  CATSurLimits &iLim1,
  double iTol);

//
// Test if surfaces are ProcOffset of same surface, in which case we assume their
// intersection is empty. Also Offset of GenericFillet
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMIsProcOffsetOfSameIntersecting(
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurf0,
  CATSurface *iRep0,
  CATSurLimits &iLim0,
  CATSurface *iSurf1,
  CATSurface *iRep1,
  CATSurLimits &iLim1,
  double iTol);

//
// Return the "distance" (Max Min) between a polygon and a 3d circle defined
// by it's center iC and an orthornomal base (iI, iJ, iK).
// 
ExportedByCATGMModelInterfaces double CATPGMDeviationPolygonCircle(
  CATSoftwareConfiguration *iConfig,
  const CATMathSetOfPointsND &iPolygon,
  const double iRadius,
  const double iC[3],
  const double iI[3],
  const double iJ[3],
  const double iK[3]);

// 
// Return the distance between two polygons iSet0 and iSet1 (specific use only). The distance
// is given only when oDiag=1. 
//
ExportedByCATGMModelInterfaces double CATPGMDistance(
  CATSoftwareConfiguration *iConfig,
  const CATLONG32 iNbPt0,
  const CATMathPoint iSet0[],
  const CATLONG32 iNbPt1,
  const CATMathPoint iSet1[],
  const CATTolerance &iTol,
  double &oW0,
  double &oW1,
  CATLONG32 &oDiag,
  CATBoolean iDoublePoint = FALSE);

//
// Test if a fillet surface iFillet is intersecting a surface iSurface.
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMIsFilletIntersectingSurface(
  CATSoftwareConfiguration *iConfig,
  CATSurface *iFillet,
  CATSurface *iRepFillet,
  CATSurLimits *iLimitOnFillet,
  CATSurface *iSurface,
  CATSurface *iRepSurface,
  CATSurLimits *iLimitOnSurface,
  double iTol);

//
// Test if a fillet surface iFillet is intersecting a surface iSurface (internal)
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMIsFilletIntersectingSurface(
  CATSoftwareConfiguration *iConfig,
  CATFilletSurface *iFillet,
  CATSurLimits *iLimitOnFillet,
  CATSurface *iSurface,
  CATSurLimits *iLimitSurface,
  double iTol);

#ifdef Q48_IntSurSur_KeepImproveStartingPointInterface
//
// Test and improve a marching Starting point iStartPoint.
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMImproveStartingPoint(
  CATSoftwareConfiguration *iConfig,
  const double iStartPoint[4],
  const CATMathIntervalND *iDomain,
  CATMathImplicitSystem *iImplicitSystem,
  const CATTolerance &iTolObject,
  double oStartPoint[4]);
#endif // Q48_IntSurSur_KeepImproveStartingPointInterface

//
// Compare the transverse curvature at a point on the intersection of two surfaces
//        The return value is 1 if the two curvature are the same and not singular. 
//        It's 0 otherwise.
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMCompareCurvatureAtPoint(
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface0,
  CATSurface *iSurface1,
  const double *iUVRS,
  const double *iDirUVRS);

//
// Compute the curvature oCurvature on the surface iSurface 
// at point iUV along a direction othogonal to iDirUV. 
// The return value is 1 when success and 0 in cas of failure.
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMCurvatureTransverseToDirection(
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  const double *iUV,
  const double *iDirUV,
  double &oCurvature);

// 
// If the startpoint is on the frontier of the domain
// the start tangent is projected on this domain if it's "colinear" to a one of it's border.
//        
ExportedByCATGMModelInterfaces void CATPGMProjectTangent(
  CATSoftwareConfiguration *iConfig,
  const CATMathIntervalND &iDomain,
  double iStartPoint[4],
  const CATTolerance &iTol,
  double ioStartTangent[4]);

//Do not use from V5R15 - Use the method with CATSoftwareConfiguration
ExportedByCATGMModelInterfaces void CATPGMProjectTangent(
  const CATMathIntervalND &iDomain,
  double iStartPoint[4],
  const CATTolerance &iTol,
  double ioStartTangent[4]);

// On regarde ou se trouve le point par rapport aux domaines fournis
// a la tolerance iTol, qui devra etre en general de l'ordre de CATEpsg (1.e-12)	            
// 		  ________+1_____________                _________+1____________ 
//		 |                       |              |                       |
// 	i	 |                       |            i |                       |
//	n	 | ^                     |            n |                       |
//	d	 | |  Domaine (u,v)      |            d |       Domaine (r,s)   |
//	e      -1| v                     | +1      -1 e |                       |+1 
//	x	 |        u ->           |            x |                       |   
//	1	 |_______________________|            3 |_______________________|
//			-1  index 0                        -1   index 2      
// On remplit un tableau de dimension egale a la dimension de l'espace de travail
// de la facon suivante:
//   0 : Si le point est a l'interieur de l'intervalle correspondant a la coordonnee
//  -1 : Si le point est sur le min de l'intervalle correspondant a la coordonnee
//  +1 : Si le point est sur le max de l'intervalle correspondant a la coordonnee
// De plus la methode renvoie True si au moins une case du tableau est remplie
// sinon, elle renvoie False
// iSurface peut contenir un tableau de deux surfaces afin de les identifier pour
// d'eventuelle traitement canonique
ExportedByCATGMModelInterfaces CATBoolean CATPGMIsPointOnBorder(
  CATSoftwareConfiguration *iConfig,
  const CATMathIntervalND &iDomain,
  const double *iPoint,
  CATLONG32 *ioSaturatedVar,
  const double iTol,
  const double iDomainScale = 1.0,
  const CATSurface **iSurface = NULL);

//
// Fast intersection of Curves from their 3D equations
//
ExportedByCATGMModelInterfaces CATLONG32 CATPGMFastIntersectionCrvCrv(
  CATSoftwareConfiguration *iConfig,
  const CATMathFunctionX * XYZ0[3],
  const CATMathFunctionX * XYZ1[3],
  const CATMathInterval &I0,
  const CATMathInterval &I1,
  CATLONG32 nbpt0,
  CATLONG32 nbpt1,
  double iTolerance,
  const CATTolerance &iTol,
  CATMathSetOfPointsND &oSolutions,
  CATBoolean iDoublePoint = FALSE);

// DAD: week 37/2008; Performance Services combination of GetSignatureOn and GetCrossingOn
// !!!! CAUTION !!!! These services are prototypes: do not use without authorization from DAD.
// Arguments description:
// iConfig: the software configuration
// iPCrv: input 2 PCurves, solution of intersection between two surfaces
// iPCrvLim: input limits of the two curves
// iSurface: input 2 surfaces intersected that gives the previous 2 PCurves as a solution
// iSurLim: limits of the two surfaces
// ioCrvType: int value (-1: unknown; 0: admissible curve; 1: interior curve)
ExportedByCATGMModelInterfaces void CATPGMGetCrossingAndSignature(
  CATSoftwareConfiguration *iConfig,
  CATEdgeCurve *iEdgeCrv,
  CATPCurve * iPCrv[2],
  CATCrvLimits iPCrvLim[2],
  CATSurface * iSurface[2],
  CATSurLimits iSurLim[2],
  CATIntersectionSign oIntSign[2],
  CATIntersectionCrossing oIntCross[2],
  CATLONG32 *ioCrvType = NULL);

// Do not use (relies on surface current limits). Only kept because it is in CGM interface
ExportedByCATGMModelInterfaces short CATPGMTransformAngleToWithinConeRange(
  CATSoftwareConfiguration *iConfig,
  const CATTolerance &iTol,
  const CATCone *iCone,
  CATAngle &ioAngle);

// Do not use (relies on surface current limits). Only kept because it is in CGM interface
ExportedByCATGMModelInterfaces short CATPGMTransformAngleToWithinSphereRange(
  CATSoftwareConfiguration *iConfig,
  const CATTolerance &iTol,
  const CATSphere *iSphere,
  CATAngle &ioAngle);

ExportedByCATGMModelInterfaces CATBoolean CATPGMTransformAngleToWithinRange(
  CATSoftwareConfiguration *iConfig,
  const CATTolerance &iTol,
  const CATAngle iMinAngle,
  const CATAngle iMaxAngle,
  CATAngle &ioAngle);

#endif /* CATPGMUtilSurSurGen_h_ */
