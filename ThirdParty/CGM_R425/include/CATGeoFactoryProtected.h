#ifndef CATGeoFactoryProtected_H
#define CATGeoFactoryProtected_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1996
//
// DESCRIPTION : CATGeoFactoryProtected (anciennement CATGeoFactoryImpl) class declaration
//
//=============================================================================
// Dec.  03 HCN Suppression CATIAV5R11, CATIAV5R12
// July  04 RAQ Ajout CreateSubdivMesh
// Jan.  05 HCN Suppression CATIAV5R13 et CATIAV5R14
// Jul.  05 HCN Modifications pour suppression des methodes nodoc de l'interface
//              CATGeoFactory :
//              - Renommage de CATGeoFactoryImpl en CATGeoFactoryProtected
//              - Rajout des methodes manquantes presentes dans CATGeoFactory
//              - Tri des methodes
//              - GetProtectedInterface()
// May.  06 FDN Ajout de GetOldestElementBasic(...)
// Mar.  07 SOU Chordal fillet surface
// Jan.  08 RNO Ajout de CreateSubdivCellSurface
// 31/01/08 NLD Ajout SetScaleOption(),GetScaleOption() et SetScaleOptionBasic(),GetScaleOptionBasic() 
// Aout. 09 TCX Modularisation sur base CATGeoMeshFactory
// Oct.  09 DNR Suppression du #ifdef  relatif aux CATCldVectors
// Oct.  09 RAQ Ajout CreateSubdivMesh(CATSubdivMeshGeo*)
// 20120731 AAD Suppression SetScale
// Nov.  14 DPS Add the polyhedral factory in order to instanciate polyhedral bodies 
//              in the CGM Container
// 23/04/19 NLD Mise au propre compl�te
//              - detabulation
//              - smart indent
// 04/12/19 SMT1 Added Deformation flags for Create(Generic)Fillet
// 15/09/21 DPS Remove deprecated CreateGeoPolyPoint/CreateGeoPolyCurve/CreateGeoPolySurface/CreateGeoPolyBody
//=============================================================================

#include "CATIACGMLevel.h"
#include "CATBaseUnknown.h"
#include "CATMathDef.h"
#include "CATMathInline.h"
#include "CATGeoFactory.h"
#include "CATCGMScaleCategoryDef.h"

#include "YP00IMPL.h"

#include "CATRootContainerCGM.h"
#include "CATGeoFactoryCGM_Macro.h"

#include "CATParameterizationOption.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATPoints.h"
#include "CATListOfCATCrvParams.h"
 
class CATGeometry;
class CATPoint;
class CATCartesianPoint;
class CATLine;
class CATCircle;
class CATEllipse;
class CATParabola;
class CATHyperbola;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATPlane;
class CATPLine;
class CATPNurbs;
class CATPSpline;
class CATBezierCurve;
class CATNurbsCurve;
class CATSplineCurve;
class CATHelix;
class CATPointOnSurface;
class CATNurbsSurface;
class CATRuledSurface;
class CATGenericRuledSurface;
class CATOrientable;
class CATCurve;
class CATSurface;
class CATSphere;
class CATCylinder;
class CATCone;
class CATTorus;
class CATTabulatedCylinder;
class CATRevolutionSurface;
class CATProcOffsetSurface;
class CATOffsetSurface;
class CATCircularSweep;
class CATGenericFillet;
class CATSweepSurface;
class CATFilletSurface;
class CATDraftSurface;
class CATDraftSurfaceCreationData;
class CATDirectionalSurface;
class CATChamferSurface;
class CATSpecSurface;
class CATSpecSurfaceDef;
class CATProcSurface;
class CATProcSurfaceDef;
class CATLinearTransfoSurface;
class CATNonLinearTransfoSurface;
class CATNonLinearTransfoPCurve;
class CATMathNonLinearTransformation2D;
class CATIForeignSurface;
class CATForeignSurfaceData;
class CATIForeignCurve;
class CATForeignCurveData;
class CATIForeignPCurve;
class CATForeignPCurveData;
class CATPCurve;
class CATPCircle;
class CATPEllipse;
class CATPCurveEquation;
class CATMacroPoint;
class CATIntCurve;
class CATMergedCurve;
class CATSimCurve;
class CATContactCurve;
class CATProcCurve;
class CATProcCurveDef;
class CATTrimmedPCurve;
class CATMapX;
class CATSweepSegmentSurface;
class CATSweepSegmentSurfaceCreationData;

class CATMathPoint;
class CATMathPoint2D;
class CATMathVector;
class CATMathLine2D;
class CATMathDirection;
class CATMathPlane;
class CATMathLine;
class CATMathAxis;
class CATMathBox2D;
class CATMathFunctionX;
class CATMathNonLinearTransformation;
class CATCrvParam;
class CATSurParam;
class CATCrvLimits;
class CATMathSetOfPoints;
class CATMathGridOfPoints;
class CATKnotVector;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDWithVectors;
class CATGeoFactory;
class CATBody;

class CATCldGenEntity;
class CATCldBody;
class CATCldCloud;
class CATCldScan;
class CATCldGrid;
class CATCldPolygon;
class CATCldVectors;
class CATCldSetOfScans;
class CATCldSetOfGrids;
class CATCldScanOnPolygon;
class CATCldSubPolygon;
class CATCldSetOfPoints;
class CATCldSetOfPointsF;
class CATCldSetOfPointsD;

class CATICGMObject;
class CATICGMUnknown;

class CATConstantLaw;
class CATLinearLaw;
class CATSTypeLaw;
class CATSplineLaw;
class CATCompositeLaw;
class CATSobMesh;
class CATSubdivMesh;

class CATSubdivCellSurface;
class CATSubdivGridSurface;
class CATSobFace;
class CATSubdivMeshGeo;

class CATGeoPolyPoint;
class CATIPolyPoint;
class CATGeoPolyCurve;
class CATIPolyCurve;
class CATGeoPolySurface;
class CATIPolySurface;
class CATGeoPolyBody;
class CATPolyBody;

class CATClay;
class CATTessClay;
class CATCloud;
class CATTessCloud;
class CATScan;
class CATTessScan;

class CATCGMJournalList;
class CATCGMInternalTol;

class CATTolerance;

class CATGeoFactoryProtected;
class CATGeoMeshFactory;
class CATGeoPolyFactory;

class CATGeoImplicitFactory;

class CATGeometry;
class CATUserGeometry;
 


class ExportedByYP00IMPL CATGeoFactoryProtected : public CATBaseUnknown
{
public:


  //---------------------------------------------------------------------------
  // Compare geometry ages : The two elements MUST be in the same factory
  // Answer is the number (1 or 2) of the oldest elem, or 0 if they are the same
  //           or -1 if the answer is impossible (this case CAN occur !!!!!!)
  //---------------------------------------------------------------------------

          int                GetOldestElem      (CATGeometry * iGeo1, CATGeometry * iGeo2);
  virtual int                GetOldestElemBasic (CATGeometry * iGeo1, CATGeometry * iGeo2);

  //---------------------------------------------------------------------------
  // Body creation
  //---------------------------------------------------------------------------
  virtual CATBody          * CreateBody(      CATBodyMode  iMode        = CatBodyMode_Working ,
                                        const char         iRole[]      = "Unknown",
                                        const char        *iTracability = __FILE__ ,
                                        const int          iLine        = __LINE__ ) = 0 ; 

  //---------------------------------------------------------------------------
  // GetGeoMeshFactory
  //---------------------------------------------------------------------------

  virtual CATGeoMeshFactory* GetGeoMeshFactory() = 0;


  //---------------------------------------------------------------------------
  // GetGeoPolyFactory
  //---------------------------------------------------------------------------

  virtual CATGeoPolyFactory* GetGeoPolyFactory(CATBoolean iCreationMode=FALSE) = 0;

  //---------------------------------------------------------------------------
  // Cartesian Point creation
  //---------------------------------------------------------------------------

          CATCartesianPoint* CreateCartesianPoint     (const CATLength     x,
                                                       const CATLength     y,
                                                       const CATLength     z);
  
          CATCartesianPoint* CreateCartesianPoint     (const CATMathPoint& iCoord);
  
  // Pour compatibilite ascendante, a supprimer.
#ifndef CATCGMRemoveNoDocDrop7
          CATCartesianPoint* CreateCartesianPoint     ();
#endif // CATCGMRemoveNoDocDrop7Drop2
    
  virtual CATCartesianPoint* CreateCartesianPointBasic(const CATLength x,
                                                       const CATLength y,
                                                       const CATLength z) = 0;
  

  //---------------------------------------------------------------------------
  // Point On Curve creation
  //---------------------------------------------------------------------------

          CATPointOnCurve* CreatePointOnCurve     (const CATCrvParam& parameter,
                                                         CATCurve*    curve    );
  
  virtual CATPointOnCurve* CreatePointOnCurveBasic(const CATCrvParam& parameter,
                                                         CATCurve*    curve    ) = 0;
  
  
  //---------------------------------------------------------------------------
  // Point On EdgeCurve creation
  //---------------------------------------------------------------------------

          CATPointOnEdgeCurve* CreatePointOnEdgeCurve     (const CATCurve*     iSpecCurve,
                                                           const CATCrvParam&  iSpecParam,
                                                           const CATEdgeCurve* iSupport);
  
          CATPointOnEdgeCurve* CreatePointOnEdgeCurve     (const CATCurve*     iSpecCurve1,
                                                           const CATCrvParam&  iSpecParam1,
                                                           const CATCurve*     iSpecCurve2,
                                                           const CATCrvParam&  iSpecParam2,
                                                           const CATEdgeCurve* iSupport);
  
          CATPointOnEdgeCurve* CreatePointOnEdgeCurve     (const CATLONG32     iSpecCount, 
                                                           const CATCurve*     iSpecCurves[],
                                                           const CATCrvParam   iSpecParams[],
                                                           const CATEdgeCurve* iSupport);
  
          CATPointOnEdgeCurve* CreatePointOnEdgeCurve     (const CATPointOnCurve* iPointOnACurveInEdgeCurve, 
                                                           const CATEdgeCurve*    iSupport);
  
  virtual CATPointOnEdgeCurve* CreatePointOnEdgeCurveBasic(const CATLONG32     iSpecCount, 
                                                           const CATCurve*     iSpecCurves[],
                                                           const CATCrvParam   iSpecParams[],
                                                           const CATEdgeCurve* iSupport) = 0;
  

  //---------------------------------------------------------------------------
  // Point On Surface creation
  //---------------------------------------------------------------------------

          CATPointOnSurface* CreatePointOnSurface(const CATSurParam& parameter,
                                                        CATSurface*  surface);
  
          CATPointOnSurface* CreatePointOnSurface(const CATMathPoint2D& iCoord);
  
  virtual CATPointOnSurface* CreatePointOnSurfaceBasic(const CATSurParam& parameter,
                                                             CATSurface*  surface) = 0;
  

  //---------------------------------------------------------------------------
  // MacroPoint creation
  //---------------------------------------------------------------------------

          CATMacroPoint* CreateMacroPoint     (CATLISTP(CATPoint)& iPoints);
  
          CATMacroPoint* CreateMacroPoint     ();
  
  virtual CATMacroPoint* CreateMacroPointBasic() = 0;


  //---------------------------------------------------------------------------
  // Line creation
  //---------------------------------------------------------------------------

          CATLine* CreateLine     (const CATMathPoint    & pointm,
                                   const CATMathDirection& directionm);
  
          CATLine* CreateLine     (const CATMathPoint    & iStart,
                                   const CATMathPoint    & iEnd,
                                         CATCrvLimits    & oLimits);
  
          CATLine* CreateLine     (const CATPoint        * iStart,
                                   const CATPoint        * iEnd,
                                         CATCrvLimits    & oLimits);
  
          CATLine* CreateLine     (const CATPoint        * iStart,
                                   const CATPoint        * iEnd);
  
          CATLine* CreateLine     (const CATMathPoint    & iStart,
                                   const CATMathPoint    & iEnd); 
  
  virtual CATLine* CreateLineBasic(const CATMathPoint    & pointm,
                                   const CATMathDirection& directionm) = 0;
  
  virtual CATLine* CreateLineBasic(const CATMathPoint    & point1,
                                   const CATMathPoint    & point2) = 0;


  //---------------------------------------------------------------------------
  // Circle creation
  //---------------------------------------------------------------------------

          CATCircle* CreateCircle     (const CATPositiveLength iRadius,
                                       const CATMathPlane&     iAxis2m);
  
          CATCircle* CreateCircle     (const CATPositiveLength iRadius,
                                       const CATMathPlane&     iAxis2m,
                                       const CATAngle          iFrom, 
                                       const CATAngle          iTo);
  
          CATCircle* CreateCircle    (const CATMathSetOfPoints* Points, 
                                             CATCrvLimits&       Box);
  
  
          CATCircle* CreateCircle     (const CATPositiveLength iRadius);
  
  virtual CATCircle* CreateCircleBasic(const CATPositiveLength iRadius,
                                       const CATMathPlane&     iAxis2m,
                                       const CATAngle          iFrom, 
                                       const CATAngle          iTo) = 0;


