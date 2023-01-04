/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2002
//==========================================================================
//
// CATNurbsQuality :
//
// This class is first designed to check the quality of nurbs elements during data transfer.
// Secondly, we would like it to improve geometry quality by suppliing a geometry correction ability.
//
//=============================================================================
// Usage Notes:
//=============================================================================
// Feb. 02  PRG Creation
// Aug 19th HLN ajout de reparation des InnerCusps
// 28/03/08 NLD Nomenclature: une courbure c'est une courbure, et un rayon
//              de courbure c'est un rayon de courbure. qu'on se le dise
// 21/03/14 NLD Ajout InitCheck()
// 09/03/21 NLD Ajout _DeleteNewMultiForm et _DeleteNewBipar
//              Mise au propre
//==========================================================================
#ifndef CATNurbsQuality_H
#define CATNurbsQuality_H

#include "Interfaces.h"

class CATFrFNurbsMultiForm;
class CATFrFNurbsBipar;
class CATMathPoint;
class CATNurbsCorrection;
class CATFrFBezierCrvAnalysis;
class CATMathFunctionXY;
class CATSoftwareConfiguration;
class CATGeoFactory;

#include "CATListOfInt.h"
#include "CATListOfDouble.h" // hln Cusp

#include "CATCGMOperator.h"
#include "CATNurbsQualityDef.h"

