// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
//  Class for construction Conics as a NURBS
//  with various specifications
//
//  Aug 00  Creation                   PBK
//  Oct 03  Ajout SoftwareConfig       JSX
// 16/07/08 NLD Ajout Reset(). A rendre publique pour reutilisation de l'objet?
//=============================================================================
#ifndef CATConicsAsNurbsComputation_H 
#define CATConicsAsNurbsComputation_H 

#include "CATPConicsComputation.h"
#include "Y30UIUTI.h"

class CATSurface;
class CATPCurve;
class CATGeoFactory;
class CATFrFNurbsMultiForm;
class CATSoftwareConfiguration;

#include "CATMathPoint2D.h"
#include "CATMathVector2D.h"
#include "CATMathPlane.h"


//-------------------------------------------------------------------------
class ExportedByY30UIUTI CATConicsAsNurbsComputation : public CATCGMOperator
{
 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATConicsAsNurbsComputation(CATGeoFactory      *iFactory,
                              CATSoftwareConfiguration *iConfig,
                              const CATMathPlane &iPLane);
  ~CATConicsAsNurbsComputation();

  /**
   * Compute PConics with 3 points (iExtremityPoints[0], iExtremityPoints[1], iPointOnConic)
   * and two tangents(iExtremityTangents[i] : Tangent of the PConic at iExtremityPoints[i])
   */
  void SetPConicsDefinition(const CATMathPoint2D   iExtremityPoints[2],
                            const CATMathVector2D  iExtremityTangents[2],
                            const CATMathPoint2D  &iPointOnConic,
                            const CATMathPoint2D  *iDerExtremityPoints = NULL,
                            const CATMathVector2D *iDerExtremityTangents = NULL,
                            const CATMathPoint2D  *iDerPointOnConic = NULL);

  /**
   * Compute PConics with 3 points (iExtremityPoints[0], iExtremityPoints[2], iPointOnConic)  
   * and another point (iExtremityPoints[1] : intersection of the tangents computed at 
   * iExtremityPoint[0] and iExtremityPoints[2] )
   */
  void SetPConicsDefinition(const CATMathPoint2D  iExtremityPoints[3],
                            const CATMathPoint2D &iPointOnConic,
                            const CATMathPoint2D *iDerExtremityPoints = NULL,
                            const CATMathPoint2D *iDerPointOnConic = NULL);

  /**
   * Compute PConics with 2 points (iExtremityPoint[0], iExtremityPoint[2]) and a ratio (0<Ratio<1)
   * and another point (iExtremityPoints[1] : intersection of the tangents computed at 
   * iExtremityPoint[0] and iExtremityPoints[2] )
   */
  void SetPConicsDefinition(const CATMathPoint2D  iExtremityPoints[3],
                            double                iRatio,
                            const CATMathPoint2D *iDerExtremityPoints = NULL,
                            const double         *iDerRatio = NULL);

  /**
   *  Compute PConics from 4 points and one tangent, the tangent corresponding to
   *  point index iTgtOfPtIndex (0<= iTgtOfPtIndex < 4)
   */
  void SetPConicsDefinition(const CATMathPoint2D  iPoints[4],
                            const CATMathVector2D &iTangent, CATLONG32 iTgtOfPtIndex,
                            const CATMathPoint2D  *iDerPoints = NULL,
                            const CATMathVector2D *iDerTangent = NULL);

  /**
   *  Compute PConics from 5 points
   */
  void SetPConicsDefinition(const CATMathPoint2D  iPoints[5],
                            const CATMathPoint2D *iDerPoints = NULL);

  /**
   *  Set Derivative Plane
   */
  void SetDerivativePlane(const double *iDerivativePlane);

  /**
   *  Set the degree of the output MultiForm
   */
  void SetDegree(short iDegree);

  /**
   *  Get the Sofware Configuration
   */
     virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;
  /**
   * Run the operator
   * returns 0 if OK
   */
  int Run();