  //---------------------------------------------------------------------------
  // Ellipse creation
  //---------------------------------------------------------------------------

          CATEllipse* CreateEllipse(const CATPositiveLength iMajorAxis,
                                    const CATPositiveLength iMinorAxis,
                                    const CATMathPlane&     iAxis2m, 
                                    const CATAngle          iFrom,
                                    const CATAngle          iTo);
  
          CATEllipse* CreateEllipse(const CATPositiveLength iMajorAxis,
                                    const CATPositiveLength iMinorAxis,
                                    const CATMathPlane&     iAxis2m);
  
 
  // Ellipse creation on the default XY plane
          CATEllipse* CreateEllipse(const CATPositiveLength iMajorAxis,
                                    const CATPositiveLength iMinorAxis);
 
  
          CATEllipse* CreateEllipse(CATEllipse* ToCopy);

  virtual CATEllipse* CreateEllipseBasic(const CATPositiveLength iMajorAxis,
                                         const CATPositiveLength iMinorAxis,
                                         const CATMathPlane&     iAxis2m, 
                                         const CATAngle          iFrom,
                                         const CATAngle          iTo) = 0;

#ifndef CATCGMRemoveNoDocDrop7
  //---------------------------------------------------------------------------
  // Bezier Curve creation
  //---------------------------------------------------------------------------

#ifndef PLATEFORME_DS64

          CATBezierCurve* CreateBezierCurve(const int&          iNbrCtrlPts,
                                            const int&          iNbrOfArc,
                                            const int*          iDegrees,
                                            const CATMathPoint* MathCtrlPts);

#endif //PLATEFORME_DS64

          CATBezierCurve* CreateBezierCurve(const CATLONG32     iNbrOfPts,
                                            const CATLONG32     iNbrOfArcs, 
                                            const CATLONG32*    iArcsDegree,
                                            const CATMathPoint* iCtrlPts);
  

  // One arc bezier curve creation
          CATBezierCurve* CreateBezierCurve(const CATLONG32     iNbrOfPts, 
                                            const CATLONG32     iArcDegree,
                                            const CATMathPoint* iCtrlPts);
  
          CATBezierCurve* CreateBezierCurve(const CATLONG32     iNbrOfPts, 
                                            const CATMathPoint* iCtrlPts);
  

          CATBezierCurve* CreateBezierCurve(const CATMathSetOfPoints* SetOfPoints,
                                            const CATLONG32&          iNbrOfArcs, 
                                            const CATLONG32*          iArcsDegree);
  
          CATBezierCurve* CreateBezierCurve(const CATMathSetOfPoints* SetOfPoints,
                                            const CATLONG32&          iArcDegree);
  
          CATBezierCurve* CreateBezierCurve(const CATMathSetOfPoints* SetOfPoints);
 #endif //CATCGMRemoveNoDocDrop7
  
          CATBezierCurve* CreateBezierCurve(CATBezierCurve* ToCopy);
  
  virtual CATBezierCurve* CreateBezierCurveBasic(const int&          iNbrCtrlPts,
                                                 const int&          iNbrOfArc,
                                                 const int*          iDegrees,
                                                 const CATMathPoint* MathCtrlPts) = 0;


  //---------------------------------------------------------------------------
  // Nurbs Curve creation
  //---------------------------------------------------------------------------

  //CATCreate: check continuity of geometric element(at least C2 else error). Create: No check
          CATNurbsCurve* CATCreateNurbsCurve  (const CATKnotVector&            iKnotVector             ,
                                               const CATLONG32&                iIsRational             ,
                                               const CATMathSetOfPoints&       iVertices               ,
                                               const double*                   iWeights                ,
                                               const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization);

          CATNurbsCurve* CreateNurbsCurve     (const CATKnotVector&            iKnotVector             ,
                                               const CATLONG32&                iIsRational             ,
                                               const CATMathSetOfPoints&       iVertices               ,
                                               const double*                   iWeights                ,
                                               const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization);
  
  virtual CATNurbsCurve* CreateNurbsCurveBasic(const CATKnotVector&            iKnotVector             ,
                                               const CATLONG32&                iIsRational             ,
                                               const CATMathSetOfPoints&       iVertices               ,
                                               const double*                   iWeights                ,
                                               const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization,
                                               int                             iCheckLevel             = 0) = 0;


  //---------------------------------------------------------------------------
  // Spline Curve creation
  //---------------------------------------------------------------------------

          CATSplineCurve* CreateSplineCurve(const CATMathSetOfPointsND* iPoints,
                                    const CATLONG32&            nvar0,
                                    const CATLONG32&            nvar1,
                                    const CATLONG32&            nvar2,
                                    const double*               iParameters);
  
          CATSplineCurve* CreateSplineCurve(const CATMathSetOfPointsNDWithVectors* iPoints,
                                            const double*                          iParameters);
  
          CATSplineCurve* CreateSplineCurve(const CATMathSetOfPointsND* iParams,
                                            const CATMathSetOfPointsND* iPoints,
                                            const CATMathSetOfPointsND* iTangents,
                                            const CATMathSetOfPointsND* iSecondDerivatives,
                                            const CATLONG32             iFirstCoordIndex,
                                            const CATLONG32             iSecondCoordIndex,
                                            const CATLONG32             iThirdCoordIndex);
  
  virtual CATSplineCurve* CreateSplineCurveBasic(const CATMathSetOfPointsNDWithVectors* iPoints,
                                                 const double*                          iParameters) = 0;
  
  virtual CATSplineCurve* CreateSplineCurveBasic(const CATMathSetOfPointsND* iParams,
                                                 const CATMathSetOfPointsND* iPoints,
                                                 const CATMathSetOfPointsND* iTangents,
                                                 const CATMathSetOfPointsND* iSecondDerivatives,
                                                 const CATLONG32             iFirstCoordIndex,
                                                 const CATLONG32             iSecondCoordIndex,
                                                 const CATLONG32             iThirdCoordIndex) = 0;


  //---------------------------------------------------------------------------
  // Parabola creation
  //---------------------------------------------------------------------------

          CATParabola* CreateParabola     (const CATLength&    iFocalDistance,
                                           const CATMathPlane& iBackgroundPlane);
  
          CATParabola* CreateParabola     (      CATParabola * ToCopy);
  
  virtual CATParabola* CreateParabolaBasic(const CATLength&    iFocalDistance,
                                           const CATMathPlane& iBackgroundPlane) = 0;
  

  //---------------------------------------------------------------------------
  // Hyperbola creation
  //---------------------------------------------------------------------------

          CATHyperbola* CreateHyperbola(const CATPositiveLength& majaxis,
                                        const CATPositiveLength& minaxis,
                                        const CATMathPlane&      axis2m);
  
  virtual CATHyperbola* CreateHyperbolaBasic(const CATPositiveLength& majaxis,
                                             const CATPositiveLength& minaxis,
                                             const CATMathPlane&      axis2m) = 0;


  //---------------------------------------------------------------------------
  // Helix creation
  //---------------------------------------------------------------------------

  virtual CATHelix* CreateHelix     (const CATMathLine&  iAxis,
                                     const CATMathPoint& iStartingPoint,
                                     const CATAngle      iStart,
                                     const CATAngle      iEnd,
                                     const double        iPitch,
                                     const CATLONG32     iTrigonometricOrientation,
                                           double        iRadiusEvolution = 0.);
  
  virtual CATHelix* CreateHelixBasic(const CATMathLine&  iAxis,
                                     const CATMathPoint& iStartingPoint,
                                     const CATAngle      iStart,
                                     const CATAngle      iEnd,
                                     const double        iPitch,
                                     const CATLONG32     iTrigonometricOrientation,
                                           double        iRadiusEvolution = 0.) = 0;


  //---------------------------------------------------------------------------
  // PLine creation
  //---------------------------------------------------------------------------

          CATPLine* CreatePLine(const CATSurParam& iStart, 
                                const CATSurParam& iEnd, 
                                      CATSurface * iSupport);
  
          CATPLine* CreatePLine(const CATMathPoint2D& iStart, 
                                const CATMathPoint2D& iEnd);
  
          CATPLine* CreatePLine(const CATMathLine2D& iCoord);
  
  // Pour compatibilite ascendante, a supprimer.
          CATPLine* CreatePLine(      CATSurface * iSupport, 
                                const CATSurParam& iStart, 
                                const CATSurParam& iEnd);
  
  virtual CATPLine* CreatePLineBasic(      CATSurface * iSupport, 
                                     const CATSurParam& iStart, 
                                     const CATSurParam& iEnd) = 0;


  //---------------------------------------------------------------------------
  // PCircle creation
  //---------------------------------------------------------------------------

          CATPCircle* CreatePCircle(const double       iRadius,
                                    const CATSurParam& iCenter,
                                    const CATAngle     iFrom,
                                    const CATAngle     iTo,
                                          CATSurface*  iSupport);
  
          CATPCircle* CreatePCircle(const double       iRadius,
                                    const CATSurParam& iCenter,
                                          CATSurface*        iSupport);
  
          CATPCircle* CreatePCircle(const CATSurParam& iPoint1,
                                    const CATSurParam& iPoint2,
                                    const CATSurParam& iPoint3,
                                          CATSurface * iSupport);
  
          CATPCircle* CreatePCircle(const CATPositiveLength iRadius,
                                    const CATMathPoint2D&   iCenter,
                                    const CATAngle          iFrom,
                                    const CATAngle          iTo);
  
          CATPCircle* CreatePCircle(const CATMathPoint2D& iPoint1, 
                                    const CATMathPoint2D& iPoint2, 
                                    const CATMathPoint2D& iPoint3);
  
  virtual CATPCircle* CreatePCircleBasic(const double       iRadius,
                                         const CATSurParam& iCenter,
                                         const CATAngle     iFrom,
                                         const CATAngle     iTo,
                                               CATSurface*  iSupport) = 0;


  //---------------------------------------------------------------------------
  // PEllipse creation
  //---------------------------------------------------------------------------

          CATPEllipse* CreatePEllipse(const double&      iMajorAxis,
                                      const double&      iMinorAxis,
                                      const double&      iOffsetAngle,
                                      const CATSurParam& iCenter,
                                      const CATAngle     iFrom,
                                      const CATAngle     iTo,
                                            CATSurface*        iSupport);
  
          CATPEllipse* CreatePEllipse(const double&      iMajorAxis,
                                      const double&      iMinorAxis,
                                      const double&      iOffsetAngle,
                                      const CATSurParam& iCenter,
                                            CATSurface*        iSupport);
  
          CATPEllipse* CreatePEllipse(const CATMathAxis2D& iAxis,
                                      const double&        iMajorAxis,
                                      const double&        iMinorAxis,
                                      const CATAngle       iStart,
                                      const CATAngle       iEnd,
                                            CATSurface*          iSupport);
  
          CATPEllipse* CreatePEllipse(const CATMathAxis2D& iAxis,
                                      const double&        iMajorAxis,
                                      const double&        iMinorAxis,
                                            CATSurface*          iSupport);
  
  virtual CATPEllipse* CreatePEllipseBasic(const double&      iMajorAxis,
                                           const double&      iMinorAxis,
                                           const double&      iOffsetAngle,
                                           const CATSurParam& iCenter,
                                           const CATAngle     iFrom,
                                           const CATAngle     iTo,
                                                 CATSurface*        iSupport) = 0;


  //---------------------------------------------------------------------------
  // PParabola creation
  //---------------------------------------------------------------------------
  
          CATPParabola* CreatePParabola(const CATMathAxis2D& iAxis,
                                        const double         ip,
                                        const double         iStart,
                                        const double         iEnd,
                                              CATSurface*    iSupport);

          CATPParabola* CreatePParabola(const CATMathAxis2D& iAxis,
                                        const double         ip,
                                              CATSurface*    iSupport);
  
  virtual CATPParabola* CreatePParabolaBasic(const CATMathAxis2D& iAxis,
                                             const double         ip,
                                             const double*        Limits,
                                                   CATSurface*    iSupport) = 0;


  //---------------------------------------------------------------------------
  // PHyperbola creation
  //---------------------------------------------------------------------------
  
          CATPHyperbola* CreatePHyperbola(const CATMathAxis2D& iAxis,
                                          const double         iA,
                                          const double         iB,
                                          const double         iStart,
                                          const double         iEnd,
                                                CATSurface   * iSupport);
  
          CATPHyperbola* CreatePHyperbola(const CATMathAxis2D& iAxis,
                                          const double         iA,
                                          const double         iB,
                                                CATSurface   * iSupport);
  
  virtual CATPHyperbola* CreatePHyperbolaBasic(const CATMathAxis2D& iAxis,
                                               const double         iA,
                                               const double         iB,
                                               const double       * Limits,
                                                     CATSurface   * iSupport) = 0;


  //---------------------------------------------------------------------------
  // PNurbs creation     
  //---------------------------------------------------------------------------

  //CATCreate: check continuity of geometric element(at least C2 else error). Create: No check
          CATPNurbs* CATCreatePNurbs(        CATKnotVector&            iKnotVector,
                                       const CATLONG32&                iIsRational, 
                                       const double*                   iVertices,
                                       const double*                   iWeights,
                                             CATSurface*               iSupport,
                                       const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization);