//-----------------------------------------------------------------------------
class ExportedByInterfaces CATNurbsQuality : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATNurbsQuality);
  public :

  // Constructor for 3D Nurbs Curve
  CATNurbsQuality(CATGeoFactory            * factory,
                  CATSoftwareConfiguration * iConfig,
                  CATFrFNurbsMultiForm     * initialMultiForm);

  // Constructor for PNurbs
  CATNurbsQuality(CATGeoFactory            * factory,
                  CATSoftwareConfiguration * iConfig,
                  CATFrFNurbsMultiForm     * initialMultiForm, 
                  CATMathFunctionXY        * supportXGlobalEquation,
                  CATMathFunctionXY        * supportYGlobalEquation,
                  CATMathFunctionXY        * supportZGlobalEquation);

  // Constructor for Surface
  CATNurbsQuality(CATGeoFactory            * factory,
                  CATSoftwareConfiguration * iConfig,
                  CATFrFNurbsBipar         * initialBipar);

  #define CATNurbsQuality_KeepOldDeprecatedConstructors "restent des appelants applicatifs"
  #ifdef CATNurbsQuality_KeepOldDeprecatedConstructors

  //Do not use - Use the constructors with CATSoftwareConfiguration
  // Constructor for 3D Nurbs Curve
  CATNurbsQuality(CATGeoFactory            * factory,
                  CATFrFNurbsMultiForm     * initialMultiForm);

  // Constructor for PNurbs
  CATNurbsQuality(CATGeoFactory            * factory,
                  CATFrFNurbsMultiForm     * initialMultiForm, 
                  CATMathFunctionXY        * supportXGlobalEquation,
                  CATMathFunctionXY        * supportYGlobalEquation,
                  CATMathFunctionXY        * supportZGlobalEquation);

  // Constructor for Surface
  CATNurbsQuality(CATGeoFactory            * factory,
                  CATFrFNurbsBipar         * initialBipar);
  #endif
  //
  virtual ~CATNurbsQuality();

  // 19/08/2005 hln Cusp : default CheckMode is NormalCheck
  void      AddDiagnosticTypeToCheck(CATGeometricalNurbsDiagnosticType      diagnosticTypesToCheck,
                                     CATGeometricalNurbsDiagnosticSeverity  diagnosticSeverity    ,
                                     double                                 tolerance            = -1.,
                                     CATGeometricalNurbsDiagnosticCheckMode diagnosticCheckMode  = CATGeometricalNurbsDiagnostic_NormalCheck);

  // to control the number of subdivision steps
  // and therefore performance as well as accuracy
  void      SetSubdivisionDepth     (CATLONG32                              nbSubdivisions       = 3);

  CATLONG32 RunCheck                ();

  CATLONG32 GetNbErrors             ();

  CATLONG32 GetNbWarnings           ();

  CATLONG32 GetError                (CATLONG32                          iErrorNumber   , // between 0 and nbErrors-1
                                     CATGeometricalNurbsDiagnosticType& detectedError  );

  CATLONG32 GetWarning              (CATLONG32                          iWarningNumber , // between 0 and nbWarnings-1
                                     CATGeometricalNurbsDiagnosticType& detectedWarning);

  // return 0 if there exists a method to try to correct this geometrical pathology
  // -1 otherwise
  CATLONG32 AddTypeToCorrect        (CATGeometricalNurbsDiagnosticType  typesToCorrect);


  // diagnostic is assigned to :
  //      2 if the correction has totally succeeded
  //      1 if the correction has partly succeeded
  //      0 if the correction could not be achieved
  //      -1 if this type of correction has not been achieved
  //
  // returns a non null value if an error has occured
  CATLONG32             GetCorrectionDiagnostic(CATGeometricalNurbsDiagnosticType  errorTypesToCorrect,
                                                CATLONG32                        & diagnostic        );

  // returns 0 if no error has occured during the correction procedure
  // a non null value otherwise.
  CATLONG32             RunCorrection();

  CATFrFNurbsBipar    * GetNewBipare();

  CATFrFNurbsMultiForm* GetNewMultiForm();

  CATListOfInt        * GetINumOfDegeneratedArcsOrPatchs(CATLONG32 iDir); // iDir : 1 for u, 2 for v

  // Additionnal info with CATGeometricalNurbsDiagnostic_PointingSurface
  //  1 : Isopar u = StartU degenerated, 2 : EndU, 4 : StartV, 8 : EndV. (0 : Nothing Detected)
  CATLONG32 GetPointingInfo (CATLONG32 & oDiag);

  private :
    void      DataInitialisation();
    void      InitCheck         ();
    CATLONG32 CheckElementLength        (CATLONG32    & elementTooSmall          );
    CATLONG32 HasConfusedBoundaries     (CATLONG32      iDir                     ,
                                         CATMathPoint*  CPs                      ,
                                         CATLONG32      nbCPsU                   ,
                                         CATLONG32      nbCPsV                   ,
                                         CATLONG32    & diag                     );
    CATLONG32 IsClosedButNotDegenerated (CATLONG32      iDir                     ,
                                         CATMathPoint*  CPs                      ,
                                         CATLONG32      nbCPsU                   ,
                                         CATLONG32      nbCPsV                   ,
                                         CATLONG32    & isClosedAndNotDegenereted);
    CATLONG32 BezierAnalysis            ();
    CATLONG32 OneDirectionBezierAnalysis(CATLONG32                  iIsDirV          ,
                                         CATFrFNurbsMultiForm    *  mf               ,
                                         CATFrFBezierCrvAnalysis *& mfBezierAnalysis);

    CATLONG32 CorrectionInfoTransfer    ();

    CATLONG32                  _iDim; // 1 for Crv, 2 for surface
    CATLONG32                  _iDimCrv; // 3 for NurbsCurve, 2 for PNurbs 

    CATFrFNurbsMultiForm     * _initialMultiForm;
    CATFrFNurbsBipar         * _initialBipar;

    CATListOfInt               _errors;
    CATListOfInt               _warnings;
  
    CATLONG32                  _nbErrors;
    CATLONG32                  _nbWarnings;

    CATFrFNurbsMultiForm     * _newMultiForm;
    CATFrFNurbsBipar         * _newBipar;

    int                        _DeleteNewMultiForm;
    int                        _DeleteNewBipar;

    // diagnostic tolerances
    double                     _subElementMinimumLength;
    double                     _elementMinimumLength;
    double                     _nullTangentTolerance;
    double                     _insideAngleMin;
    double                     _junctionAngleMin;
    double                     _infiniteValue;
    double                     _MicroCurvatureRadius;
    double                     _badParametrizationRatio;
    double                     _pointingTol;

    // diagnostic check flags
    CATLONG32                  _checkElementTooSmall;
    CATLONG32                  _checkSubElementTooSmall;
    CATLONG32                  _checkExternalNullTangent;
    CATLONG32                  _checkInnerCuspOrTwist; // within a sub-element
    CATLONG32                  _checkOuterCuspOrTwist; // between two sub-elements
    CATLONG32                  _checkControlPointsOutOfSpace; // control points out of space
    CATLONG32                  _checkMicroCurvature;
    CATLONG32                  _checkBadParametrization;
    CATLONG32                  _checkPointingSurface;

    CATLONG32                  _controlPointsOutOfSpaceAlreadyChecked; // control points out of space

    // hln Cusp : NormalCheck or FullCheck
    // diagnostic check mode
    CATLONG32                  _checkmodeInnerCuspOrTwist;

    CATLONG32                  _nbSubdivisionSteps;
    CATLONG32                  _pointingInfo;

    CATNurbsCorrection       * _correction;
    CATListOfInt               _listOfPathologyTypeToCorrect;

    CATFrFBezierCrvAnalysis  * _BezierAnalysisU;
    CATFrFBezierCrvAnalysis  * _BezierAnalysisV;

    CATMathFunctionXY        * _supportXGlobalEquation;
    CATMathFunctionXY        * _supportYGlobalEquation;
    CATMathFunctionXY        * _supportZGlobalEquation;

    CATSoftwareConfiguration * _Config;
};
#endif













