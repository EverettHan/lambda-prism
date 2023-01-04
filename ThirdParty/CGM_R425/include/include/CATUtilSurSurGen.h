   #define ShuntOldDeprecatedFastIntersectionCrvCrv "NLD141020"
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATUtilSurSurGen.h
//  Base class for intersection of surfaces utilitaries
//
//=============================================================================
// Dec.  99 PSH Creation                                               P. Sebah
// 07/12/07 NLD XScale: Argument iDomainScale a IsPointOnBorder()
// 02/07/08 NLD A FAIRE APRES MIGRATION: Suppression du IsCanonicalIntersecting() sans configuration
// 25/01/11 FDS Mise en commentaires de 7 routines inutiles et suppression des exported by inutiles
// 27/02/13 R1Y Added functions to obtain canonical data from a 4D quintic.
// 15/03/13 R1Y Added the function CreateIntCurveFromMap().
// 15/07/13 JSX Added CATTolerance in Intersect2D
// 02/09/13 Q48 Added functions to treat cone-apex case in Sur-Sur and Crv-Sur intersections
// 27/05/14 Q48 Added functions to treat line-circle intersections for SurSurGen
// 20/05/15 Q48 Added functions to treat sphere-pole case in Sur-Sur intersections
// 04/05/16 Q48 Added functions to remove dependency on current limits
// 28/03/19 Q48 Move IsPCurveAPLine/IsPCurveAPCircle to CATSurSurResultCurve
// 14/10/20 NLD Shunt two deprecated FastIntersectionCrvCrv signatures
// 16/10/20 NLD IntersectLineInsidePlane() and Intersect2D() receive software configuration
// 07/07/21 Q48 Move ImproveStartingPoint to CATIntersectionSurSurGen and remove unused interface
// 18/10/21 S9L Utility for frontier intersection using standard CATIntersectionCrvCrv
//=============================================================================
//
#ifndef CATUtilSurSurGen_h
#define CATUtilSurSurGen_h
//
#include "Y30C3XGG.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATTolerance.h"
#include "CATIntersectionSign.h"
class CATSurface;
class CATFilletSurface;
class CATGenericFillet;
class CATSweepSurface;
class CATNurbsSurface;
class CATSurLimits;
class CATCurve;
class CATPCurve;
class CATLine;
class CATCircle;
class CATEdgeCurve;
class CATCrvLimits;
class CATCrvParam;
class CATSurParam;
class CATMathImplicitSystem;
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATMathPoint;
class CATMathVector;
class CATMathBox;
class CATMathInterval;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATMathLine2D;
class CATMathPoint2D;
class CATMathDirection2D;
class CATMathVector2D;
class CATPlane;
class CATCone;
class CATSphere;
class CATMathPlane;
class CATIntCurve;
struct CATPipeData;

// Temp
#include "CATGeoOpArchiTEMP.h"

//
// Test if the two limited surfaces iSurface0 and iSurface1 may intersect at iTol
// and if the result is intersecting a given box iSearchBox.
// 
// Method for canonical surfaces, planes and offset surfaces.
//
ExportedByY30C3XGG CATLONG32 IsSurfaceIntersecting(CATSoftwareConfiguration * iConfig,
                                                   CATSurface               * iSurface0, 
                                                   CATSurLimits             * iLimitOn0,
                                                   CATSurface               * iSurface1, 
                                                   CATSurLimits             * iLimitOn1,
                                                   CATMathBox               & iSearchBox, 
                                                   double iTol); 

//
// Test if the two limited surfaces iSurface0 and iSurface1 may intersect at iTol
// and if the result is intersecting a given box iSearchBox. 
//
ExportedByY30C3XGG CATLONG32 IsCanonicalIntersecting(CATSoftwareConfiguration * iConfig,
                                                     CATSurface               * iSurface0, 
                                                     CATSurLimits             * iLimitOn0, 
                                                     CATMathBox               & iSurfBox0,
                                                     CATSurface               * iSurface1, 
                                                     CATSurLimits             * iLimitOn1, 
                                                     CATMathBox               & iSurfBox1,
                                                     CATMathBox               & iSearchBox, 
                                                     double                     iTol); 

/*
CATLONG32 IsCanonicalIntersecting (CATSurface * iSurface0, CATSurLimits * iLimitOn0,
                                   CATSurface * iSurface1, CATSurLimits * iLimitOn1,
                                   CATMathBox & iSearchBox, double iTol); 
*/
//
// Test if the implicit surface iSurface0 is intersecting the limited surface 
// iSurface1 and if the result is intersecting a given box iSearchBox.
//
CATLONG32 IsFirstImplicitIntersecting(CATSoftwareConfiguration * iConfig,
                                      CATSurface               * iSurface0, 
                                      CATSurface               * iSurface1, 
                                      CATSurLimits             * iLimitOn,
                                      CATMathBox               & iSurfBox1, 
                                      CATMathBox               & iSearchBox, 
                                      double                     iTol);