          CATPNurbs* CreatePNurbs     (      CATKnotVector&            iKnotVector,
                                       const CATLONG32&                iIsRational, 
                                       const double*                   iVertices,
                                       const double*                   iWeights,
                                             CATSurface*               iSupport,
                                       const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization);
  
  virtual CATPNurbs* CreatePNurbsBasic(      CATKnotVector&            iKnotVector,
                                       const CATLONG32&                iIsRational, 
                                       const double*                   iVertices,
                                       const double*                   iWeights,
                                             CATSurface*               iSupport,
                                       const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization,
                                       int                             iCheckLevel = 0) = 0;


  //---------------------------------------------------------------------------
  // PSpline creation
  //---------------------------------------------------------------------------

          CATPSpline* CreatePSpline(const CATMathSetOfPointsND* iPoints,
                                    const CATLONG32&            nvar0,
                                    const CATLONG32&            nvar1,
                                    const double*               iParameters,
                                          CATSurface*                 iSupport);
  
          CATPSpline* CreatePSpline(const CATMathSetOfPointsND* iParams,
                                    const CATMathSetOfPointsND* iPoints,
                                    const CATMathSetOfPointsND* iTangents,
                                    const CATMathSetOfPointsND* iSecondDerivatives,
                                    const CATLONG32             iFirstCoordIndex,
                                    const CATLONG32             iSecondCoordIndex,
                                          CATSurface*           iSupport);
    
          CATPSpline* CreatePSpline(const CATMathSetOfPointsNDWithVectors* iPoints,
                                    const double*                          iParameters,
                                          CATSurface*                      iSupport);
  
  virtual CATPSpline* CreatePSplineBasic(const CATMathSetOfPointsNDWithVectors* iPoints,
                                         const double*                          iParameters,
                                               CATSurface*                      iSupport) = 0;
  
  virtual CATPSpline* CreatePSplineBasic(const CATMathSetOfPointsND* iParams,
                                         const CATMathSetOfPointsND* iPoints,
                                         const CATMathSetOfPointsND* iTangents,
                                         const CATMathSetOfPointsND* iSecondDerivatives,
                                         const CATLONG32             iFirstCoordIndex,
                                         const CATLONG32             iSecondCoordIndex,
                                               CATSurface*           iSupport) = 0;


  //---------------------------------------------------------------------------
  // Trimmed PCurve creation
  //---------------------------------------------------------------------------

  virtual CATTrimmedPCurve* CreateTrimmedPCurve     (      CATSurface  * iSupport  ,
                                                           CATPCurve   * iReference,
                                                     const CATCrvLimits& iLimits   );

  virtual CATTrimmedPCurve* CreateTrimmedPCurveBasic(      CATSurface  * iSupport  ,
                                                           CATPCurve   * iReference,
                                                     const CATCrvLimits& iLimits   ) = 0;

    
  //---------------------------------------------------------------------------
  // Plane creation
  //---------------------------------------------------------------------------

          CATPlane* CreatePlane(const CATMathPlane& Axis2M);
  
          CATPlane* CreatePlane(const CATMathPoint& PointM1,
                                const CATMathPoint& PointM2,
                                const CATMathPoint& PointM3);

  // Plane creation with its equation coefficient
          CATPlane* CreatePlane(const CATMathDirection& DirectionM,
                                const CATLength&        D);
  
          CATPlane* CreatePlane();
  
  virtual CATPlane* CreatePlaneBasic(const CATMathPlane& Axis2M) = 0;


  //---------------------------------------------------------------------------
  // Nurbs Surface creation     
  //---------------------------------------------------------------------------

  //CATCreate: check continuity of geometric element(at least C2 else error). Create: No check
          CATNurbsSurface* CATCreateNurbsSurface(const CATKnotVector&            iKnotVectorU, 
                                                 const CATKnotVector&            iKnotVectorV,
                                                 const CATLONG32&                iIsRational, 
                                                 const CATMathGridOfPoints&      iVertices,
                                                 const double*                   iWeights,
                                                 const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization);

          CATNurbsSurface* CreateNurbsSurface   (const CATKnotVector&            iKnotVectorU, 
                                                 const CATKnotVector&            iKnotVectorV,
                                                 const CATLONG32&                iIsRational, 
                                                 const CATMathGridOfPoints&      iVertices,
                                                 const double*                   iWeights,
                                                 const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization);
  
          CATNurbsSurface* CreateNurbsSurface(CATNurbsSurface* ToCopy);
  
  virtual CATNurbsSurface* CreateNurbsSurfaceBasic(const CATKnotVector&            iKnotVectorU, 
                                                   const CATKnotVector&            iKnotVectorV,
                                                   const CATLONG32&                iIsRational, 
                                                   const CATMathGridOfPoints&      iVertices,
                                                   const double*                   iWeights,
                                                   const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization,
                                                         int                       iCheckLevel = 0) = 0;


  //---------------------------------------------------------------------------
  // Sphere creation
  //---------------------------------------------------------------------------

          CATSphere* CreateSphere(const CATMathAxis&      iAxis,
                                  const CATPositiveLength iRadius,
                                  const CATAngle          iMeridianStart,
                                  const CATAngle          iMeridianEnd,
                                  const CATAngle          iParallelStart,
                                  const CATAngle          iParallelEnd);
  
          CATSphere* CreateSphere(const CATMathAxis&      iAxis,
                                  const CATPositiveLength iRadius);
  
  virtual CATSphere* CreateSphereBasic(const CATMathAxis&      iAxis, 
                                       const CATPositiveLength iRadius,
                                       const CATAngle          iMeridianStart,
                                       const CATAngle          iMeridianEnd,
                                       const CATAngle          iParallelStart,
                                       const CATAngle          iParallelEnd) = 0;


  //---------------------------------------------------------------------------
  // Cylinder creation
  //---------------------------------------------------------------------------

          CATCylinder* CreateCylinder(const CATMathAxis& iAxis,
                                      const CATLength&   iRadius,
                                      const CATLength&   iAxisStart,
                                      const CATLength&   iAxisEnd,
                                      const CATAngle&    iAngleStart,
                                      const CATAngle&    iAngleEnd);
  
  
  virtual CATCylinder* CreateCylinderBasic(const CATMathAxis& iAxis,
                                           const CATLength&   iRadius,
                                           const CATLength&   iAxisStart,
                                           const CATLength&   iAxisEnd,
                                           const CATAngle&    iAngleStart,
                                           const CATAngle&    iAngleEnd) = 0;


  //---------------------------------------------------------------------------
  // Cone creation
  //---------------------------------------------------------------------------

          CATCone* CreateCone     (const CATMathAxis& iConeAxis,
                                   const CATLength    iStartRadius,
                                   const CATAngle     iConeAngle,
                                   const CATAngle     iStartAngle,
                                   const CATAngle     iEndAngle,
                                   const CATLength    iStartRuleLength,
                                   const CATLength    iEndRuleLength);
  
  virtual CATCone* CreateConeBasic(const CATMathAxis& iConeAxis,
                                   const CATLength    iStartRadius,
                                   const CATAngle     iConeAngle,
                                   const CATAngle     iStartAngle,
                                   const CATAngle     iEndAngle,
                                   const CATLength    iStartRuleLength,
                                   const CATLength    iEndRuleLength) = 0;
  

  //---------------------------------------------------------------------------
  // Torus creation
  //---------------------------------------------------------------------------

          CATTorus* CreateTorus     (const CATMathAxis& iTorusAxis,
                                     const CATLength    iMajorRadius,
                                     const CATAngle     iMajorStartAngle,
                                     const CATAngle     iMajorEndAngle,
                                     const CATLength    iMinorRadius,
                                     const CATAngle     iMinorStartAngle,
                                     const CATAngle     iMinorEndAngle);
  
          CATTorus* CreateTorus     (const CATMathAxis& iTorusAxis,
                                           CATLength    iMajorRadius,
                                     const CATAngle     iMajorStartAngle,
                                     const CATAngle     iMajorEndAngle,
                                           CATLength    iMinorRadius,
                                     const CATBoolean   iCoreSide);

  virtual CATTorus* CreateTorusBasic(const CATMathAxis& iTorusAxis,
                                     const CATLength    iMajorRadius,
                                     const CATAngle     iMajorStartAngle,
                                     const CATAngle     iMajorEndAngle,
                                     const CATLength    iMinorRadius,
                                     const CATAngle     iMinorStartAngle,
                                     const CATAngle     iMinorEndAngle) = 0;


  //---------------------------------------------------------------------------
  // Tabulated Cylinder creation
  //---------------------------------------------------------------------------

          CATTabulatedCylinder* CreateTabulatedCylinder     (      CATCurve*         iProfile,
                                                             const CATMathDirection& iDirection,
                                                             const CATLength&        iStart,
                                                             const CATLength&        iEnd);
  
          CATTabulatedCylinder* CreateTabulatedCylinder     (      CATCurve*         iProfile,
                                                             const CATCrvLimits&     iProfileLimits,
                                                             const CATMathDirection& iDirection,
                                                             const CATLength&        iStart,
                                                             const CATLength&        iEnd,
                                                                   CATBoolean&       oIsOrientationChanged);
  
          CATTabulatedCylinder* CreateTabulatedCylinder     (      CATCurve*         iProfile,
                                                             const CATMathDirection& iDirection,
                                                             const CATLength&        iStart,
                                                             const CATLength&        iEnd,
                                                                   CATBoolean&       oIsOrientationChanged);
  
  virtual CATTabulatedCylinder* CreateTabulatedCylinderBasic(      CATCurve*         iProfile,
                                                             const CATCrvLimits&     iProfileLimits,
                                                             const CATMathDirection& iDirection,
                                                             const CATLength&        iStart,
                                                             const CATLength&        iEnd) = 0;


  //---------------------------------------------------------------------------
  // Revolution Surface creation
  //---------------------------------------------------------------------------

          CATRevolutionSurface* CreateRevolutionSurface     (      CATCurve*     iProfile,
                                                             const CATMathAxis&  iRefAxis,
                                                             const CATAngle&     iStart,
                                                             const CATAngle&     iEnd);
  
          CATRevolutionSurface* CreateRevolutionSurface     (      CATCurve*     iProfile,
                                                             const CATCrvLimits& iProfileLimits,
                                                             const CATMathAxis&  iRefAxis,
                                                             const CATAngle&     iStart,
                                                             const CATAngle&     iEnd,
                                                                   CATBoolean&   oIsOrientationChanged);
  
          CATRevolutionSurface* CreateRevolutionSurface     (      CATCurve*     iProfile,
                                                             const CATMathAxis&  iRefAxis,
                                                             const CATAngle&     iStart,
                                                             const CATAngle&     iEnd,
                                                                   CATBoolean&   oIsOrientationChanged);
  
  virtual CATRevolutionSurface* CreateRevolutionSurfaceBasic(      CATCurve*     iProfile,
                                                             const CATCrvLimits& iProfileLimits,
                                                             const CATMathAxis&  iDirectionRefAxis,
                                                             const CATAngle&     iStart,
                                                             const CATAngle&     iEnd) = 0;


  //---------------------------------------------------------------------------
  // Offset Surface creation
  //---------------------------------------------------------------------------

          CATOffsetSurface* CreateOffsetSurface(const CATLength   iOffset,
                                                      CATSurface* iReference);
  
          CATOffsetSurface* CreateOffsetSurface(const CATLength     iOffset,
                                                      CATSurface  * iReference,
                                                const CATSurLimits& iLimits);
  
  
          CATOffsetSurface* CreateOffsetSurface(const double       iOffset,
                                                      CATSurface*  iReference,
                                                      CATSurface*  iGeometricRep);

  virtual CATOffsetSurface* CreateOffsetSurfaceBasic(const CATLength   iOffset,
                                                           CATSurface* iReference,
                                                           CATSurface* iGeometricRep) = 0;

  virtual CATOffsetSurface* CreateOffsetSurfaceBasic(const CATLength     iOffset   ,
                                                           CATSurface  * iReference,
                                                     const CATSurLimits& iLimits   ) = 0;


  //---------------------------------------------------------------------------
  // Constant Law creation
  //---------------------------------------------------------------------------

          CATConstantLaw* CreateConstantLaw(const double iTMin,
                                            const double iTMax,
                                            const double iValue);
  
          CATConstantLaw* CreateConstantLaw(CATConstantLaw* ToCopy);
  
  virtual CATConstantLaw* CreateConstantLawBasic(const double iTMin,
                                                 const double iTMax,
                                                 const double iValue) = 0;


  //---------------------------------------------------------------------------
  // Linear Law creation
  //---------------------------------------------------------------------------

          CATLinearLaw* CreateLinearLaw(const double iTMin,
                                        const double iValueAtTMin,
                                        const double iTMax,
                                        const double iValueAtTMax);
  
          CATLinearLaw* CreateLinearLaw(CATLinearLaw* ToCopy);
  
  virtual CATLinearLaw* CreateLinearLawBasic(const double iTMin,
                                             const double iValueAtTMin,
                                             const double iTMax,
                                             const double iValueAtTMax) = 0;


  //---------------------------------------------------------------------------
  // Spline Law creation
  //---------------------------------------------------------------------------

