#ifndef CATSetOfPointsToCanonic_H
#define CATSetOfPointsToCanonic_H 

// COPYRIGHT DASSAULT SYSTEMES 1999

// CATSetOfPointsToCanonic
//  Operator to replace a given SetOfPoints by a canonical approximation (plane,
//  cylinder, ...). 
#include "Y30UIUTI.h"

#include "CATCGMOperator.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATGeometryType.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

class CATGeoFactory;
class CATMathSetOfPoints;
class CATSurface;
class CATSurLimits;
class CATSoftwareConfiguration;

class CATCGMStream;
#include "CATString.h"
#include "CATGeoOpTimer.h"	

class ExportedByY30UIUTI CATSetOfPointsToCanonic : public CATCGMOperator {
  CATCGMVirtualDeclareClass(CATSetOfPointsToCanonic);
public :
  //
  //-----------------------------------------------------------------------
  //- Constructor-destructor
  //-----------------------------------------------------------------------
  //
  //Do not use - Use the constructors with CATSoftwareConfiguration
  CATSetOfPointsToCanonic (CATGeoFactory * iFactory,
    CATMathSetOfPoints * iPoints, double iTolApprox, CATGeometricType iFormToRecognize);
  CATSetOfPointsToCanonic(CATGeoFactory * iFactory,
    CATMathPoint * iPoints,
    CATLONG32 NbPoints,
    double iTolApprox, CATGeometricType iFormToRecognize);

  CATSetOfPointsToCanonic (CATGeoFactory * iFactory,CATSoftwareConfiguration * iConfig,
    CATMathSetOfPoints * iPoints, double iTolApprox, CATGeometricType iFormToRecognize);
  
  CATSetOfPointsToCanonic(CATGeoFactory * iFactory,CATSoftwareConfiguration * iConfig,
    CATMathPoint * iPoints,
    CATLONG32 NbPoints,
    double iTolApprox, CATGeometricType iFormToRecognize);
  
  ~CATSetOfPointsToCanonic ();
  //
  // Launches the operator 
  //
  /** @nodoc @nocgmitf */
  int RunOperator ();
  //
  // Returns canonical equivalent surface (or return 0 if no canonical equivalent
  // surface has been found), together with the surface limits.
  //
  CATSurface * GetSurface  (CATSurLimits & oLimits);
  
  CATGeometricType IsCanonic();

  void SetFormToRecognize(CATGeometricType iFormToRecognize);
	
  // 
  // Dans le cas ou on cherche un cylindre, cette methode permet de 
  // donner une init 
  // iCenter = point sur l'axe du cylindre
  // iDir = direction normalisee de l'axe du cylindre
  // Radius = rayon du cylindre
  //	
  void SetInitialCylinder(CATMathPoint &iCenter, CATMathVector &iDir, double iRadius);

  // 
  // Dans le cas ou on cherche un cone, cette methode permet de 
  // donner une init 
  // iApex = sommet du cone (apex)
  // iDir = direction normalisee de l'axe du cone
  // iAngle = demi angle au sommet (radian)
  //
  void SetInitialCone(CATMathPoint &iApex, CATMathVector &iDir, double iAngle);

private : 
  //
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  //
  double _tol;
  CATMathPoint * _Points;
  CATLONG32 _NbPoints;
  CATLONG32 _NbEigenVect;
  CATGeometricType  _FormToRecognize, _FormRecognized;
  double *_CanonicDef;
  CATLONG32 _AllocCanonicDef, _NbCombinaison;
  CATLONG32 _TryMinimize;
  double _InitC[3], _InitD[3], _InitRadius;	
  CATSoftwareConfiguration * _Config;
  //
  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------
  //
  CATLONG32 GetQuadraticForm(double * oCoef);

  void RecognizePlaneForm();
  void CheckPlane();

  void RecognizeCylinderForm(double * iCoef);
  void CheckCylinder();
  void RunCylinderByMinimization();

  void RecognizeSphereForm(double * iCoef);
  void CheckSphere();

  void RunConeByMinimization();
  void CheckCone();

  void Reset();

//========================================================================
// CGMReplay Implementation - VSJ Creation
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:
  
  /** @nodoc @nocgmitf */
  virtual const CATString * GetOperatorId();
  /** @nodoc @nocgmitf */
  virtual CATGeoOpTimer * GetTimer();
  /** @nodoc @nocgmitf */
  virtual CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & Str);
  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void WriteOutput(CATCGMStream & Str);
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMOutput & os) ;
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMStream& Str, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual CATBoolean ValidateOutput(CATCGMStream& Str, CATCGMOutput & os,int VersionNumber=1);  
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

private : 
	CATBoolean Compare(const CATMathPoint &p1, const CATMathPoint &p2);
  
};
//
// Create and remove 
//
// Deprecated create methods ...Use the one with SoftwareConfiguration 
ExportedByY30UIUTI CATSetOfPointsToCanonic * CreateSetOfPointsToCanonic (CATGeoFactory * iFactory,
                                                                         CATMathSetOfPoints * iSetOfPoints,
                                                                         double iTolApprox,
                                                                         CATGeometricType iFormToRecognize = CATGeometryType,
                                                                         CATSkillValue iMode=BASIC);

ExportedByY30UIUTI CATSetOfPointsToCanonic * CreateSetOfPointsToCanonic (CATGeoFactory * iFactory,
                                                                         CATMathPoint * iSetOfPoints,
                                                                         CATLONG32 NbPoints,
                                                                         double iTolApprox,
                                                                         CATGeometricType iFormToRecognize = CATGeometryType,
                                                                         CATSkillValue iMode = BASIC) ;

ExportedByY30UIUTI CATSetOfPointsToCanonic * CATCreateSetOfPointsToCanonic (CATGeoFactory * iFactory,
																																					CATSoftwareConfiguration* iConfig,
                                                                         CATMathSetOfPoints * iSetOfPoints,
                                                                         double iTolApprox,
                                                                         CATGeometricType iFormToRecognize = CATGeometryType,
                                                                         CATSkillValue iMode=BASIC);

ExportedByY30UIUTI CATSetOfPointsToCanonic * CATCreateSetOfPointsToCanonic (CATGeoFactory * iFactory,
																																					CATSoftwareConfiguration* iConfig,
                                                                         CATMathPoint * iSetOfPoints,
                                                                         CATLONG32 NbPoints,
                                                                         double iTolApprox,
                                                                         CATGeometricType iFormToRecognize = CATGeometryType,
                                                                         CATSkillValue iMode = BASIC) ;

ExportedByY30UIUTI void Remove (CATSetOfPointsToCanonic * iCanonicOper);

#endif