//
// Test if iSurface0 is a ProcOffset of iSurface1, in which case we assume their
// intersection is empty. Also Offset of GenericFillet
//
CATLONG32 IsFirstProcOffsetIntersecting(CATSoftwareConfiguration * iConfig,
                                        CATSurface               * iSurf0, 
                                        CATSurface               * iRep0, 
                                        CATSurLimits             & iLim0,
                                        CATSurface               * iSurf1, 
                                        CATSurface               * iRep1, 
                                        CATSurLimits             & iLim1,
                                        double                     iTol);


//
// Test if surfaces are ProcOffset of same surface, in which case we assume their
// intersection is empty. Also Offset of GenericFillet
// 
CATLONG32 IsProcOffsetOfSameIntersecting(CATSoftwareConfiguration * iConfig,
                                         CATSurface               * iSurf0, 
                                         CATSurface               * iRep0, 
                                         CATSurLimits             & iLim0,
                                         CATSurface               * iSurf1, 
                                         CATSurface               * iRep1, 
                                         CATSurLimits             & iLim1,
                                         double                     iTol);


//
// Return the "distance" (Max Min) between a polygon and a 3d circle defined
// by it's center iC and an orthornomal base (iI, iJ, iK).
// 
double DeviationPolygonCircle(      CATSoftwareConfiguration * iConfig,
                              const CATMathSetOfPointsND     & iPolygon,
                              const double                     iRadius, 
                              const double                     iC[3],
                              const double                     iI[3], 
                              const double                     iJ[3], 
                              const double                     iK[3]);
// 
// Return the distance between two polygons iSet0 and iSet1 (specific use only). The distance
// is given only when oDiag=1. 
//
double Distance(      CATSoftwareConfiguration * iConfig,
                const CATLONG32                  iNbPt0, 
                const CATMathPoint               iSet0[], 
                const CATLONG32                  iNbPt1, 
                const CATMathPoint               iSet1[],
                const CATTolerance             & iTol,
                      double                   & oW0, 
                      double                   & oW1, 
                      CATLONG32                & oDiag,
                      CATBoolean                 iDoublePoint = FALSE);  
//
// Test if a fillet surface iFillet is intersecting a surface iSurface.
//
CATLONG32 IsFilletIntersectingSurface(CATSoftwareConfiguration * iConfig,
                                      CATSurface               * iFillet, 
                                      CATSurface               * iRepFillet,
                                      CATSurLimits             * iLimitOnFillet,
                                      CATSurface               * iSurface, 
                                      CATSurface               * iRepSurface,
                                      CATSurLimits             * iLimitOnSurface,
                                      double                     iTol); 
//
// Test if a fillet surface iFillet is intersecting a surface iSurface (internal)
//
CATLONG32 IsFilletIntersectingSurface(CATSoftwareConfiguration * iConfig,
                                      CATFilletSurface         * iFillet, 
                                      CATSurLimits             * iLimitOnFillet,
                                      CATSurface               * iSurface, 
                                      CATSurLimits             * iLimitSurface,
                                      double                     iTol); 

#ifdef Q48_IntSurSur_KeepImproveStartingPointInterface
//
// Test and improve a marching Starting point iStartPoint.
//
CATLONG32 ImproveStartingPoint(      CATSoftwareConfiguration * iConfig,
                               const double                     iStartPoint[4], 
                               const CATMathIntervalND        * iDomain, 
                                     CATMathImplicitSystem    * iImplicitSystem, 
                               const CATTolerance             & iTolObject,
                                     double                     oStartPoint[4]);
#endif // Q48_IntSurSur_KeepImproveStartingPointInterface

//
// Compare the transverse curvature at a point on the intersection of two surfaces
//        The return value is 1 if the two curvature are the same and not singular. 
//        It's 0 otherwise.
//
CATLONG32 CompareCurvatureAtPoint(      CATSoftwareConfiguration * iConfig,
                                        CATSurface               * iSurface0, 
                                        CATSurface               * iSurface1,
                                  const double                   * iUVRS, 
                                  const double                   * iDirUVRS);
//
// Compute the curvature oCurvature on the surface iSurface 
// at point iUV along a direction othogonal to iDirUV. 
// The return value is 1 when success and 0 in cas of failure.
//
CATLONG32 CurvatureTransverseToDirection (      CATSoftwareConfiguration * iConfig,
                                                CATSurface               * iSurface, 
                                          const double                   * iUV, 
                                          const double                   * iDirUV, 
                                                double                   & oCurvature);
