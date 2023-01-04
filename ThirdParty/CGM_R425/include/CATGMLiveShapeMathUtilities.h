#ifndef CATGMLiveShapeMathUtilities_H
#define CATGMLiveShapeMathUtilities_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATErrors.h"
#include "CATMathConstant.h"
#include "CATGeoFactory.h"
#include "CATCollec.h"
#include "CATLISTP_CATMathTransformation.h"
#include "ListPOfCATFace.h"
#include "CATEdgeHashTable.h"
#include "CATLISTV_CATMathPoint.h"

class CATlsoContext;
class CATMathVector;
class CATMathLine;
class CATMathPoint;
class CATFace;
class CATCellManifold;
class CATDeclarativeManifold;
class CATMathBox;
class CATMathTransformation;
class CATElementarySurface;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATMath3x3Matrix;

typedef enum 
{
  UnknownTransformation = 0,
  TranslationTransformation = 1, 
  RotationTransformation = 2, 
  IdentityTransformation = 3
}
CATlsoTransformationType;

// @nocgmitf (do not create phase 2 interface) 
class ExportedByPersistentCell CATGMLiveShapeMathUtilities
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  static double GetDefaultTolerance(CATGeoFactory * iFactory);

  // AreSameTransfo
  // --------------
  // If you have no CATlsoContext, create one with a body, or give your tolerance (be carfull with scaling in factory)
  static CATBoolean AreSameTransfo(const CATMathTransformation & iMathTransformation1,
                                   const CATMathTransformation & iMathTransformation2,
                                   CATlsoContext               * iContext,
                                   double                      * iTolerance=NULL);

  // Are Same transfo according to the same criteria as CDS
  static CATBoolean AreSameTransfo(const CATMathTransformation & iMathTransformation1,
                                   const CATMathTransformation & iMathTransformation2,
                                   CATGeoFactory & iFactory);

  // Are Same transfo according to the same criteria as CDS
  static CATBoolean AreSameTransfo(CATLISTP(CATMathTransformation) & iTransfoList,
                                   CATGeoFactory & iFactory);
 

  // AreSameVector
  // -------------
  // If you have no CATlsoContext, create one with a body, or give your tolerance (be carfull with scaling in factory)
  static CATBoolean AreSameVector(const CATMathVector & iVector1,
                                  const CATMathVector & iVector2,
                                  CATlsoContext       * iContext,
                                  double              * iTolerance=NULL);

  // AreSameMatrix
  // -------------
  // If you have no CATlsoContext, create one with a body, or give your tolerance (be carfull with scaling in factory)
  static CATBoolean AreSameMatrix(const CATMath3x3Matrix & iMatrix1,
                                  const CATMath3x3Matrix & iMatrix2,
                                  CATlsoContext       * iContext,
                                  double              * iTolerance=NULL);

  // AreSameLine
  // -------------
  // If you have no CATlsoContext, create one with a body, or give your tolerance (be carfull with scaling in factory)
  static CATBoolean AreSameLine(const CATMathLine & iLine1,
                                const CATMathLine & iLine2,
                                CATlsoContext     * iContext,
                                double            * iTolerance=NULL);

  // AreSameDouble
  // -------------
  // If you have no CATlsoContext, create one with a body, or give your tolerance (be carfull with scaling in factory)
  static CATBoolean AreSameDouble(const double iDouble1,
                                  const double iDouble2,
                                  CATlsoContext       * iContext,
                                  double              * iTolerance);

  // AreSameAngle
  // -------------
  // If you have no CATlsoContext, create one with a body, or give your tolerance (be carfull with scaling in factory)
  static CATBoolean AreSameAngle(const CATAngle iAngle1,
                                 const CATAngle iAngle2,
                                 CATlsoContext       * iContext,
                                 double              * iTolerance);

  // AreSamePoint
  // -------------
  // If you have no CATlsoContext, create one with a body, or give your tolerance (be carfull with scaling in factory)
  static CATBoolean AreSamePoint(const CATMathPoint & iPoint1,
                                 const CATMathPoint & iPoint2,
                                 CATlsoContext       * iContext,
                                 double              * iTolerance);

  // AreSamePlane
  // -------------
  static CATBoolean AreSamePlane(const CATMathPlane & iPlane1,
                                 const CATMathPlane & iPlane2,
                                 CATGeoFactory * iFactory);
  // Power
  // -------------
  // Return iMathTransformation^iN
  static CATMathTransformation Power(const CATMathTransformation & iMathTransformation, int iN);

  // NthRoot
  // -------------
  // Return S_OK if nth root of iMathTransformation has been found.
  static HRESULT NthRoot(const CATMathTransformation & iMathTransformation, int iN, const CATTolerance& iTolerance, CATMathTransformation & oNthRoot);

  // AreConfused
  // -------------
  // If you have no CATlsoContext, create one with a body, or give your tolerance (be carfull with scaling in factory)
  static CATBoolean AreConfused(const CATMathLine & iLine1,
                                const CATMathLine & iLine2,
                                CATlsoContext     * iContext,
                                double            * iTolerance=NULL);

  // ComputeTransformation
  // -------------
  // Compute a Rotation + Translation from two Points and an axis.
  static void ComputeTransformation( const CATMathPoint    & iPoint1,
                                     const CATMathPoint    & iPoint2,
                                     const CATMathLine     & iAxis,
								     CATMathTransformation & oTransfo);

   static HRESULT GetSymmetricAngle(const CATMathPlane &iMathPlane, const CATAngle & iAngle, const CATMathAxis &iAxis, CATGeoFactory * iFactory, CATAngle & oSymAngle);

   static CATlsoTransformationType GetTransformationType(const CATMathTransformation & iTransformation, CATGeoFactory * iFactory);

   static void GetCenter(CATFace * iFace, CATMathPoint & oCenter);

   static void GetCenter(CATCellManifold * iCM, CATMathPoint & oCenter);

   static CATAngle GetAngle(const CATMathPlane & iMathPlane, const CATMathLine & iMathLine, CATGeoFactory * iFactory); //result Angle >= 0 result Angle <= CATPI

   static double GetMax(CATListOfDouble & iValues, CATGeoFactory & factory);

   static double GetMin(CATListOfDouble & iValues, CATGeoFactory & factory);

   static CATBoolean AreConfusedMathPlane(const CATMathPlane & iFirstMathPlane, const CATMathPlane & iSecondMathPlane, CATGeoFactory * iFactory);

   static CATBoolean AreConfusedMathPlane(const CATMathPlane & iFirstMathPlane, const CATMathPlane & iSecondMathPlane, double iTol);

   static CATBoolean AreCoplanarMathLine(CATMathLine * iFirstLine, CATMathLine * iSecondLine, CATGeoFactory * iFactory);

   static void TranslateMathBox(CATMathBox & iBox, CATMathTransformation & iTransfo, CATMathBox & oBox, double iTolerance);

   static void ComputeMathBox(const ListPOfCATFace & iFaceList, CATMathBox & oBox);

   static void ComputeMathBox(const CATEdgeHashTable & iEdgeHT, CATMathBox & oBox);

   static double ComputeMathBoxDiagonal(CATMathBox & iBox);

   static void ComputeMathBoxDimensionList(const CATMathBox & iBox, CATListOfDouble & oDimensionList);

   static CATBoolean DoBoxesIntersect(const CATMathBox& iBox1, const CATMathTransformation& iTransfo, const CATMathBox& iBox2, const double iTolerance); // returns whether iBox1 intersects iTransfo*iBox2 

   static void SetTransfoNull(CATMathTransformation & oTransformation);

   static CATBoolean IsNullMathTransfo(CATMathTransformation * iMathTransfo, double eps);

   static CATBoolean IsNullMathTransfo(CATMathTransformation * iMathTransfo, CATGeoFactory * iFactory);

   static CATBoolean AreSameAxis(CATMathAxis & iAxis1, CATMathAxis & iAxis2, CATGeoFactory * iFactory);

   // additional check : origins and planes.
   static CATBoolean AreExactlySameAxis(CATMathAxis & iAxis1, CATMathAxis & iAxis2, CATGeoFactory * iFactory);

   static CATBoolean IsTransfoNull(const CATMathTransformation & iTransfo, CATGeoFactory & iFactory);
   
   static CATBoolean IsInvariant(CATSurface * iSurface, CATMathTransformation & iTransfo, double iTol);

   static CATElementarySurface * GetElementarySurface(CATFace * iFace, CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATBoolean & oNeedToRemoveEltSurface);

   static void AvoidFlatMathBox(CATMathBox & ioBox, CATGeoFactory & iFactory);

   static CATBoolean AreParallel(CATMathDirection & iFirstDir, CATMathDirection & iSecondDir, double iAngleTol);

   static void GetMinPoint(CATMathBox & iBB, CATMathDirection & iDir, CATMathPoint & oMinPoint, double tol);

   static void GetCurvature (const CATMathVector & iFirstDeriv, const CATMathVector & iSecondDeriv, CATMathVector & oCurvature);

   /**
      Rcomputation of an input transformation into an 
      equivalent neutral invariant transformation before moving a Draft face manifold.

      @param iConfig
             CATSoftwareConfiguration
      @param iFace
             Input (Draft) Face to be moved
      @param iDeclManifold
             Input (Draft) DeclarativeManifold to be moved
      @param iUserTransfo
             Input user transformation
      @param oNewMoveTransfo
             Recomputed transformation (when recomputation is relevent)
      @param oHasTransfoChanged (optional)
             If TRUE, it means that a recomputation has been done, FALSE otherwise

      @returns 
               S_OK if recomputation has occured or no computation needed
               E_FAIL otherwise

      @details
               A recomputation is eventually made iif
               - iUserTransfo is a Translation
               - iDeclManifold is a type of CATDraftManifold
               - iDeclManifold has a planar neutral face
   */
   static HRESULT ComputeTransformationForDraftFaceMove(CATSoftwareConfiguration    * iConfig, 
                                                        CATFace                     * iFace,
                                                        CATDeclarativeManifold      * iDeclManifold,
                                                        const CATMathTransformation & iUserTransfo,
                                                        CATMathTransformation       & oNewMoveTransfo,
                                                        CATBoolean                  * oHasTransfoChanged = NULL);

   // Get the MathPoint which is intersection bet. Curve and Surface
   static CATBoolean ComputeIntersectionSurfaceCurve(CATGeoFactory            * iFactory,
                                                     CATSoftwareConfiguration * iConfiguration,
                                                     CATCurve                 * iCurve,
                                                     CATSurface               * iSurface,
                                                     CATMathPoint             & oIntersectPoint);

   // =======================================
   // Stream/UnStream methods on Math objects (list)
   // =======================================
   
   /* CATLISTV of CATMathPoint */
   static void StreamMathPointList(const CATLISTV(CATMathPoint) & iMathPointList, CATCGMStream  &ioStr);
   static void UnStreamMathPointList(CATLISTV(CATMathPoint) & oMathPointList, CATCGMStream  &ioStr);
};

#endif 