          CATSplineLaw* CreateSplineLaw(const CATLONG32 iNbrOfConstraint,
                                        const double*   iT,
                                        const double*   iValue);
  
          CATSplineLaw* CreateSplineLaw(CATSplineLaw* ToCopy);
  
  virtual CATSplineLaw* CreateSplineLawBasic(const CATLONG32 iNbrOfConstraint,
                                             const double*   iT,
                                             const double*   iValue) = 0;


  //---------------------------------------------------------------------------
  // Composite Law creation
  //---------------------------------------------------------------------------

          CATCompositeLaw* CreateCompositeLaw(const CATLONG32          iNbrOfFunctions,
                                              const double*            iBorders,
                                              const CATMathFunctionX** iFunctions);
  
          CATCompositeLaw* CreateCompositeLaw(CATCompositeLaw* ToCopy);
  
  virtual CATCompositeLaw* CreateCompositeLawBasic(const CATLONG32          iNbrOfFunctions,
                                                   const double*            iBorders,
                                                   const CATMathFunctionX** iFunctions) = 0;


  //---------------------------------------------------------------------------
  // SType Law creation
  //---------------------------------------------------------------------------

          CATSTypeLaw* CreateSTypeLaw(const double    iTMin,
                                      const double    iValueAtTMin,
                                      const CATLONG32 iNullDerivOrderAtTMin,
                                      const double    iTMax,
                                      const double    iValueAtTMax,
                                      const CATLONG32 iNullDerivOrderAtTMax);
  
          CATSTypeLaw* CreateSTypeLaw(CATSTypeLaw* ToCopy);
  
  virtual CATSTypeLaw* CreateSTypeLawBasic(const double    iTMin,
                                           const double    iValueAtTMin,
                                           const CATLONG32 iNullDerivOrderAtTMin,
                                           const double    iTMax,
                                           const double    iValueAtTMax,
                                           const CATLONG32 iNullDerivOrderAtTMax) = 0;


  //---------------------------------------------------------------------------
  // C2Extrapolation Composite Law creation
  //---------------------------------------------------------------------------
  
          CATCompositeLaw* CreateC2ExtrapolationCompositeLaw(const CATLaw*   iToExtrapolate,
                                                             const double    iMinLimiteValue,
                                                             const double    iMaxLimiteValue,
                                                             const CATLONG32 iSide = 0);
  
  virtual CATCompositeLaw* CreateC2ExtrapolationCompositeLawBasic(const CATLaw*   iToExtrapolate,
                                                                  const double    iMinLimiteValue,
                                                                  const double    iMaxLimiteValue,
                                                                  const CATLONG32 iSide = 0) = 0;


  //---------------------------------------------------------------------------
  // Foreign Curve creation 
  //---------------------------------------------------------------------------

          CATIForeignCurve* CreateForeignCurve     (CATForeignCurveData* iForeignCurveData);
  
  virtual CATIForeignCurve* CreateForeignCurveBasic(CATForeignCurveData* iForeignCurveData) = 0;


  //---------------------------------------------------------------------------
  // Foreign PCurve creation 
  //---------------------------------------------------------------------------

          CATIForeignPCurve* CreateForeignPCurve     (CATForeignPCurveData* iForeignPCurveData,
                                                      CATSurface          * iSupport          );
  
  virtual CATIForeignPCurve* CreateForeignPCurveBasic(CATForeignPCurveData* iForeignPCurveData,
                                                      CATSurface          * iSupport          ) = 0;
    

  //---------------------------------------------------------------------------
  // Foreign Surface creation 
  //---------------------------------------------------------------------------

          CATIForeignSurface* CreateForeignSurface     (CATForeignSurfaceData* iForeignSurfaceData);
  
  virtual CATIForeignSurface* CreateForeignSurfaceBasic(CATForeignSurfaceData* iForeignSurfaceData) = 0;



  //---------------------------------------------------------------------------
  // PCurve Equation creation
  //---------------------------------------------------------------------------

          CATPCurveEquation* CreatePCurveEquation(const CATMathFunctionX* iFx,
                                                  const CATMathFunctionX* iFy,
                                                  const double            iStart,
                                                  const double            iEnd,
                                                  const double            iMaxStart,
                                                  const double            iMaxEnd,
                                                        CATSurface*       iSupport);
  
          CATPCurveEquation* CreatePCurveEquation(const CATMathFunctionX* iFx,
                                                  const CATMathFunctionX* iFy,
                                                  const CATCrvLimits&     TrimLim,
                                                  const CATCrvLimits&     FullLim,
                                                        CATSurface*       iSupport);
  
  virtual CATPCurveEquation* CreatePCurveEquationBasic(const CATMathFunctionX* iFx,
                                                       const CATMathFunctionX* iFy,
                                                       const double            iStart,
                                                       const double            iEnd,
                                                       const double            iMaxStart,
                                                       const double            iMaxEnd,
                                                             CATSurface*       iSupport) = 0;


  //---------------------------------------------------------------------------
  // IntCurve creation
  //---------------------------------------------------------------------------

          CATIntCurve* CreateIntCurve(      CATPCurve*        iC1    ,
                                            CATPCurve*        iC2    );
  
          CATIntCurve* CreateIntCurve(const CATLONG32         iNbMapX,
                                      const CATMapX**         iMapX  ,
                                      const CATPositiveLength iMaxGap);
  
  // CATIntCurve* CreateIntCurve(CATMapX* iMapX);
  
  // virtual CATIntCurve* CreateIntCurveBasic(CATMapX* iMapX) = 0;

  virtual CATIntCurve* CreateIntCurveBasic(CATPCurve* iC1, CATPCurve* iC2) = 0;

  virtual CATIntCurve* CreateIntCurveBasic(const CATLONG32         iNbMapX,
                                           const CATMapX**         iMapX,
                                           const CATPositiveLength iMaxGap) = 0;


  //---------------------------------------------------------------------------
  // SimCurve creation
  //---------------------------------------------------------------------------

          CATSimCurve* CreateSimCurve     (      CATLISTP(CATCurve)&     iCurves,
                                                 CATLISTP(CATCrvLimits)& iLimits,
                                                 CATListOfInt&           iOrns,
                                           const CATPositiveLength       iGap); 
  
          CATSimCurve* CreateSimCurve     (      CATLISTP(CATCurve)&     iCurves,
                                                 CATListOfInt&           iOrns,
                                           const CATPositiveLength       iGap); 
  
          CATSimCurve* CreateSimCurve     (      CATLISTP(CATCurve)&     iNewCurves,
                                           const CATPositiveLength       iGap); 
  
          CATSimCurve* CreateSimCurve     (      CATCurve*               iNewCurves); 
  
          CATSimCurve* CreateSimCurve     (const CATLONG32               iNbMapX,
                                           const CATMapX**               iMapX,
                                           const CATPositiveLength       iMaxGap);
  
  virtual CATSimCurve* CreateSimCurveBasic(      CATLISTP(CATCurve)&     iNewCurves,
                                                 CATLISTP(CATCrvLimits)& iLimits,
                                                 CATListOfInt&           iOrns,
                                           const CATPositiveLength       iGap) = 0; 

  virtual CATSimCurve* CreateSimCurveBasic(const CATLONG32         iNbMapX,
                                           const CATMapX**         iMapX,
                                           const CATPositiveLength iMaxGap) = 0;


  //---------------------------------------------------------------------------
  // MergedCurve creation
  //---------------------------------------------------------------------------

          CATMergedCurve* CreateMergedCurve     (const CATCurve*     iC1,
                                                 const CATCurve*     iC2);
  
          CATMergedCurve* CreateMergedCurve     (const CATCurve*     iC1,
                                                 const CATCrvLimits& iLim1, 
                                                 const CATCurve*     iC2,
                                                 const CATCrvLimits& iLim2); 
  
          CATMergedCurve* CreateMergedCurve     (const CATPointOnEdgeCurve* iPoecS1, 
                                                 const CATPointOnEdgeCurve* iPoecE1, 
                                                 const CATPointOnEdgeCurve* iPoecS2, 
                                                 const CATPointOnEdgeCurve* iPoecE2);
  
          CATMergedCurve* CreateMergedCurve     (const CATPointOnEdgeCurve* iPoecS1, 
                                                 const CATPointOnEdgeCurve* iPoecE1, 
                                                 const CATCurve*            iC2,
                                                 const CATCrvLimits&        iLim2);
  
          CATMergedCurve* CreateMergedCurve     (const CATCurve*             iC1,
                                                 const CATCrvLimits&         iLim1, 
                                                 const CATCurve*             iC2,
                                                 const CATCrvLimits&         iLim2, 
                                                 const CATMathSetOfPointsND& iParamMapping,
                                                 const CATPositiveLength     iMaxGap);
  
          CATMergedCurve* CreateMergedCurve     (const CATPointOnEdgeCurve*  iPoecS1, 
                                                 const CATPointOnEdgeCurve*  iPoecE1, 
                                                 const CATPointOnEdgeCurve*  iPoecS2, 
                                                 const CATPointOnEdgeCurve*  iPoecE2,
                                                 const CATMathSetOfPointsND& iParamMapping,
                                                 const CATPositiveLength     iMaxGap); 
  
          CATMergedCurve* CreateMergedCurve     (const CATLONG32         iNbMapX,
                                                 const CATMapX**         iMapX,
                                                 const CATPositiveLength iMaxGap);
  
  virtual CATMergedCurve* CreateMergedCurveBasic(const CATCurve*             iC1,
                                                 const CATCrvLimits&         iLim1, 
                                                 const CATCurve*             iC2,
                                                 const CATCrvLimits&         iLim2, 
                                                 const CATMathSetOfPointsND& iParamMapping,
                                                 const CATPositiveLength     iMaxGap) = 0; 
  
  virtual CATMergedCurve* CreateMergedCurveBasic(const CATCurve*     iC1,
                                                 const CATCrvLimits& iLim1, 
                                                 const CATCurve*     iC2,
                                                 const CATCrvLimits& iLim2) = 0; 
  
  virtual CATMergedCurve* CreateMergedCurveBasic(const CATLONG32         iNbMapX,
                                                 const CATMapX**         iMapX,
                                                 const CATPositiveLength iMaxGap) = 0;


  //---------------------------------------------------------------------------
  // ContactCurve creation
  //---------------------------------------------------------------------------

          CATContactCurve* CreateContactCurve     (CATEdgeCurve* iEdgeCurve,
                                                   CATSurface*   iSurface);
  
  virtual CATContactCurve* CreateContactCurveBasic(CATEdgeCurve* iEdgeCurve,
                                                   CATSurface*   iSurface) = 0;


  //---------------------------------------------------------------------------
  // ProcCurve creation
  //---------------------------------------------------------------------------

          CATProcCurve* CreateProcCurve     (CATProcCurveDef* iProcCurveDef);
  
  virtual CATProcCurve* CreateProcCurveBasic(CATProcCurveDef* iProcCurveDef) = 0;


  //---------------------------------------------------------------------------
  // Ruled Surface creation
  //---------------------------------------------------------------------------

          CATRuledSurface* CreateRuledSurface(const CATCurve*              profile,
                                              const CATMathDirection&      direction,
                                              const CATAngle&              angle,
                                              const double&                length1,
                                              const double&                length2,
                                              const CATCrvLimits*          limits = 0,
                                              const CATLISTP(CATCrvParam)* params = 0);
  
  virtual CATRuledSurface* CreateRuledSurfaceBasic(const CATCurve*              profile,
                                                   const CATMathDirection&      direction,
                                                   const CATAngle&              angle,
                                                   const double&                length1,
                                                   const double&                length2,
                                                   const CATCrvLimits*          limits = 0,
                                                   const CATLISTP(CATCrvParam)* params = 0) = 0;
  
  virtual CATRuledSurface* CreateRuledSurfaceBasic(const CATCurve* profile1,
                                                   const double&   length1,
                                                   const double&   limit1,
                                                   const CATCurve* profile2,
                                                   const double&   length2,
                                                   const double&   limit2) = 0;


  //---------------------------------------------------------------------------
  // Generic Ruled Surface creation
  //---------------------------------------------------------------------------

          CATGenericRuledSurface* CreateGenericRuledSurface     (const CATMathSetOfPointsND* iParams,
                                                                 const CATMathSetOfPointsND* iPoints,
                                                                 const CATMathSetOfPointsND* iTangents,
                                                                 const CATMathSetOfPointsND* iSecondDerivatives,
                                                                 const CATLONG32             iFirstTraceIndex,
                                                                 const CATLONG32             iSecondTraceIndex);
  
  virtual CATGenericRuledSurface* CreateGenericRuledSurfaceBasic(const CATMathSetOfPointsND* iParams,
                                                                 const CATMathSetOfPointsND* iPoints,
                                                                 const CATMathSetOfPointsND* iTangents,
                                                                 const CATMathSetOfPointsND* iSecondDerivatives,
                                                                 const CATLONG32             iFirstTraceIndex,
                                                                 const CATLONG32             iSecondTraceIndex) = 0;

  
  //---------------------------------------------------------------------------
  // Offset Surface creation
  //---------------------------------------------------------------------------