// 
// If the startpoint is on the frontier of the domain
// the start tangent is projected on this domain if it's "colinear" to a one of it's border.
//        
void       ProjectTangent(      CATSoftwareConfiguration * iConfig,
                          const CATMathIntervalND        & iDomain, 
                                double                     iStartPoint[4], 
                          const CATTolerance             & iTol,
                                double                     ioStartTangent[4]);

//Do not use from V5R15 - Use the method with CATSoftwareConfiguration
void       ProjectTangent(const CATMathIntervalND & iDomain, 
                                double              iStartPoint[4], 
                          const CATTolerance      & iTol, 
                                double              ioStartTangent[4]);

// On regarde ou se trouve le point par rapport aux domaines fournis
// a la tolerance iTol, qui devra etre en general de l'ordre de CATEpsg (1.e-12)
//             ________+1_____________                _________+1____________ 
//            |                       |              |                       |
//     i      |                       |            i |                       |
//     n      | ^                     |            n |                       |
//     d      | |  Domaine (u,v)      |            d |       Domaine (r,s)   |
//     e    -1| v                     | +1      -1 e |                       |+1 
//     x      |        u ->           |            x |                       |   
//     1      |_______________________|            3 |_______________________|
//               -1  index 0                        -1   index 2      
// On remplit un tableau de dimension egale a la dimension de l'espace de travail
// de la facon suivante:
//   0 : Si le point est a l'interieur de l'intervalle correspondant a la coordonnee
//  -1 : Si le point est sur le min de l'intervalle correspondant a la coordonnee
//  +1 : Si le point est sur le max de l'intervalle correspondant a la coordonnee
// De plus la methode renvoie True si au moins une case du tableau est remplie
// sinon, elle renvoie False
// iSurface peut contenir un tableau de deux surfaces afin de les identifier pour
// d'eventuelle traitement canonique
CATBoolean IsPointOnBorder(      CATSoftwareConfiguration * iConfig,
                           const CATMathIntervalND        & iDomain, 
                           const double                   * iPoint,
                                 CATLONG32                * ioSaturatedVar,
                           const double                     iTol,
                           const double                     iDomainScale = 1.0,
                           const CATSurface              ** iSurface = NULL);


//
// Fast intersection of Curves from their 3D equations
//
//  FastIntersectionCrvCrv_0Kept
CATLONG32 FastIntersectionCrvCrv(      CATSoftwareConfiguration * iConfig,
                                 const CATMathFunctionX         * XYZ0[3],
                                 const CATMathFunctionX         * XYZ1[3],
                                 const CATMathInterval          & I0,
                                 const CATMathInterval          & I1,
                                       CATLONG32                  nbpt0, 
                                       CATLONG32                  nbpt1,
                                       double                     iTolerance,
                                 const CATTolerance             & iTol,
                                       CATMathSetOfPointsND     & oSolutions,
                                       CATBoolean                 iDoublePoint = FALSE);

#ifndef ShuntOldDeprecatedFastIntersectionCrvCrv
// @nocgmitf DAD Week 35/2008: deprecated; use FastIntersectionCrvCrvTol instead
//    (with current curve limits through GetLimits())
//    FastIntersectionCrvCrv_1Deprecated
void       FastIntersectionCrvCrv(      CATSoftwareConfiguration * iConfig,
                                        CATCurve                 * iCurve0, 
                                        CATCurve                 * iCurve1,
                                        double                     Tol2, 
                                  const CATTolerance             & iTol,
                                        CATMathSetOfPointsND     & oSolutions);
#endif
// @nocgmitf DAD Week 35/2008: deprecated; use FastIntersectionCrvCrvTol instead
// 09/2004 pkc : pour supprimer les GetLimits
//  FastIntersectionCrvCrv_2Deprecated
#ifndef ShuntOldDeprecatedFastIntersectionCrvCrv
void       FastIntersectionCrvCrv(      CATSoftwareConfiguration * iConfig,
                                        CATCurve                 * iCurve0,
                                        CATCrvLimits             & iLim0,
                                        CATCurve                 * iCurve1,
                                        CATCrvLimits             & iLim1,
                                        double                     Tol2,
                                  const CATTolerance             & iTol,
                                        CATMathSetOfPointsND     & oSolutions);
#endif


// @nocgmitf DAD Week 35/2008: new service using a simple tolerance instead of a squared one
void ExportedByY30C3XGG FastIntersectionCrvCrvTol(      CATSoftwareConfiguration * iConfig,
                                                        CATCurve                 * iCurve0,
                                                        CATCrvLimits             & iLim0,
                                                        CATCurve                 * iCurve1,
                                                        CATCrvLimits             & iLim1,
                                                        double                     iSimpleTol,
                                                  const CATTolerance             & iTol,
                                                        CATMathSetOfPointsND     & oSolutions);