  /**
   * Get the conic as a CATNurbsCurve, the degree of the NurbsCurve is 2 or 5
   * return NULL if there is no solution for the specified degree
   */
  CATFrFNurbsMultiForm* GetMultiForm();

  /**
   * Return the results
   */
  void GetCoord(double *oCoord);
  void GetHCoord(double *oHCoord);
  void GetFirstDeriv(double *oFirstDeriv);
  void GetHFirstDeriv(double *oHFirstDeriv);

  int CheckFirstDeriv();

  //=======================================================================
  //- Protected Functions
  //=======================================================================
 protected :

  void Reset(const CATMathPlane &iPlane) ;
  int CheckData();

  int ScalePoints();
  int ComputeImplicitEquation();
  int ComputeLocalAxis();
  int ComputeAandB();
  int ComputeControlPointsCoord();
  int Compute3DPoints();
  CATFrFNurbsMultiForm* CreateMultiForm();
  int CheckResult(CATFrFNurbsMultiForm* iMultiForm);
  void VisualizeDebug(CATFrFNurbsMultiForm *iMultiForm);

  //=======================================================================
  //- Protected Data
  //=======================================================================
 protected :

  // les entrees
  CATSoftwareConfiguration *_Config;
  short                 _Degree;
  short                 _NbPoints;
  short                 _NbTangents;
  short                 _TgtOfPtIndex[2];
  CATBoolean            _SpecPointsAvaible;
  CATBoolean            _DerivateAsked;

  CATMathPoint2D        _Points[5];
  CATMathVector2D       _Tangents[2];
  CATMathPoint2D        _SpecPoints[3];
  double                _Rho;

  CATMathPoint2D        _DerPoints[5];
  CATMathVector2D       _DerTangents[2];
  CATMathPoint2D        _DerSpecPoints[3];
  double                _DerRho;

  CATMathPoint          _PlaneOrigin;
  CATMathVector         _PlaneVectorU;
  CATMathVector         _PlaneVectorV;

  CATMathPoint          _DerPlaneOrigin;
  CATMathVector         _DerPlaneVectorU;
  CATMathVector         _DerPlaneVectorV;

  // _DefinitionType
  // = 1 for 2pt, 2tg, 1pt on conic
  // = 2 for 3 spec pt, 1 pt on conic
  // = 3 for 3 spec pt, 1 ratio (0.<ratio<1.)
  // = 4 for 4 pt, 1 tg
  // = 5 for 5 pt
  short                 _DefinitionType; 


  // les donnees de travail
  CATMathPoint2D        _TrPoints[5];
  CATMathPoint2D        _DerTrPoints[5];

  CATMathVector2D       _Translation;
  double                _CoefHomot;

  CATMathPoint2D        _O;
  CATMathVector2D       _U, _V;
  double                _A, _B;
  double                _a, _b, _c, _d, _e, _f;
  double                _CoordU[6], _CoordV[6], _Weights[6];

  CATMathPoint2D        _DerO;
  CATMathVector2D       _DerU, _DerV;
  double                _DerA, _DerB;
  double                _aDer, _bDer, _cDer, _dDer, _eDer, _fDer;
  double                _DerCoordU[6], _DerCoordV[6], _DerWeights[6];
  int                   _ReturnCode;

  // les resultats
  CATMathPoint          _Point3D[6];
  CATMathPoint          _DerPoint3D[6];

};


/**
 * Creates an operator for computing a conic as a NurbsCurve
 * Use ALWAYS  : 
 *     the SetPConicsDefinition methods of the CATConicsAsNurbsComputation class 
 *     to specify how to define the conic
 *     the Run method of the CATConicsAsNurbsComputation class to run the operator
 *     and the GetMultiForm method to get the MultiForm result
 */

ExportedByY30UIUTI CATConicsAsNurbsComputation *CATCreateConicsAsNurbsComputation(CATGeoFactory            *iWhere,
                                                               CATSoftwareConfiguration *iConfig,
                                                               const CATMathPlane  &iPlane);


#endif