          CATGeometry         * CreateOffset                (const CATLength     iOffset   ,
                                                                   CATSurface  * iReference);


  //---------------------------------------------------------------------------
  // ProcOffset Surface creation
  //---------------------------------------------------------------------------

          CATProcOffsetSurface* CreateProcOffsetSurface     (const CATLength     iOffset   ,
                                                                   CATSurface  * iReference,
                                                             const CATSurLimits& iLimits   );
  
          CATProcOffsetSurface* CreateProcOffsetSurface(           CATProcOffsetSurface* ToCopy);  
  
  virtual CATProcOffsetSurface* CreateProcOffsetSurfaceBasic(const CATLength     iOffset,
                                                                   CATSurface*   iReference,
                                                             const CATSurLimits& iLimits) = 0;


  //---------------------------------------------------------------------------
  // Circular Sweep creation 
  //---------------------------------------------------------------------------

          CATCircularSweep* CreateCircularSweep     (const CATMathSetOfPointsNDWithVectors* iPoints    ,
                                                     const double*                          iParameters);
  
  virtual CATCircularSweep* CreateCircularSweepBasic(const CATMathSetOfPointsNDWithVectors* iPoints, 
                                                     const double*                          iParameters) = 0;


  //---------------------------------------------------------------------------
  // Sweep Surface creation 
  //---------------------------------------------------------------------------
  
          CATSweepSurface* CreateSweepSurface     (CATNurbsSurface* iNurbsSurface);
  
  virtual CATSweepSurface* CreateSweepSurfaceBasic(CATNurbsSurface* iNurbsSurface) = 0;


  //---------------------------------------------------------------------------
  // Sweep Segment Surface creation 
  //---------------------------------------------------------------------------
  
          CATSweepSegmentSurface* CreateSweepSegmentSurface     (const CATSweepSegmentSurfaceCreationData* iSweepSegmentSurfaceCreationData);  
  
  virtual CATSweepSegmentSurface* CreateSweepSegmentSurfaceBasic(const CATSweepSegmentSurfaceCreationData* iSweepSegmentSurfaceCreationData) = 0;  


  //---------------------------------------------------------------------------
  // Sweep Circle Surface creation 
  //---------------------------------------------------------------------------

          CATFilletSurface* CreateSweepCircleSurface   (const CATMathSetOfPointsND* iParams,
                                                        const CATMathSetOfPointsND* iPoints,
                                                        const CATMathSetOfPointsND* iTangents,
                                                        const CATMathSetOfPointsND* iSecondDerivatives,
                                                        const CATLONG32             iFirstTraceIndex,
                                                        const CATLONG32             iSecondTraceIndex,
                                                        const CATLONG32             iCenterCurveIndex,
                                                        const CATLONG32             iAngleIndex,
                                                        const short                 iConfiguration,
                                                        double                      iRadius,
                                                        CATCurve*                   iCircleSpine,
                                                        CATGeometry*                iSupport1,
                                                        CATGeometry*                iSupport2,
                                                        int                         iOrientation1,
                                                        int                         iOrientation2,
                                                        CATGeometry*                iContact1,
                                                        CATGeometry*                iContact2,
                                                        CATLONG32&                  oCentripetalOrientation);

virtual CATFilletSurface* CreateSweepCircleSurfaceBasic(const CATMathSetOfPointsND* iParams,
                                                        const CATMathSetOfPointsND* iPoints,
                                                        const CATMathSetOfPointsND* iTangents,
                                                        const CATMathSetOfPointsND* iSecondDerivatives,
                                                        const CATLONG32             iFirstTraceIndex,
                                                        const CATLONG32             iSecondTraceIndex,
                                                        const CATLONG32             iCenterCurveIndex,
                                                        const CATLONG32             iAngleIndex,
                                                        const short                 iConfiguration,
                                                        double                      iRadius,
                                                        CATCurve*                   iCircleSpine,
                                                        CATGeometry*                iSupport1,
                                                        CATGeometry*                iSupport2,
                                                        int                         iOrientation1,
                                                        int                         iOrientation2,
                                                        CATGeometry*                iContact1,
                                                        CATGeometry*                iContact2,
                                                        CATLONG32&                  oCentripetalOrientation) = 0;


  //---------------------------------------------------------------------------
  // Generic Fillet creation 
  //---------------------------------------------------------------------------
  //SMT1 04.12.19 Nobody could quite explain the CATTIE mechanism to us.
  //It seems safest to duplicate the method: One version still has the same signature as the method in CATGeoFactory,
  // the other one has the new additional arguments (Deformation flags)
          CATGenericFillet* CreateGenericFillet     (const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const CATMathBox2D*         iBox = NULL);

           CATGenericFillet* CreateGenericFillet     (const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const CATMathBox2D*         iBox,
                                                     CATBoolean                  iDeformedStart,
                                                     CATBoolean                  iDeformedEnd);
  
  virtual CATGenericFillet* CreateGenericFilletBasic(const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const CATMathBox2D*         iBox = NULL,
                                                     CATBoolean                  iDeformedStart = FALSE,
                                                     CATBoolean                  iDeformedEnd = FALSE) = 0;


  //---------------------------------------------------------------------------
  // Fillet Surface creation 
  //---------------------------------------------------------------------------
  
  //SMT1 04.12.19 Nobody could quite explain the CATTIE mechanism to us.
  //It seems safest to duplicate the method: One version still has the same signature as the method in CATGeoFactory,
  // the other one has the new additional arguments (Deformation flags)
          CATFilletSurface* CreateFilletSurface     (const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const short                 iConfiguration,
                                                     double                      iRadius,
                                                     CATGeometry*                iSupport1,
                                                     CATGeometry*                iSupport2,
                                                     int                         iOrientation1,
                                                     int                         iOrientation2,
                                                     CATGeometry*                iContact1,
                                                     CATGeometry*                iContact2,
                                                     CATLONG32&                  oCentripetalOrientation);

          CATFilletSurface* CreateFilletSurface     (const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const short                 iConfiguration,
                                                     double                      iRadius,
                                                     CATGeometry*                iSupport1,
                                                     CATGeometry*                iSupport2,
                                                     int                         iOrientation1,
                                                     int                         iOrientation2,
                                                     CATGeometry*                iContact1,
                                                     CATGeometry*                iContact2,
                                                     CATLONG32&                  oCentripetalOrientation,
                                                     CATBoolean                  iDeformedStart,
                                                     CATBoolean                  iDeformedEnd);
  
          CATFilletSurface* CreateFilletSurface     (const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const short                 iConfiguration,
                                                     CATCurve*                   iSpine,
                                                     CATLaw*                     iRadiusLaw,
                                                     CATLaw*                     iMappingLaw,
                                                     CATGeometry*                iSupport1,
                                                     CATGeometry*                iSupport2,
                                                     int                         iOrientation1,
                                                     int                         iOrientation2,
                                                     CATGeometry*                iContact1,
                                                     CATGeometry*                iContact2,
                                                     CATLONG32&                  oCentripetalOrientation,
                                                     const CATLONG32             iContinuityMode = 0);

          CATFilletSurface* CreateFilletSurface     (      CATFilletSurface    * ToCopy); 
  
  virtual CATFilletSurface* CreateFilletSurfaceBasic(const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const short                 iConfiguration,
                                                     double                      iRadius,
                                                     CATGeometry*                iSupport1,
                                                     CATGeometry*                iSupport2,
                                                     int                         iOrientation1,
                                                     int                         iOrientation2,
                                                     CATGeometry*                iContact1,
                                                     CATGeometry*                iContact2,
                                                     CATLONG32&                  oCentripetalOrientation,
                                                     CATBoolean                  iDeformedStart = FALSE, 
                                                     CATBoolean                  iDeformedEnd   = FALSE) = 0;
  
  virtual CATFilletSurface* CreateFilletSurfaceBasic(const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const short                 iConfiguration,
                                                     CATCurve*                   iSpine,
                                                     CATLaw*                     iRadiusLaw,
                                                     CATLaw*                     iMappingLaw,
                                                     CATGeometry*                iSupport1,
                                                     CATGeometry*                iSupport2,
                                                     int                         iOrientation1,
                                                     int                         iOrientation2,
                                                     CATGeometry*                iContact1,
                                                     CATGeometry*                iContact2,
                                                     CATLONG32&                  oCentripetalOrientation,
                                                     const CATLONG32             iContinuityMode = 0) = 0;


  //---------------------------------------------------------------------------
  // TriTangent Fillet Surface creation 
  //---------------------------------------------------------------------------

  virtual CATFilletSurface* CreateTriTangentFilletSurface     (const CATMathSetOfPointsND* iParams,
                                                               const CATMathSetOfPointsND* iPoints,
                                                               const CATMathSetOfPointsND* iTangents,
                                                               const CATMathSetOfPointsND* iSecondDerivatives,
                                                               const CATLONG32             iFirstTraceIndex,
                                                               const CATLONG32             iSecondTraceIndex,
                                                               const CATLONG32             iCenterCurveIndex,
                                                               const CATLONG32             iAngleIndex,
                                                               const short                 iConfiguration,
                                                               CATGeometry*                iSupport1,
                                                               CATGeometry*                iSupport2,
                                                               CATGeometry*                iSupport3,
                                                               int                         iOrientation1,
                                                               int                         iOrientation2,
                                                               int                         iOrientation3,
                                                               CATGeometry*                iContact1,
                                                               CATGeometry*                iContact2,
                                                               CATGeometry*                iContact3,
                                                               CATLONG32&                  oCentripetalOrientation);

  virtual CATFilletSurface* CreateTriTangentFilletSurfaceBasic(const CATMathSetOfPointsND* iParams,
                                                               const CATMathSetOfPointsND* iPoints,
                                                               const CATMathSetOfPointsND* iTangents,
                                                               const CATMathSetOfPointsND* iSecondDerivatives,
                                                               const CATLONG32             iFirstTraceIndex,
                                                               const CATLONG32             iSecondTraceIndex,
                                                               const CATLONG32             iCenterCurveIndex,
                                                               const CATLONG32             iAngleIndex,
                                                               const short                 iConfiguration,
                                                               CATGeometry*                iSupport1,
                                                               CATGeometry*                iSupport2,
                                                               CATGeometry*                iSurface3,
                                                               int                         iOrientation1,
                                                               int                         iOrientation2,
                                                               int                         iOrientation3,
                                                               CATGeometry*                iContact1,
                                                               CATGeometry*                iContact2,
                                                               CATGeometry*                iContact3,
                                                               CATLONG32&                  oCentripetalOrientation) = 0;


  //---------------------------------------------------------------------------
  // BiTangent Fillet Surface creation 
  //---------------------------------------------------------------------------

virtual CATFilletSurface* CreateBiTangentCircleFilletSurfaceBasic(const CATMathSetOfPointsND* iParams,
                                                                  const CATMathSetOfPointsND* iPoints,
                                                                  const CATMathSetOfPointsND* iTangents,
                                                                  const CATMathSetOfPointsND* iSecondDerivatives,
                                                                  const CATLONG32             iFirstTraceIndex,
                                                                  const CATLONG32             iSecondTraceIndex,
                                                                  const CATLONG32             iCenterCurveIndex,
                                                                  const CATLONG32             iAngleIndex,
                                                                  const short                 iConfiguration,
                                                                  CATCurve*                   iCircleSpine,
                                                                  CATCurve*                   iRadiusSpine,
                                                                  CATLaw*                     iRadiusLaw,
                                                                  CATLaw*                     iMappingLaw,
                                                                  CATGeometry*                iSupport1,
                                                                  CATGeometry*                iSupport2,
                                                                  int                         iOrientation1,
                                                                  int                         iOrientation2,
                                                                  CATGeometry*                iContact1,
                                                                  CATGeometry*                iContact2,
                                                                  CATLONG32&                  oCentripetalOrientation) = 0; 
  
  virtual CATFilletSurface* CreateBiTangentCircleFilletSurface   (const CATMathSetOfPointsND* iParams,
                                                                  const CATMathSetOfPointsND* iPoints,
                                                                  const CATMathSetOfPointsND* iTangents,
                                                                  const CATMathSetOfPointsND* iSecondDerivatives,
                                                                  const CATLONG32             iFirstTraceIndex,
                                                                  const CATLONG32             iSecondTraceIndex,
                                                                  const CATLONG32             iCenterCurveIndex,
                                                                  const CATLONG32             iAngleIndex,
                                                                  const short                 iConfiguration,
                                                                  CATCurve*                   iCircleSpine,
                                                                  CATCurve*                   iRadiusSpine,
                                                                  CATLaw*                     iRadiusLaw,
                                                                  CATLaw*                     iMappingLaw,
                                                                  CATGeometry*                iSupport1,
                                                                  CATGeometry*                iSupport2,
                                                                  int                         iOrientation1,
                                                                  int                         iOrientation2,
                                                                  CATGeometry*                iContact1,
                                                                  CATGeometry*                iContact2,
                                                                  CATLONG32&                  oCentripetalOrientation); 
  
  //---------------------------------------------------------------------------
  // Chordal Fillet Surface creation 
  //---------------------------------------------------------------------------
  