// @nocgmitf use of standard intersection operator for intersection of two curves
void ExportedByY30C3XGG IntersectionCrvCrvTol(CATSoftwareConfiguration * iConfig,
                                              CATCurve                 * iCurve0,
                                              CATCrvLimits             & iLim0,
                                              CATCurve                 * iCurve1,
                                              CATCrvLimits             & iLim1,
                                              double                     iSimpleTol,
                                              CATMathSetOfPointsND     & oSolutions);

//void CrvCrvReconvergeInits(CATSoftwareConfiguration * iConfig,
//                           CATCurve                 * iCurve0, 
//                           CATCurve                 * iCurve1,
//                           double                     lo0, 
//                           double                     hi0, 
//                           double                     lo1, 
//                           double                     hi1,
//                           double                     Tol2, 
//                           CATMathSetOfPointsND     & iInits,
//                           CATMathSetOfPointsND     & oSolutions);

// @nocgmitf Q48 week 21/2014: reconvergence helper function for FastIntersectionLineCircle
CATBoolean CrvCrvReconvergeInit(      CATSoftwareConfiguration * iConfig,
                                const CATCurve                 * iCurve0, 
                                const CATCurve                 * iCurve1,
                                const CATMathInterval          & iDomain0,
                                const CATMathInterval          & iDomain1,
                                const double                     iTol,
                                const CATTolerance             & iTolObject,
                                      double                     ioInit[]);

// @nocgmitf Q48 week 21/2014: special treatment of line/circle case
void       FastIntersectionLineCircle(      CATSoftwareConfiguration * iConfig,
                                            CATLine                  * iLine, 
                                            CATCircle                * iCircle,
                                      const double                     iTol,
                                            CATMathSetOfPointsND     & oSolutions);

// @nocgmitf Q48 week 21/2014: common code for crv/crv minimisation
CATBoolean FastIntersectionCrvCrv_Minimisation(      CATSoftwareConfiguration * iConfig,
                                               const CATMathFunctionX         * iEq0[],
                                               const CATMathFunctionX         * iEq1[],
                                               const CATMathInterval          & iDomain0,
                                               const CATMathInterval          & iDomain1,
                                               const CATTolerance             & iTolObject,
                                                     double                     ioInit[],
                                                     double                   & oDist);

// @nocgmitf
// Returns distance between point iA and segment [iP,iQ]
// Stores parametre where this distance occurs on the segment in ow (0.<=ow<=1.)
// oDiag = 0 -> OK
// oDiag = 1 -> iP and iQ are confused at CATEpsg; no calculation is made
//

double PointSegmentDistanceSq(      CATSoftwareConfiguration * iConfig,
                              const CATMathPoint             & iA, 
                              const CATMathPoint             & iP, 
                              const CATMathPoint             & iQ, 
                              const CATTolerance             & iTol,
                                    double                   & ow, 
                                    CATLONG32                & oDiag);

/* unused
// @nocgmitf
double PointSegmentDistance(CATSoftwareConfiguration * iConfig,
                            const CATMathPoint & iA, const CATMathPoint & iP, 
                            const CATMathPoint & iQ, const CATTolerance & iTol,
                            double & ow, CATLONG32 & oDiag);
*/



// @nocgmitf
// Returns distance between segment [iP0,iQ0] and segment [iP1,iQ1]
// Stores parametres where this distance occurs on each segment 
// in ow0 and ow1 (0.<=ow0,ow1<=1.)
// oDiag = 0 -> General case
// oDiag = 1 -> the segments lie on parallel lines; ow0 and ow1 may not be unique
// oDiag = 2 -> iP0 and iQ0, or iP1 and iQ1 are confused at CATEpsg; no calculation
//              is made

double SegmentSegmentDistanceSq(      CATSoftwareConfiguration * iConfig,
                                const CATMathPoint             & iP0, 
                                const CATMathPoint             & iQ0,
                                const CATMathPoint             & iP1, 
                                const CATMathPoint             & iQ1, 
                                      double                   * ow0, 
                                      double                   * ow1, 
                                      CATLONG32                & oDiag);

