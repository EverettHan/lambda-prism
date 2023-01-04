#ifndef CATIPGMFaceCurvatureAnalyzer_h_
#define CATIPGMFaceCurvatureAnalyzer_h_

// COPYRIGHT DASSAULT SYSTEMES 2021
//=============================================================================
//
// CATFaceCurvatureAnalyzer : operator evaluating curvatures on a CATFace
//                            returning mathematical values
//                            supporting both exact and polyhedral geometries
//
// The main motivation of this operator consists in hiding to the caller
// the geometrical type (CATSurface / CATGeoPolySurface ...) of the CATFace
//
//=============================================================================
// Usage notes:
//
// This operator can be used to retrieve the curvatures from any point of a CATFace
// This operator is a multi-Run operator, in order to compute curvatures from several points
// The caller has to call Run() as many times he has defined a point on face
//
// All the returned curvature values are signed
// The gaussian curvature, as product of minimal and maximal curvatures, 
// is negative in case of change of convexity between the 2 principal directions, else positive.
// The other curvatures (Min, Max, Mean, Border, Inward, SpecDir) are 
// - null if the surface is locally planar (infinite radius)
// - positive if the local normal points to the center of the local circle (concave configuration),
// - negative if the center of the local circle is opposite to the local normal (convex configuration)
//
//=============================================================================

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"

class CATCrvParam;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATPoint;
class CATSoftwareConfiguration;
class CATSurParam;
class CATVertex;
class CATMathPoint;
class CATMathDirection;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMFaceCurvatureAnalyzer;

class ExportedByCATGMModelInterfaces CATIPGMFaceCurvatureAnalyzer: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFaceCurvatureAnalyzer();

  //-----------------------------------------------------------------------
  //- Public Settings, to call before Run()
  //-----------------------------------------------------------------------
  // Different ways to define the point on face on which the operator will evaluate local curvatures
  // This point has to verify a semantic link with the input CATFace
  // -----------------------------------------------------------------------------------------------
  // The input CATSurParam has to reference the geometry of the CATFace
  virtual void SetSurParam(const CATSurParam &iSurParam) = 0;

  // The input point has to reference the geometry of the CATFace
  virtual void SetPoint(CATPoint *iPointOnFace) = 0;

  // The input vertex has to belong to the CATFace boundary, or to be lying on the CATFace
  virtual void SetVertex(CATVertex *iVertexOnFace) = 0;

  // The input edge has to belong to the CATFace boundary, or to be lying on the CATFace
  virtual void SetEdgeParam(CATEdge *iEdgeOnFace, const CATCrvParam &iCrvParam) = 0;

  // The input edge has to belong to the CATFace boundary, or to be lying on the CATFace
  // The input point has to reference the geometry of the CATEdge
  virtual void SetEdgePoint(CATEdge *iEdgeOnFace, CATPoint *iPointOnEdge) = 0;


  // Sets a specific direction in addition of a specific point
  // ---------------------------------------------------------
  // Each time a new point is specified, this specific direction will be reset to null
  virtual void SetSpecDirection(const CATMathDirection &iSpecDir) = 0;

  // Enables/Disables the curvature computation along the boundary from edges or vertices
  // The default mode is disabled
  // It's mandatory to enable this mode before Run() in order to get the Border Curvature after Run()
  // ---------------------------------------------------------
  virtual void SetBorderDirectionMode(CATBoolean iEnableBorderMode) = 0;

  // Enables/Disables the curvature computation inward the face from bounded edges or vertices
  // The default mode is disabled
  // It's mandatory to enable this mode before Run() in order to get the Inward Curvature after Run()
  // ---------------------------------------------------------
  virtual void SetInwardDirectionMode(CATBoolean iEnableInwardMode) = 0;


  //-----------------------------------------------------------------------
  //- Public Get Methods, to call after Run()
  //-----------------------------------------------------------------------
  // Returns the 2 principal signed curvatures (min and max)
  // The optional vectors are the directions which are tangent to the local circular arcs
  // These 2 vectors are othorgonal to the local normal, but not necessarily orthogonal to each other
  virtual HRESULT GetPrincipalCurvatures(
    double &oMinCurvature,
    double &oMaxCurvature,
    CATMathDirection *opMinDirection = NULL,
    CATMathDirection *opMaxDirection = NULL) = 0;

  // Returns the signed mean curvature
  virtual HRESULT GetMeanCurvature(double &oMeanCurvature) = 0;

  // Returns the signed product of the 2 principal curvatures
  // This product is called "Gaussian curvature"
  virtual HRESULT GetGaussianCurvature(double &oGaussianCurvature) = 0;

  // Additional curvatures from a specified edge or vertex (if any) belonging to the face boundary
  // ---------------------------------------------------------------------------------------------
  // The border curvature is computed from an edge (input edge or edge incident to an input vertex), 
  // following the positive/negative loop orientation according to iOrientationVsLoop
  virtual HRESULT GetBorderCurvature(
    CATOrientation &iOrientationVsLoop,
    double &oBorderCurvature,
    CATMathDirection *opBorderDirection = NULL) = 0;

  // The inward curvature is computed from an edge or a vertex, following the vector inward the face
  virtual HRESULT GetInwardCurvature(
    double &oInwardCurvature,
    CATMathDirection *opInwardDirection = NULL) = 0;

  // Additional curvature in a specific direction defined calling SetSpecDirection before Run()
  // ------------------------------------------------------------------------------------------
  // Returns the signed curvature observed locally in the specified direction
  virtual HRESULT GetDirectionalCurvature(double &oLocalCurvature) = 0;


  //-----------------------------------------------------------------------
  //- Other Get Methods, to call after Run()
  //-----------------------------------------------------------------------

  // Returns the 3D point from which the computation has been done
  // Returns E_FAIL if the current point has no semantic link with the input CATFace
  virtual HRESULT GetMathPoint(CATMathPoint &oMathPt) = 0;

  // Returns the normal direction computed on the current point,
  // taking into account the contextual orientation associated to the input CATFace
  // Returns E_FAIL if the current point has no semantic link with the input CATFace
  virtual HRESULT GetNormal(CATMathDirection &oMathDir) = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFaceCurvatureAnalyzer(); // -> delete can't be called
};

/**
 * Creates the CATFaceCurvatureAnalyzer from a face
 * @param iFactory
 * The factory containing all the input geometric objects
 * @param iSoftwareConfiguration
 * The pointer to the software configuration for the Versioning management
 * @param iFaceToEvaluate
 * The face to evaluate the local curvatures from any point
 * <dd>Use the <tt>Run</tt> method to computes the operation.</dl>
 * @param iFaceOrientation
 * The contextual orientation (positive by default) to considerate the face
 * CATOrientationPositive and CATOrientationNegative are the 2 only expected values
 * In case of negative value, the face will be seen as inverted during the computation :
 * the sign of all the curvatures will be inverted, the normal direction will be inverted,
 * the minimal (resp. maximal) curvature value will be changed into the maximal (resp. minimal) value etc...
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMModelInterfaces CATIPGMFaceCurvatureAnalyzer *CATPGMCreateFaceCurvatureAnalyzer(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATFace *iFaceToEvaluate,
  CATOrientation iFaceOrientation = CATOrientationPositive);

#endif /* CATIPGMFaceCurvatureAnalyzer_h_ */