          CATFilletSurface* CreateChordalFilletSurface( const CATMathSetOfPointsND* iParams,
                                                        const CATMathSetOfPointsND* iPoints,
                                                        const CATMathSetOfPointsND* iTangents,
                                                        const CATMathSetOfPointsND* iSecondDerivatives,
                                                        const CATLONG32             iFirstTraceIndex,
                                                        const CATLONG32             iSecondTraceIndex,
                                                        const CATLONG32             iCenterCurveIndex,
                                                        const CATLONG32             iAngleIndex,
                                                        const short                 iConfiguration,
                                                        double                      iChord,
                                                        CATGeometry*                iSupport1,
                                                        CATGeometry*                iSupport2,
                                                        int                         iOrientation1,
                                                        int                         iOrientation2,
                                                        CATGeometry*                iContact1,
                                                        CATGeometry*                iContact2,
                                                        CATLONG32&                  oCentripetalOrientation);
  
          CATFilletSurface* CreateChordalFilletSurface( const CATMathSetOfPointsND* iParams,
                                                        const CATMathSetOfPointsND* iPoints,
                                                        const CATMathSetOfPointsND* iTangents,
                                                        const CATMathSetOfPointsND* iSecondDerivatives,
                                                        const CATLONG32             iFirstTraceIndex,
                                                        const CATLONG32             iSecondTraceIndex,
                                                        const CATLONG32             iCenterCurveIndex,
                                                        const CATLONG32             iAngleIndex,
                                                        const short                 iConfiguration,
                                                        CATCurve*                   iSpine,
                                                        CATLaw*                     iChordLaw,
                                                        CATLaw*                     iMappingLaw,
                                                        CATGeometry*                iSupport1,
                                                        CATGeometry*                iSupport2,
                                                        int                         iOrientation1,
                                                        int                         iOrientation2,
                                                        CATGeometry*                iContact1,
                                                        CATGeometry*                iContact2,
                                                        CATLONG32&                  oCentripetalOrientation,
                                                        const CATLONG32             iContinuityMode = 0);
  
  virtual CATFilletSurface* CreateChordalFilletSurfaceBasic( const CATMathSetOfPointsND* iParams,
                                                             const CATMathSetOfPointsND* iPoints,
                                                             const CATMathSetOfPointsND* iTangents,
                                                             const CATMathSetOfPointsND* iSecondDerivatives,
                                                             const CATLONG32             iFirstTraceIndex,
                                                             const CATLONG32             iSecondTraceIndex,
                                                             const CATLONG32             iCenterCurveIndex,
                                                             const CATLONG32             iAngleIndex,
                                                             const short                 iConfiguration,
                                                             double                      iChord,
                                                             CATGeometry*                iSupport1,
                                                             CATGeometry*                iSupport2,
                                                             int                         iOrientation1,
                                                             int                         iOrientation2,
                                                             CATGeometry*                iContact1,
                                                             CATGeometry*                iContact2,
                                                             CATLONG32&                  oCentripetalOrientation) = 0;
  
  virtual CATFilletSurface* CreateChordalFilletSurfaceBasic( const CATMathSetOfPointsND* iParams,
                                                             const CATMathSetOfPointsND* iPoints,
                                                             const CATMathSetOfPointsND* iTangents,
                                                             const CATMathSetOfPointsND* iSecondDerivatives,
                                                             const CATLONG32             iFirstTraceIndex,
                                                             const CATLONG32             iSecondTraceIndex,
                                                             const CATLONG32             iCenterCurveIndex,
                                                             const CATLONG32             iAngleIndex,
                                                             const short                 iConfiguration,
                                                             CATCurve*                   iSpine,
                                                             CATLaw*                     iChordLaw,
                                                             CATLaw*                     iMappingLaw,
                                                             CATGeometry*                iSupport1,
                                                             CATGeometry*                iSupport2,
                                                             int                         iOrientation1,
                                                             int                         iOrientation2,
                                                             CATGeometry*                iContact1,
                                                             CATGeometry*                iContact2,
                                                             CATLONG32&                  oCentripetalOrientation,
                                                             const CATLONG32             iContinuityMode = 0) = 0;


  //---------------------------------------------------------------------------
  // Draft Surface creation.
  //---------------------------------------------------------------------------
          CATDraftSurface* CreateDraftSurface     (const CATCurve*              profile,
                                                   const CATMathDirection&      direction,
                                                   const CATAngle&              angle,
                                                   const double&                length1,
                                                   const double&                length2,
                                                         CATMathSetOfPointsND&  ioMapping,
                                                   const CATCrvLimits*          limits = 0,
                                                   const CATLISTP(CATCrvParam)* params = 0);
  
          CATDraftSurface* CreateDraftSurface     (      CATDraftSurfaceCreationData* ioData);
  
  virtual CATDraftSurface* CreateDraftSurfaceBasic(const CATCurve*              profile,
                                                   const CATMathDirection&      direction,
                                                   const CATAngle&              angle,
                                                   const double&                length1,
                                                   const double&                length2,
                                                         CATMathSetOfPointsND&  ioMapping,
                                                   const CATCrvLimits*          limits = 0,
                                                   const CATLISTP(CATCrvParam)* params = 0) = 0;
  
  virtual CATDraftSurface* CreateDraftSurfaceBasic(CATDraftSurfaceCreationData* ioData) = 0;
  
  virtual CATDraftSurface* CreateDraftSurfaceBasic(const CATSurface* ToCopy) = 0;


  //---------------------------------------------------------------------------
  // Chamfer Surface creation 
  //---------------------------------------------------------------------------
    
          CATChamferSurface* CreateChamferSurface(const CATMathSetOfPointsND* iParams,
                                                  const CATMathSetOfPointsND* iPoints,
                                                  const CATMathSetOfPointsND* iTangents,
                                                  const CATMathSetOfPointsND* iSecondDerivatives,
                                                  const CATLONG32             iFirstTraceIndex,
                                                  const CATLONG32             iSecondTraceIndex,
                                                  const short                 iConfiguration,
                                                  // Modif alm 02/10 : suppression de la spine, le chamfer type est defini dans
                                                  // GeometricObjects/PublicInterfaces/CATConnectDefines.h
                                                  //       CATCurve* iSpine,
                                                  const CATLONG32             iChamferType,
                                                  const double                iFirstValue,
                                                  const double                iSecondValue,
                                                  CATSurface*                 iSurface1,
                                                  CATSurface*                 iSurface2,
                                                  int                         iOrientation1,
                                                  int                         iOrientation2,
                                                  CATGeometry*                iContact1,
                                                  CATGeometry*                iContact2);
  
  virtual CATChamferSurface* CreateChamferSurfaceBasic(const CATMathSetOfPointsND* iParams,
                                                       const CATMathSetOfPointsND* iPoints,
                                                       const CATMathSetOfPointsND* iTangents,
                                                       const CATMathSetOfPointsND* iSecondDerivatives,
                                                       const CATLONG32             iFirstTraceIndex,
                                                       const CATLONG32             iSecondTraceIndex,
                                                       const short                 iConfiguration,
                                                       // Modif alm 02/10 : suppression de la spine, le chamfer type est defini dans
                                                       // GeometricObjects/PublicInterfaces/CATConnectDefines.h
                                                       //      CATCurve* iSpine,
                                                       const CATLONG32             iChamferType,
                                                       const double                iFirstValue,
                                                       const double                iSecondValue,
                                                       CATSurface*                 iSurface1,
                                                       CATSurface*                 iSurface2,
                                                       int                         iOrientation1,
                                                       int                         iOrientation2,
                                                       CATGeometry*                iContact1,
                                                       CATGeometry*                iContact2) = 0;


  //---------------------------------------------------------------------------
  // Directional Surface creation
  //---------------------------------------------------------------------------

          CATDirectionalSurface* CreateDirectionalSurface     (CATPCurve*            iGuideCurve,
                                                               CATCrvLimits*         iLimits,
                                                               CATAngle              iAngleWithNormal,
                                                               CATLength             iLengthRuled,
                                                               CATMathSetOfPointsND& ioMapping); 
  
  
  virtual CATDirectionalSurface* CreateDirectionalSurfaceBasic(CATPCurve*            iGuideCurve,
                                                               CATCrvLimits*         iLimits,
                                                               CATAngle              iAngleWithNormal,
                                                               CATLength             iLengthRuled,
                                                               CATMathSetOfPointsND& ioMapping) = 0;


  //---------------------------------------------------------------------------
  // Spec Surface creation
  //---------------------------------------------------------------------------

          CATSpecSurface* CreateSpecSurface     (CATSpecSurfaceDef* iSpecSurfaceDef);
  
  virtual CATSpecSurface* CreateSpecSurfaceBasic(CATSpecSurfaceDef* iSpecSurfaceDef) = 0;
  

  //---------------------------------------------------------------------------
  // Proc Surface creation
  //---------------------------------------------------------------------------

          CATProcSurface* CreateProcSurface     (CATProcSurfaceDef* iProcSurfaceDef);
  
  virtual CATProcSurface* CreateProcSurfaceBasic(CATProcSurfaceDef* iProcSurfaceDef) = 0;


  //---------------------------------------------------------------------------
  // Linear Transfo Surface creation 
  //---------------------------------------------------------------------------

          CATLinearTransfoSurface* CreateLinearTransfoSurface     (CATMathTransformation  & iTransformation,
                                                                   CATSurface*              iReference);
  
          CATLinearTransfoSurface* CreateLinearTransfoSurface     (CATLinearTransfoSurface* iSurfaceToCopy);
  
  virtual CATLinearTransfoSurface* CreateLinearTransfoSurfaceBasic(CATMathTransformation  & iTransformation,
                                                                   CATSurface*              iReference) = 0;


  //---------------------------------------------------------------------------
  // Non Linear Transfo Surface creation 
  //---------------------------------------------------------------------------

          CATNonLinearTransfoSurface* CreateNonLinearTransfoSurface     (CATMathNonLinearTransformation& iTransformation,
                                                                         CATSurface*                     iReference);

          CATNonLinearTransfoSurface* CreateNonLinearTransfoSurface     (CATMathNonLinearTransformation& iTransformation,
                                                                         CATSurface*                     iReference,
                                                                         CATSurLimits&                   iSurMaxLimits); 

          CATNonLinearTransfoSurface* CreateNonLinearTransfoSurface     (CATNonLinearTransfoSurface* iSurfaceToCopy);
  
  virtual CATNonLinearTransfoSurface* CreateNonLinearTransfoSurfaceBasic(CATMathNonLinearTransformation& iTransformation,
                                                                         CATSurface*                     iReference) = 0;

  virtual CATNonLinearTransfoSurface* CreateNonLinearTransfoSurfaceBasic(CATMathNonLinearTransformation& iTransformation,
                                                                         CATSurface*                     iReference,
                                                                         CATSurLimits&                   iSurMaxLimits) = 0;


  //---------------------------------------------------------------------------
  // Non Linear Transfo PCurve creation
  //---------------------------------------------------------------------------
  
          CATNonLinearTransfoPCurve* CreateNonLinearTransfoPCurve(           CATPCurve*                        iFromPCrv,
                                                                       const double                            iuShift,
                                                                       const double                            ivShift,
                                                                             CATMathNonLinearTransformation2D* ioTransfo,
                                                                             CATSurface*                       iSupport);
  
  virtual CATNonLinearTransfoPCurve* CreateNonLinearTransfoPCurveBasic(      CATPCurve*                        iFromPCrv,
                                                                       const double                            iuShift,
                                                                       const double                            ivShift,
                                                                             CATMathNonLinearTransformation2D* ioTransfo,
                                                                             CATSurface*                       iSupport) = 0;

  
  #ifndef CATCGMRemoveNoDocDrop7
  //---------------------------------------------------------------------------
  // Orientable creation
  //---------------------------------------------------------------------------

          CATOrientable* CreateOrientable(      CATGeometry*    iGeometry,
                                          const CATLONG32       iOrientable);
  #endif //CATCGMRemoveNoDocDrop7Drop2

  
          CATOrientable* CreateOrientable(           CATOrientable* ToCopy);
  
  virtual CATOrientable* CreateOrientableBasic(      CATGeometry* iGeometry,
                                               const CATLONG32 iOrientable) = 0;



  //---------------------------------------------------------------------------
  // Access to Model Size and Resolution
  //---------------------------------------------------------------------------

  virtual CATPositiveLength GetModelSize() const = 0;

  virtual CATPositiveLength GetResolution            (const CATResolutionType iResolutionType = CatC0) const = 0;

 
  //Deprecated method. Do not use. AAD 20120731
  virtual void              SetModelSize             (const double   & iModelSize                 ) = 0;
 

  //Deprecated method. Do not use. AAD 20120731
  virtual void              SetModelSizeAndResolution(      double     iModelSizeInUnit           ,
                                                            CATBoolean iKeepPreviousResolution    = FALSE,
                                                            double     iResolutionC0FromModelSize = 1.E-8) = 0;  //@NumValidated 

  virtual void              SetScaleCategory         (      CATCGMScaleCategory iScaleCategory) = 0;//++EB 20130403

#if ! defined  ( CATIACGMR217Code )
  //  virtual const CATTolerance &GetTolerance() const = 0;//--EB 20140529
  INLINE  const CATTolerance &GetTolerance      () const; //++EB 20140529
#endif
  virtual const CATTolerance &GetToleranceObject() const = 0; //++EB 20140529