/* unused
// @nocgmitf
double SegmentSegmentDistance(CATSoftwareConfiguration * iConfig,
                              const CATMathPoint & iP0, const CATMathPoint & iQ0,
                              const CATMathPoint & iP1, const CATMathPoint & iQ1, 
                              const CATTolerance & iTol,
                              double * ow0, double * ow1, CATLONG32 & oDiag);

// @nocgmitf Distance between a segment and a polyline
// ow0 (in [0. , 1.]) is the parametre on the segment and ow1 (in [0., NbOfSegments])
// the parametre on the polyline where the distance occurs. 
// oDiag = 0 -> General case
// oDiag = 1 -> Two successive points are confused at CATEpsg; result is meaningless

double SegmentPolyLineDistanceSq(CATSoftwareConfiguration * iConfig,
                                 CATMathPoint & iA, CATMathPoint & iB, 
                                 CATMathSetOfPointsND & iPoints,
                                 const CATTolerance & iTol,
                                 double * ow0, double * ow1, CATLONG32 & oDiag);

// @nocgmitf
double SegmentPolyLineDistance(CATSoftwareConfiguration * iConfig,
                               CATMathPoint & iA, CATMathPoint & iB, 
                               CATMathSetOfPointsND & iPoints,
                               const CATTolerance & iTol,
                               double * ow0, double * ow1, CATLONG32 & oDiag);
*/

// @nocgmitf Distance between two polylines
// ow0 and ow1 are the parametres (starting from 0. at the first point and increasing
// by 1. for each segment) where the minimum segment-segment distance occurs
// oDiag = 0 -> General case
// oDiag = 1 -> Two successive points are confused at CATEpsg; result is meaningless

double PolyLinePolyLineDistanceSq(      CATSoftwareConfiguration * iConfig,
                                        CATMathSetOfPointsND     & Points0, 
                                        CATMathSetOfPointsND     & Points1, 
                                  const CATTolerance             & iTol,
                                        double                   * ow0, 
                                        double                   * ow1, 
                                        CATLONG32                & oDiag);

// @nocgmitf
double PolyLinePolyLineDistance(      CATSoftwareConfiguration * iConfig,
                                      CATMathSetOfPointsND     & Points0, 
                                      CATMathSetOfPointsND     & Points1,
                                const CATTolerance             & iTol,
                                      double                   * ow0, 
                                      double                   * ow1, 
                                      CATLONG32                & oDiag);



/* unused
// @nocgmitf Distance between a segment and a plane;
// segment is parametrized so that w=0. -> iP, w=1. -> iQ
// plane is parametrized so that (u,v)=(0.,0.) -> iA, (u,v)=(1.,0.) -> iB, 
//                               (u,v)=(0.,1.) -> iC
// oDiag = 0 -> OK
// oDiag = 1 -> points confused at CATEpsg, result not meaningful
// oDiag = 2 -> plane degenerated, result not meaningful


double SegmentPlaneDistance(      CATSoftwareConfiguration * iConfig,
                            const CATMathPoint & iP, const CATMathPoint & iQ, 
                            const CATMathPoint & iA, const CATMathPoint & iB,
                            const CATMathPoint & iC, const CATTolerance & iTol,
                                  double & ou, double & ov, double & ow, CATLONG32 & oDiag);

// @nocgmitf
// Distance between a segment and a plane box (like SegmentPlaneDistance but ou and ov are
// restricted to [0.,1.])
//

double SegmentPlaneBoxDistance(CATSoftwareConfiguration * iConfig,
                               const CATMathPoint & iP, const CATMathPoint & iQ, 
                               const CATMathPoint & iA, const CATMathPoint & iB,
                               const CATMathPoint & iC, const CATTolerance & iTol,
                               double & ou, double & ov,
                               double & ow, CATLONG32 & oDiag);

// @nocgmitf
// MaxiMinDist(A,B) = max_{x\in A} min_{y\in B} d(x,y)
//  (note that this is not symmetrical)
// 
// Returns an UPPER BOUND of actual MaxiMinDist
//
// oDiag = 0 -> OK
// oDiag = 1 -> Two successive points are confused at CATEpsg, result is meaningless
//
double MaxiMinDistSegmentPolyLineSq(CATSoftwareConfiguration * iConfig,
                                    CATMathPoint & P, CATMathPoint & Q, 
                                    CATMathSetOfPointsND & Points,
                                    const CATTolerance & iTol,
                                    CATLONG32 & oDiag);
*/

// @nocgmitf
double     MaxiMinDistSegmentPolyLine(         CATSoftwareConfiguration * iConfig,
                                               CATMathPoint             & P, 
                                               CATMathPoint             & Q, 
                                               CATMathSetOfPointsND     & Points,
                                         const CATTolerance             & iTol,
                                               CATLONG32                & oDiag);

// @nocgmitf
double     MaxiMinDistPolyLinePolyLineSq(      CATSoftwareConfiguration * iConfig,
                                               CATMathSetOfPointsND     & Points0, 
                                               CATMathSetOfPointsND     & Points1,
                                         const CATTolerance             & iTol,
                                               CATLONG32                & oDiag);

// @nocgmitf
double     MaxiMinDistPolyLinePolyLine(        CATSoftwareConfiguration * iConfig,
                                               CATMathSetOfPointsND     & Points0, 
                                               CATMathSetOfPointsND     & Points1,
                                         const CATTolerance             & iTol,
                                               CATLONG32                & oDiag);

// @nocgmitf
double     MaxiMinDistPlaneBoxPolyLineSq(      CATSoftwareConfiguration * iConfig,
                                               CATMathPoint             & A, 
                                               CATMathPoint             & B, 
                                               CATMathPoint             & C,
                                               CATMathSetOfPointsND     & Points, 
                                         const CATTolerance             & iTol,
                                               CATLONG32                & oDiag);

// @nocgmitf
double     MaxiMinDistPlaneBoxPolyLine  (      CATSoftwareConfiguration * iConfig,
                                               CATMathPoint             & A, 
                                               CATMathPoint             & B, 
                                               CATMathPoint             & C,
                                               CATMathSetOfPointsND     & Points, 
                                         const CATTolerance       & iTol,
                                               CATLONG32                & oDiag);



// @nocgmitf
//  Non-intersection detection for pipes (pipe/box, pipe/pipe)
//

CATLONG32  IsPipeIntersecting           (      CATSoftwareConfiguration * iConfig,
                                               CATSurface               * iRep[2], 
                                               CATSurLimits               iLim[2], 
                                               CATMathBox                 iSurfBox[2], 
                                               CATPipeData                iPipe[2], 
                                               double                     iTol);

// @nocgmitf Non-intersection utilities Pipe/Box, Pipe/Pipe, Pipe/Curve

CATLONG32  IsPipeBoxIntersecting        (      CATSoftwareConfiguration * iConfig,
                                               CATPipeData              & iPipe, 
                                               CATMathBox               & iBox, 
                                               double                     iTol,
                                         const CATTolerance             & inTol);

// @nocgmitf
CATLONG32  IsPipePipeIntersecting       (      CATSoftwareConfiguration * iConfig,
                                               CATPipeData              * iPipe1, 
                                               CATPipeData              * iPipe2, 
                                               double                     iTol, 
                                         const CATTolerance             & nTol);

// @nocgmitf
CATLONG32  IsPipeCrvIntersecting        (      CATSoftwareConfiguration * iConfig,
                                               CATPipeData              * iPipe, 
                                               CATCurve                 * iCrv, 
                                               CATCrvLimits             * iLim, 
                                               double                     iTol,
                                         const CATTolerance             & nTol);

// @nocgmitf Non-intersection detection for Tabulated
CATLONG32  IsTabulatedIntersecting      (      CATSoftwareConfiguration * iConfig,
                                               CATSurface               * iSurf0, 
                                               CATSurLimits             * ioLimit0, 
                                               CATMathBox               & iSurfBox0,
                                               CATSurface               * iSurf1, 
                                               CATSurLimits             * ioLimit1, 
                                               CATMathBox               & iSurfBox1,
                                               CATMathBox               & iSearchBox);

// @nocgmitf Non-intersection GenericFillet/GenericFillet

CATLONG32 IsGFilletGFilletIntersecting  (      CATSoftwareConfiguration * iConfig,
                                               CATFilletSurface         * iSurf0, 
                                               CATGenericFillet         * iRep0, 
                                               CATSurLimits             * iLim0,
                                               CATFilletSurface         * iSurf1, 
                                               CATGenericFillet         * iRep1,
                                               CATSurLimits             * iLim1, 
                                               double                     iTol);

// @nocgmitf
// Approximate a curve as a polyline and an estimated sag
//

void       DiscretizeCurve(CATSoftwareConfiguration * iConfig,
                           CATCurve                 * iCrv, 
                           CATCrvLimits             * iLim, 
                           CATMathSetOfPointsND     * oPoints, 
                           double                   & oSag);

// @nocgmitf Recursive sampler underlying DiscretizeCurve()

void       RecSample(      CATSoftwareConfiguration * iConfig,
                           double                     w0, 
                           double                     w1, 
                           CATMathSetOfPointsND     * Points, 
                     const CATMathFunctionX         * XYZ[3], 
                     const double                   * F0, 
                     const double                   * F1, 
                           double                   & MaxSag, 
                           CATLONG32                  Depth, 
                           double                     RequestedMaxSag,
                           CATLONG32                  MaxDepth);