  //---------------------------------------------------------------------------
  // Access to Unit and Infinite
  //---------------------------------------------------------------------------

  virtual double GetUnit() const = 0;
  
  virtual double GetInfinite() const = 0;

  virtual void SetUnit(const double iUnitInMeter) = 0;


  //---------------------------------------------------------------------------
  // Access to Tolerance
  //---------------------------------------------------------------------------

  // Retrieves the CATCGMInternalTol associated with <tt>this</tt> CATGeoFactory.
  virtual CATCGMInternalTol           * GetCGMInternalTol();

  virtual CATCGMTolerancesCompatibility CompareTolerances(CATGeoFactory* iOtherFactory, 
                                                          CATBoolean     iThrowIfComparableButNotIdentical = FALSE) = 0;

  //---------------------------------------------------------------------------
  // for upward compatibility - do not use
  //---------------------------------------------------------------------------
  virtual CATPositiveLength GetIdenticalPointTolerance() const;
    
  //---------------------------------------------------------------------------
  // returns the implicit factory(factory for implicit objects)
  //---------------------------------------------------------------------------
  virtual CATGeoFactory   * GetImplicitGeoFactory() const = 0;
  
  //---------------------------------------------------------------------------
  // returns the factory of this
  //---------------------------------------------------------------------------
  virtual CATGeoFactory   * GetGeoFactory() const = 0;
 
  //---------------------------------------------------------------------------
  // Retrieves an object from its tag 
  //  Default implementation returning always NULL
  //---------------------------------------------------------------------------
  virtual CATICGMObject   * FindObjectFromTag (      CATULONG32               tag      ,
                                                     CATGeometricType         iType    = CATGeometryType);
  
  //---------------------------------------------------------------------------
  // Multiple Retrieves an object from its tag 
  //---------------------------------------------------------------------------
  virtual void              FindObjectsFromTag(const CATLONG32                iNbObject,
                                               const CATULONG32               iTags[]  ,
                                                     CATLISTP(CATICGMObject)& ioObjects);

  //---------------------------------------------------------------------------
  // Object Duplication into the Container
  //---------------------------------------------------------------------------
          CATGeometry* Clone(const CATGeometry* iObjectToBeCloned);
  
  //---------------------------------------------------------------------------
  // remove object from the container
  //---------------------------------------------------------------------------
  virtual void Remove(CATICGMObject*                                  iObjectToRemove,
                      const CATICGMContainer::CATRemovingDependancies iHow           = CATICGMContainer::KeepDependancies) = 0;
  
  virtual void Remove(CATICGMObject*                                  iObjectToRemove,
                      CATCGMJournalList*                              iInReport     ) = 0;
  
  virtual void Remove(CATBody          *                              iBody         ,
                      CATTopData       &                              iTopData      ) = 0;
  
  //---------------------------------------------------------------------------
  // returns the Datum Geometry
  //---------------------------------------------------------------------------
  virtual const CATGeometry* GetDatum(const CATGeoFactory::CATDatumId Id) const;

  //---------------------------------------------------------------------------
  // Points geometric compare
  //---------------------------------------------------------------------------
          CATBoolean Compare(const CATMathPoint&, const CATMathPoint&) const;


  //---------------------------------------------------------------------------
  // KernelAttributeKey
  //---------------------------------------------------------------------------
  
  virtual void      AddKernelAttributeKey   (int       iAttributeKey ,
                                             int       iAttributeType) = 0;

  virtual void      RemoveKernelAttributeKey(int       iAttributeKey ) = 0;

  virtual CATLONG32 GetNbKernelAttributeKeys() = 0;

  virtual int       GetKernelAttributeKey   (CATLONG32 iIndex        ,
                                             int     & oAttributeType) = 0;

  //---------------------------------------------------------------------------
  // Optimize data management
  //---------------------------------------------------------------------------
  virtual void Tass();
   
  //---------------------------------------------------------------------------
  // Internal utilities to report Limits
  //---------------------------------------------------------------------------
  static void MapSurLimits(const CATSurface* From, CATSurface* To);

  static void MapCrvLimits(const CATCurve* From, CATCurve* To);
  
  //---------------------------------------------------------------------------
  // To get access to the Factory interface
  //---------------------------------------------------------------------------
  virtual ULONG __stdcall CATAddRefFrom(void               * iForDebug     ,
                                        CATBoolean           iLockEquation = FALSE);

  virtual ULONG __stdcall CATReleaseFrom(void              * iForDebug     ,
                                         CATBoolean          iLockEquation = FALSE);

  virtual int             IsATypeOf     (CATGeometricType    iTypeReference)const;

  virtual void            PropagateQuery(CATICGMUnknown    * iFrom         ,
                                         CATCGMQueryManager& iQuery        );

  //---------------------------------------------------------------------------
  // GetProtectedInterface
  //---------------------------------------------------------------------------
  static CATGeoFactoryProtected* GetFactoryProtectedInterface(CATGeoFactory* iFactory);

  //---------------------------------------------------------------------------
  // GetProtectedInterface : DO NOT USE, USE GetFactoryProtectedInterface instead !!!!!!!
  //---------------------------------------------------------------------------
          CATGeoFactoryProtected* GetProtectedInterface() const;

  #ifndef CATCGMRemoveNoDocDrop7 // Prereq is to Remove CATGeoFactory::Clone

  virtual CATHyperbola          * CreateHyperbola               (CATHyperbola            * ToCopy);
          CATCloudOfPoints      * CreateCloudOfPoints           (CATCloudOfPoints        * ToCopy); 
          CATGenericRuledSurface* CreateGenericRuledSurface     (CATGenericRuledSurface  * ToCopy);
          CATRuledSurface       * CreateRuledSurface            (CATRuledSurface         * ToCopy);
          CATChamferSurface     * CreateChamferSurface          (CATChamferSurface       * ToCopy);
          CATNurbsCurve         * CreateNurbsCurve              (CATNurbsCurve           * ToCopy);
          CATDraftSurface       * CreateDraftSurface            (CATDraftSurface         * ToCopy);
          CATGenericFillet      * CreateGenericFillet           (CATGenericFillet        * ToCopy);
          CATCircularSweep      * CreateCircularSweep           (CATCircularSweep        * ToCopy);
          CATSweepSurface       * CreateSweepSurface            (CATSweepSurface         * ToCopy);
          CATOffsetSurface      * CreateOffsetSurface           (CATOffsetSurface        * ToCopy);
          CATRevolutionSurface  * CreateRevolutionSurface       (CATRevolutionSurface    * ToCopy);
          CATTabulatedCylinder  * CreateTabulatedCylinder       (CATTabulatedCylinder    * ToCopy);
          CATTorus              * CreateTorus                   (CATTorus                * ToCopy);
          CATSphere             * CreateSphere                  (CATSphere               * ToCopy);
          CATCone               * CreateCone                    (CATCone                 * ToCopy);
          CATCylinder           * CreateCylinder                (CATCylinder             * ToCopy);
          CATCircle             * CreateCircle                  (CATCircle               * ToCopy);
          CATPlane              * CreatePlane                   (CATPlane                * ToCopy);
          CATSplineCurve        * CreateSplineCurve             (CATSplineCurve          * ToCopy);
          CATPEllipse           * CreatePEllipse                (CATPEllipse             * ToCopy);
          CATLine               * CreateLine                    (CATLine                 * ToCopy);
          CATContactCurve       * CreateContactCurve            (CATContactCurve         * ToCopy); 
          CATMergedCurve        * CreateMergedCurve             (CATMergedCurve          * ToCopy); 
          CATSimCurve           * CreateSimCurve                (CATSimCurve             * ToCopy); 
          CATIntCurve           * CreateIntCurve                (CATIntCurve             * ToCopy); 
          CATPSpline            * CreatePSpline                 (CATPSpline              * ToCopy);
          CATPNurbs             * CreatePNurbs                  (CATPNurbs               * ToCopy);
          CATPCurveEquation     * CreatePCurveEquation          (CATPCurveEquation       * ToCopy);
          CATPCircle            * CreatePCircle                 (CATPCircle              * ToCopy);
          CATPLine              * CreatePLine                   (CATPLine                * ToCopy);
          CATMacroPoint         * CreateMacroPoint              (CATMacroPoint           * ToCopy);
          CATCartesianPoint     * CreateCartesianPoint          (CATCartesianPoint       * ToCopy);
          CATPointOnSurface     * CreatePointOnSurface          (CATPointOnSurface       * ToCopy);
          CATPointOnCurve       * CreatePointOnCurve            (CATPointOnCurve         * ToCopy);
          CATPointOnEdgeCurve   * CreatePointOnEdgeCurve        (CATPointOnEdgeCurve     * ToCopy); 



  #endif // CATCGMRemoveNoDocDrop7
  

  // Definition du comportement de la loi en fonction du scale de la factory
  // iPowerScaleF : puissance du scale avec lequel varie la valeur de la loi
  // iPowerScaleX : puissance du scale avec lequel varie le parametre de la loi
  //*********** IMPLEMENTATION R18 EN ATTENTE. OK R19****************************
  virtual void       SetScaleOptionBasic(CATLaw   * iLaw        ,
                                         CATLONG32  iPowerScaleF,
                                         CATLONG32  iPowerScaleX,
                                         CATLONG32  iReviewed   = 0) =0 ;

          void       SetScaleOption     (CATLaw   * iLaw        ,
                                         CATLONG32  iPowerScaleF,
                                         CATLONG32  iPowerScaleX,
                                         CATLONG32  iReviewed   = 0) ;
  // returns 0 if not previously set
  virtual CATLONG32  GetScaleOptionBasic(CATLaw   * iLaw        ,
                                         CATLONG32& oPowerScaleF,
                                         CATLONG32& oPowerScaleX,
                                         CATLONG32& oReviewed   ) =0 ;

          CATLONG32  GetScaleOption     (CATLaw   * iLaw        ,
                                         CATLONG32& oPowerScaleF,
                                         CATLONG32& oPowerScaleX,
                                         CATLONG32& oReviewed   ) ;




  //---------------------------------------------------------------------------
  // Scan creation
  //---------------------------------------------------------------------------

          CATScan* CreateScan(           CATLONG32         iNbPoints,
                                   const float*            iPoints,
                                   const float*            iNormals,
                                   const CATULONG32*       iPointsActivity,
                                         CATLONG32         NumberOfScan,
                                         CATLONG32*        NumberOfPointsPerScan,
                                         CATPositiveLength CharacteristicDistance = 0);

          CATScan* CreateScanBasic(      CATLONG32         iNbPoints,
                                   const float*            iPoints,
                                   const float*            iNormals,
                                   const CATULONG32*       iPointsActivity,
                                         CATLONG32         NumberOfScan,
                                         CATLONG32*        NumberOfPointsPerScan,
                                         CATPositiveLength CharacteristicDistance = 0);


  //---------------------------------------------------------------------------
  // Tess Cloud creation
  //---------------------------------------------------------------------------
  
          CATTessCloud* CreateTessCloud(           CATCloud*   iCloud, 
                                                   CATLONG32   iNbPrimitives,
                                             const CATLONG32*  iPrimitives,
                                             const CATLONG32*  iNeighbours,
                                             const CATULONG32* iPrimitivesActivity);

          CATTessCloud* CreateTessCloudBasic(      CATCloud*   iCloud, 
                                                   CATLONG32   iNbPrimitives,
                                             const CATLONG32*  iPrimitives,
                                             const CATLONG32*  iNeighbours,
                                             const CATULONG32* iPrimitivesActivity) ;
  

  //---------------------------------------------------------------------------
  // Tess Scan creation
  //---------------------------------------------------------------------------
  
          CATTessScan* CreateTessScan(      CATScan*          iScan,
                                            CATLONG32         iNbPrimitives,
                                      const CATLONG32*  iPrimitives,
                                      const CATLONG32*  iNeighbours,
                                      const CATULONG32* iPrimitivesActivity);

  
          CATTessScan* CreateTessScanBasic(CATScan*          iScan,
                                           CATLONG32         iNbPrimitives,
                                           const CATLONG32*  iPrimitives,
                                           const CATLONG32*  iNeighbours,
                                           const CATULONG32* iPrimitivesActivity) ;


  //---------------------------------------------------------------------------
  // Cloud Of Points creation
  //---------------------------------------------------------------------------

          CATCloudOfPoints* CreateCloudOfPoints(      CATLISTP(CATMathSetOfPointsND)& iListOfPoints,
                                                const CATPositiveLength               iOperatingDistance); 
  
          CATCloudOfPoints* CreateCloudOfPointsBasic(      CATLISTP(CATMathSetOfPointsND)& iListOfPoints,
                                                     const CATPositiveLength               iOperatingDistance) ; 


  //---------------------------------------------------------------------------
  // Cloud Objects creation
  //---------------------------------------------------------------------------

          CATCldBody                    * CreateCldBody                    (const CATCldSetOfPoints* iSetOfPoints = NULL);

          CATCldBody                    * CreateCldBody                    (const CATCldGenEntity  * iEntity);