/*
void EasyDiscretizeCurve(CATSoftwareConfiguration * iConfig,
                         CATCurve * iCurve, CATMathSetOfPointsND & oPoints,
                         double iResampleParametre2, CATLONG32 iMaxDepth,
                         double & oSag);

void EasyRecSample(CATSoftwareConfiguration * iConfig,
                   CATCrvParam & cp0, CATCrvParam & cp1, 
                   CATMathSetOfPointsND & Points,
                   const CATCurve * Curve, 
                   const CATMathPoint & P0, const CATMathPoint & P1,
                   double & MaxSag, CATLONG32 Depth, double ResampleParametre2,
                   CATLONG32 MaxDepth);
*/

// @nocgmitf
CATLONG32 Intersect2D             (      CATSoftwareConfiguration * iConfig,
                                   const CATMathLine2D            & L1,
                                   const CATMathLine2D            & L2,
                                         double                   & p1,
                                         double                   & p2,
                                   const CATTolerance             & tol,
                                         double                     Tolerance);


// @nocgmitf
CATLONG32 IntersectLineInsidePlane(      CATGeoFactory            * iFactory,
                                         CATSoftwareConfiguration * iConfig,
                                         CATMathLine2D            & solution,
                                         CATMathPlane             & MPlane,
                                   const CATPlane                 * Plane, 
                                         CATSurLimits             * Planelimits,
                                         double                   & min, 
                                         double                   & max,
                                   const CATTolerance             & tol);


// DAD: week 37/2008; Performance Services combination of GetSignatureOn and GetCrossingOn
// !!!! CAUTION !!!! These services are prototypes: do not use without authorization from DAD.
// Arguments description:
// iConfig: the software configuration
// iPCrv: input 2 PCurves, solution of intersection between two surfaces
// iPCrvLim: input limits of the two curves
// iSurface: input 2 surfaces intersected that gives the previous 2 PCurves as a solution
// iSurLim: limits of the two surfaces
// ioCrvType: int value (-1: unknown; 0: admissible curve; 1: interior curve)
ExportedByY30C3XGG void GetCrossingAndSignature(CATSoftwareConfiguration * iConfig, 
                                                CATEdgeCurve             * iEdgeCrv,
                                                CATPCurve                * iPCrv[2], 
                                                CATCrvLimits               iPCrvLim[2],
                                                CATSurface               * iSurface[2], 
                                                CATSurLimits               iSurLim[2],
                                                CATIntersectionSign        oIntSign[2],
                                                CATIntersectionCrossing    oIntCross[2], 
                                                CATLONG32                * ioCrvType = NULL);

// @nocgmitf For internal use of GetCrossingAndSignature
double EvalLocalSignature (      CATSoftwareConfiguration * iConfig, 
                                 CATSurface               * iSurface[2],
                           const CATSurParam                iSurPar[2], 
                           const CATMathVector2D            iTgt[2],
                           const double                     TolAng, 
                           const CATTolerance             & iTolObject,
                                 double                   & oSquareAngleNormals, 
                                 CATLONG32                & oSignScalNormals);

// @nocgmitf For internal use of GetCrossingAndSignature
CATLONG32 EvalCurvatures (      CATSoftwareConfiguration * iConfig, 
                                CATSurface               * iSurface[2],
                          const CATSurParam                iSurPar[2], 
                          const CATMathVector2D            iTgt[2],
                          const CATTolerance             & iTolObject, 
                                double                     oCurvatures[2]);

// @nocgmitf
// Called by Test4dDataForTwoPLines. Samples some points on a Spline and the corresponding Line to see if they match.
CATBoolean TestBy4DSampling(const CATTolerance          &       iTolObject,
                            const CATMathSetOfPointsND  * const iParamsForQuintic,
                            const CATMathSetOfPointsND  * const iPointsForQuintic,
                            const CATMathSetOfPointsND  * const iTangentsForQuintic,
                            const CATMathSetOfPointsND  * const iSecondDerivForQuintic,
                            const CATSurface            * const iSurface0,
                            const CATSurface            * const iSurface1,
                                  CATLONG32                     i);

// @nocgmitf
// Function to determine whether 4D quintic data is effectively two p-lines and, if so, return the appropriate data
// If the return value of this function is TRUE then the value of oIsPLinePLine is correct,
// and if oIsPLinePLine is TRUE then all returned data is reliable
// If the return value of this function is FALSE then an error has occured, and all returned data is unreliable
CATBoolean Test4dDataForTwoPLines(      CATSoftwareConfiguration *       iConfig,
                                  const CATTolerance             &       iTolObject,
                                  const CATMathSetOfPointsND     * const iParamsForQuintic,
                                  const CATMathSetOfPointsND     * const iPointsForQuintic,
                                  const CATMathSetOfPointsND     * const iTangentsForQuintic,
                                  const CATMathSetOfPointsND     * const iSecondDerivForQuintic,
                                  const CATSurface               * const iSurface0,
                                  const CATSurface               * const iSurface1,
                                        CATMathImplicitSystem    * const iImplicitSystem,
                                        CATBoolean               &       oIsPLinePLine,
                                        CATSurParam              &       oSurParamStart0,
                                        CATSurParam              &       oSurParamEnd0,
                                        CATSurParam              &       oSurParamStart1,
                                        CATSurParam              &       oSurParamEnd1);