          CATCldCloud                   * CreateCldCloud                   (const CATCldGenEntity  * iEntity);

          CATCldScan                    * CreateCldScan                    (const CATCldGenEntity  * iEntity);

          CATCldGrid                    * CreateCldGrid                    (const CATCldGenEntity  * iEntity);

          CATCldPolygon                 * CreateCldPolygon                 (const CATCldGenEntity  * iEntity);

          CATCldVectors                 * CreateCldVectors                 (const CATCldGenEntity  * iEntity);

          CATCldSetOfScans              * CreateCldSetOfScans              (const CATCldGenEntity  * iEntity);

          CATCldSetOfGrids              * CreateCldSetOfGrids              (const CATCldGenEntity  * iEntity);

          CATCldScanOnPolygon           * CreateCldScanOnPolygon           (const CATCldPolygon    * iPolygon);

          CATCldSetOfPointsF            * CreateCldSetOfPointsF            ();

          CATCldSetOfPointsD            * CreateCldSetOfPointsD            ();

          CATCldCloud                   * CreateCldCloudBasic              (const CATCldGenEntity  * iEntity);

          CATCldScan                    * CreateCldScanBasic               (const CATCldGenEntity  * iEntity);

          CATCldGrid                    * CreateCldGridBasic               (const CATCldGenEntity  * iEntity);

          CATCldPolygon                 * CreateCldPolygonBasic            (const CATCldGenEntity  * iEntity);

          CATCldVectors                 * CreateCldVectorsBasic            (const CATCldGenEntity  * iEntity);

          CATCldSetOfScans              * CreateCldSetOfScansBasic         (const CATCldGenEntity  * iEntity);

          CATCldSetOfGrids              * CreateCldSetOfGridsBasic         (const CATCldGenEntity  * iEntity);

          CATCldScanOnPolygon           * CreateCldScanOnPolygonBasic      (const CATCldPolygon    * iPolygon);

          CATCldSetOfPointsF            * CreateCldSetOfPointsFBasic       ();

          CATCldSetOfPointsD            * CreateCldSetOfPointsDBasic       ();

          CATCloud                      * CreateCloud                      (      CATLONG32          iNbPoints,
                                                                            const float            * iPoints,
                                                                            const float            * iNormals,
                                                                            const CATULONG32       * iPointsActivity,
                                                                                  CATPositiveLength  CharacteristicDistance = 0);

          CATCloud                    * CreateCloudBasic                    (      CATLONG32         iNbPoints,
                                                                             const float           * iPoints,
                                                                             const float           * iNormals,
                                                                             const CATULONG32      * iPointsActivity,
                                                                                   CATPositiveLength CharacteristicDistance = 0);
 
  //---------------------------------------------------------------------------
  // Subdivision Mesh creation
  //---------------------------------------------------------------------------

          CATSubdivMesh                    * CreateSubdivMesh                    ();

          CATSubdivMesh                    * CreateSubdivMesh                    (CATSobMesh* iMesh);

          CATSubdivMesh                    * CreateSubdivMesh                    (CATSubdivMeshGeo* iSubdivMeshGeo);
          CATSubdivMesh                    * CreateSubdivMeshBasic                    (CATSubdivMeshGeo* iSubdivMeshGeo);


          CATSubdivMesh                    * CreateSubdivMeshBasic               (CATSobMesh* iMesh);
   //-----------------------------------------------------------------------------
  // CATSubdivMeshGeo creation implementation
  //-----------------------------------------------------------------------------
          CATSubdivMeshGeo                    * CreateSubdivMeshGeoBasic         (CATSobMesh* iMesh, const CATBoolean iBuildInsideFactory = TRUE);

  //-----------------------------------------------------------------------------
  // CATSubdivCellSurface creation from a CATSubdivMeshGeo object, a CATSobFace and a Daughter-Face Index
  //-----------------------------------------------------------------------------
          CATSubdivCellSurface                    * CreateSubdivCellSurface      ()  ;
          CATSubdivCellSurface                    * CreateSubdivCellSurface      (CATSubdivMesh* iSubdivMesh,
                                                                                  CATSobFace * iFace,
                                                                                  int iDaughterIndex) ;
          CATSubdivCellSurface                    * CreateSubdivCellSurfaceBasic (CATSubdivMesh* iSubdivMesh,
                                                                                  CATSobFace * iFace,
                                                                                  int iDaughterIndex);

  //--------------------------------------------------------------------------------------------------
  // CATSubdivCellSurface creation from a CATSubdivMesh object, and Grid of NU*NV CATSobFace(s) 
  // Such as iTabFaces[iu + iv*NU] 0<=iu<NU 0<=iv<NV 
  //--------------------------------------------------------------------------------------------------
          CATSubdivGridSurface                     * CreateSubdivGridSurface     (      CATSubdivMesh*         iSubdivMesh,
                                                                                  const int                    NU         ,
                                                                                  const int                    NV         ,
                                                                                        CATSobFace   * const * iTabFaces  ) ;

          CATSubdivGridSurface                     * CreateSubdivGridSurfaceBasic(      CATSubdivMesh*         iSubdivMesh,
                                                                                  const int                    NU         ,
                                                                                  const int                    NV         ,
                                                                                        CATSobFace   * const * iTabFaces  );

  //Create a Surface with the imposed Steps in the Uniforms KnotVectors
          CATSubdivGridSurface                     * CreateSubdivGridSurface     (      CATSubdivMesh      * iSubdivMesh,
                                                                                  const int                  NU         ,
                                                                                  const int                  NV         ,
                                                                                        CATSobFace * const * iTabFaces  ,
                                                                                        double               StepU      ,
                                                                                        double               StepV      );

          CATSubdivGridSurface                     * CreateSubdivGridSurfaceBasic(      CATSubdivMesh      * iSubdivMesh,
                                                                                  const int                  NU         ,
                                                                                  const int                  NV         ,
                                                                                        CATSobFace * const * iTabFaces  ,
                                                                                        double               StepU      ,
                                                                                        double               StepV      );
  
  //---------------------------------------------------------------------------
  // Polyhedral objects
  //---------------------------------------------------------------------------
          
  /*
  Deprecated instantiation of CATGeoPolyPoint, CATGeoPolyCurve, CATGeoPolySurface, CATGeoPolyBody
  See CATGeoPolyFactory to switch to new implementations, wrapping native CATIPolyObjects

  CATGeoPolyPoint   *CreateGeoPolyPoint(CATIPolyPoint *iPolyPoint);
  CATGeoPolyCurve   *CreateGeoPolyCurve(CATIPolyCurve *iPolyCurve);
  CATGeoPolySurface *CreateGeoPolySurface(CATIPolySurface *iPolySurface) ;

  CATGeoPolyBody    *CreateGeoPolyBody(CATPolyBody *iPolyBody);
  */

  virtual CATCldSubPolygon* CreateCldSubPolygon(const CATCldPolygon* iPolygon);
  virtual CATCldSubPolygon* CreateCldSubPolygonBasic (const CATCldPolygon* iPolygon);

  //---------------------------------------------------------------------------
  // Restricted
  //---------------------------------------------------------------------------


          void NoDefaultImplemention() const;

          void *NoDefaultImplemention(const char iMessage[]) const;


  //---------------------------------------------------------------------------
  // Dangerous : do not use
  // UserGeometry creation
  //---------------------------------------------------------------------------
  virtual  CATUserGeometry* CreateUserGeometry(CATGeometry *iGeometry);


  //---------------------------------------------------------------------------
  // GetGeoImlicitFactory (for ScalarFields)
  //---------------------------------------------------------------------------

  virtual CATGeoImplicitFactory* GetGeoImplicitFactory(CATBoolean iCreationMode=FALSE) = 0;

protected :

  virtual ~CATGeoFactoryProtected() ;
          CATGeoFactoryProtected( const CATCGMMode iMode = CatCGMImplicit) ;

  //---------------------------------------------------------------------------
  // Internal utilities
  //---------------------------------------------------------------------------
  INLINE CATRootContainerCGM* GetRootContainer (int& IsExplicit) const ;
          void InitRootContainer ();
          void RaiseUnavailableMethod( const char* MethodName ) ;

#if defined ( CATCGMBOAObject ) 
  //---------------------------------------------------------------------------
  //  As CATRootContainerCGM (_MyRoot) is directly aggregated 
  //      no more need previous redondant variable
  //---------------------------------------------------------------------------
  CATBoolean        _IsInitialised;
  CATCGMContainer * _PerfImplicitContainer;
  unsigned short    _CreateExplicit ;
#else
  //---------------------------------------------------------------------------
  // Pointer to RootContainer & type
  // Warning : You Must call  InitRootContainer if _Root is NULL
  //---------------------------------------------------------------------------
  CATRootContainerCGM *  _Root ;
  unsigned short _CreateExplicit ;
#endif

};


//-----------------------------------------------------------------------------
// INLINE functions 
//-----------------------------------------------------------------------------
INLINE CATRootContainerCGM* CATGeoFactoryProtected::GetRootContainer(int& IsExplicit) const
{
#if defined ( CATCGMBOAObject ) 
  if ( !_IsInitialised ) ((CATGeoFactoryProtected*)this)->InitRootContainer();
  IsExplicit = _CreateExplicit ;
  return (CATRootContainerCGM *) _PerfImplicitContainer ;
#else
  // Initialisation
  //---------------------------------------------
  if ( !_Root ) ((CATGeoFactoryProtected*)this)->InitRootContainer();
  IsExplicit = _CreateExplicit ;
  return _Root ;
#endif
}
#if ! defined  ( CATIACGMR217Code )
INLINE const CATTolerance &CATGeoFactoryProtected::GetTolerance() const
{
  return GetToleranceObject() ;
}
#endif 

//-----------------------------------------------------------------------------
// Macro for creating objects.
// This macro is used by CATGeoFactoryCGM and others child Factories.
//-----------------------------------------------------------------------------

#if defined ( CATCGMBOAObject ) 

#define CATCGMMacCreateBegin( iCATGeoFactoryGEO, iClassImpl , iClassInterface  )    \
  if (! iCATGeoFactoryGEO->_IsInitialised) iCATGeoFactoryGEO->InitRootContainer (); \
  TIECGM##iClassInterface * newTie = new TIECGM##iClassInterface();                 \
  if ( newTie == NULL ) CATThrowForNullPointerReturnValue(NULL);                    \
  iClassImpl* NewObject = ( iClassImpl*) & (newTie->_CGM_object);                   \
  if ( NewObject == NULL ) CATThrowForNullPointerReturnValue(NULL);                 \
  (iCATGeoFactoryGEO->_PerfImplicitContainer)->SetContainerImpl( NewObject  );      \
  iClassInterface* NewInterface = newTie;

#define CATCGMMacCreateEnd(iCATGeoFactoryGEO,iEvent)                    \
  ( iCATGeoFactoryGEO->_PerfImplicitContainer )->Add ( NewObject );     \
  if ( iEvent ) NewObject->IsModified();                                \
  if ( iCATGeoFactoryGEO->_CreateExplicit )                             \
   NewObject->SetMode ( CatCGMExplicit ) ;                              \
  else if ( CATCGMDebug::EventsOnImplicit ) {                           \
   ( iCATGeoFactoryGEO->_PerfImplicitContainer )->Callback(NewInterface,CATCGMEventCallback::Created);  \
   }                                                

#else

#define CATCGMMacCreateBegin( iCATGeoFactoryGEO, iClassImpl , iClassInterface  )                \
  if (! iCATGeoFactoryGEO->_Root) iCATGeoFactoryGEO->InitRootContainer ();                      \
  iClassImpl* NewObject = new iClassImpl((CATCGMContainer *)(void *)iCATGeoFactoryGEO->_Root);  \
  if ( NewObject == NULL ) CATThrowForNullPointerReturnValue(NULL);                             \
  ((CATCGMContainer *)(void *)iCATGeoFactoryGEO->_Root)->SetContainerImpl(NewObject);           \
  CATICGMUnknown* LocalInterface = NewObject->GetInterface();                                   \
  if ( LocalInterface == NULL ) CATThrowForNullPointerReturnValue(NULL);                        \
  iClassInterface* NewInterface = (iClassInterface*)LocalInterface


#define CATCGMMacCreateEnd(iCATGeoFactoryGEO,iEvent)                           \
  ((CATCGMContainer *)(void *)(iCATGeoFactoryGEO->_Root))->Add ( NewObject );  \
  if ( iEvent ) NewObject->IsModified();                                       \
  if ( iCATGeoFactoryGEO->_CreateExplicit )                                    \
   NewObject->SetMode ( CatCGMExplicit ) ;                                     \
  else if ( CATCGMDebug::EventsOnImplicit ) {                                  \
   ((CATCGMContainer *)(void *)(iCATGeoFactoryGEO->_Root))->Callback(NewInterface,CATCGMEventCallback::Created);  \
   }                                                

#endif




#define CATMacCreateBegin(iClassImpl,iClassInterface) \
  CATCGMMacCreateBegin(this,iClassImpl,iClassInterface)

#define CATMacCreateEnd(iEvent) \
  CATCGMMacCreateEnd(this,iEvent)



#endif