// @nocgmitf
// Function to determine whether 4D quintic data is effectively a p-line and a p-circle and, if so, return the appropriate data
// If the return value of this function is TRUE then the value of oIsPLinePCircle is correct,
// and if oIsPLinePCircle is TRUE then all returned data is reliable
// If the return value of this function is FALSE then an error has occured, and all returned data is unreliable
CATBoolean Test4dDataForPLinePCircle(      CATSoftwareConfiguration *       iConfig,
                                     const double                           iResolution,
                                     const CATTolerance             &       iTolObject,
                                     const CATMathSetOfPointsND     * const iPointsForQuintic,
                                     const CATSurface               * const iSurface0,
                                     const CATSurface               * const iSurface1,
                                     const CATBoolean                       iCanonicalResultOnRevol,
                                           CATBoolean               &       oIsPLinePCircle,
                                           CATBoolean               &       oPLineIsOnSurface0,
                                           CATSurParam              &       oSurParamLineStart,
                                           CATSurParam              &       oSurParamLineEnd,
                                           CATSurParam              &       oSurParamCircleStart,
                                           CATSurParam              &       oSurParamCircleEnd,
                                           CATSurParam              &       oSurParamCircleCentre,
                                           double                   &       oCircleRadius,
                                           CATAngle                 &       oCircleStartAngle,
                                           CATAngle                 &       oCircleEndAngle,
                                           CATBoolean               &       oPlaneTorusAxisInPlane,
                                           CATBoolean               &       oPlaneSphereAxisInPlane,
                                           short                            iFrontier = -1,
                                     const CATMathVector            *       iApproxDirCurve=NULL);

// @nocgmitf
// Function to create an intersection curve (by calculating an edge-curve map, if necessary)
CATBoolean CreateIntCurveFromMap(const CATBoolean                        iVerifyLinearMapping,
                                 const CATBoolean                        iOptimiseArcs,
                                 const CATBoolean                        iPreferFirstPCurve,
                                 const CATBoolean                        iInteligentRefCurveInIntCurve,
                                 const CATTolerance              &       iTolObject,
                                 const double                            iMaxInterpError,
                                       CATPCurve                *  const iPCurve1,
                                       CATPCurve                *  const iPCurve2,
                                       CATSoftwareConfiguration *  const iConfig,
                                       CATGeoFactory            *        ioFactory,
                                       double                    &       oMaxGap,
                                       CATIntCurve              *&       oIntCurve,
                                       int                      *        oReversedPLine = NULL,
                                 const CATBoolean                        iHasInits = TRUE);

// Do not use (relies on surface current limits). Only kept because it is in CGM interface
short TransformAngleToWithinConeRange(      CATSoftwareConfiguration * iConfig, 
                                      const CATTolerance             & iTol,
                                      const CATCone                  * iCone,
                                            CATAngle                 & ioAngle);

// Do not use (relies on surface current limits). Only kept because it is in CGM interface
short TransformAngleToWithinSphereRange(      CATSoftwareConfiguration * iConfig,
                                        const CATTolerance             & iTol,
                                        const CATSphere                * iSphere,
                                              CATAngle                 & ioAngle);

// @nocgmitf
short TransformAngleToWithinConeRange(      CATSoftwareConfiguration * iConfig, 
                                      const CATTolerance             & iTol,
                                      const CATCone                  * iCone,
                                      const CATSurLimits             & iLimits,
                                            CATAngle                 & ioAngle);

// @nocgmitf
short TransformAngleToWithinSphereRange(      CATSoftwareConfiguration * iConfig,
                                        const CATTolerance             & iTol,
                                        const CATSphere                * iSphere,
                                        const CATSurLimits             & iLimits,
                                              CATAngle                 & ioAngle);

// @nocgmitf
short TransformAngleToWithinRange(      CATSoftwareConfiguration * iConfig, 
                                  const CATTolerance             & iTol,
                                  const CATSurface               * iSurface,
                                  const CATSurLimits             & iLimits,
                                        CATAngle                 & ioAngle);

CATBoolean TransformAngleToWithinRange(      CATSoftwareConfiguration * iConfig,
                                       const CATTolerance             & iTol,
                                       const CATAngle                   iMinAngle,
                                       const CATAngle                   iMaxAngle,
                                             CATAngle                 & ioAngle);

#endif
