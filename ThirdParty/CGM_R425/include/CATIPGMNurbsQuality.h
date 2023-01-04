#ifndef CATIPGMNurbsQuality_h_
#define CATIPGMNurbsQuality_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATNurbsQualityDef.h"
#include "CATListOfInt.h"

class CATFrFBezierCrvAnalysis;
class CATFrFNurbsBipar;
class CATFrFNurbsMultiForm;
class CATGeoFactory;
class CATMathFunctionXY;
class CATMathPoint;
class CATNurbsCorrection;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMNurbsQuality;

//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMNurbsQuality: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMNurbsQuality();

  // 19/08/2005 hln Cusp : default CheckMode is NormalCheck
  virtual void AddDiagnosticTypeToCheck(
    CATGeometricalNurbsDiagnosticType diagnosticTypesToCheck,
    CATGeometricalNurbsDiagnosticSeverity diagnosticSeverity,
    double tolerance = -1.,
    CATGeometricalNurbsDiagnosticCheckMode diagnosticCheckMode = CATGeometricalNurbsDiagnostic_NormalCheck) = 0;

  // to control the number of subdivision steps
  // and therefore performance as well as accuracy
  virtual void SetSubdivisionDepth(CATLONG32 nbSubdivisions = 3) = 0;

  virtual CATLONG32 RunCheck() = 0;

  virtual CATLONG32 GetNbErrors() = 0;

  virtual CATLONG32 GetNbWarnings() = 0;

  virtual CATLONG32 GetError(
    CATLONG32 iErrorNumber,
    CATGeometricalNurbsDiagnosticType &detectedError) = 0;

  virtual CATLONG32 GetWarning(
    CATLONG32 iWarningNumber,
    CATGeometricalNurbsDiagnosticType &detectedWarning) = 0;

  // return 0 if there exists a method to try to correct this geometrical pathology
  // -1 otherwise
  virtual CATLONG32 AddTypeToCorrect(CATGeometricalNurbsDiagnosticType typesToCorrect) = 0;

  // diagnostic is assigned to :
  //      2 if the correction has totally succeeded
  //      1 if the correction has partly succeeded
  //      0 if the correction could not be achieved
  //      -1 if this type of correction has not been achieved
  //
  // returns a non null value if an error has occured
  virtual CATLONG32 GetCorrectionDiagnostic(
    CATGeometricalNurbsDiagnosticType errorTypesToCorrect,
    CATLONG32 &diagnostic) = 0;

  // returns 0 if no error has occured during the correction procedure
  // a non null value otherwise.
  virtual CATLONG32 RunCorrection() = 0;

  virtual CATFrFNurbsBipar *GetNewBipare() = 0;

  virtual CATFrFNurbsMultiForm *GetNewMultiForm() = 0;

  virtual CATListOfInt *GetINumOfDegeneratedArcsOrPatchs(CATLONG32 iDir) = 0;

  // Additionnal info with CATGeometricalNurbsDiagnostic_PointingSurface
  //  1 : Isopar u = StartU degenerated, 2 : EndU, 4 : StartV, 8 : EndV. (0 : Nothing Detected)
  virtual CATLONG32 GetPointingInfo(CATLONG32 &oDiag) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMNurbsQuality(); // -> delete can't be called
};

// Constructor for Surface
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
  CATGeoFactory *factory,
  CATSoftwareConfiguration *iConfig,
  CATFrFNurbsBipar *initialBipar);

// Constructor for PNurbs
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
  CATGeoFactory *factory,
  CATSoftwareConfiguration *iConfig,
  CATFrFNurbsMultiForm *initialMultiForm,
  CATMathFunctionXY *supportXGlobalEquation,
  CATMathFunctionXY *supportYGlobalEquation,
  CATMathFunctionXY *supportZGlobalEquation);

// Constructor for 3D Nurbs Curve
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
  CATGeoFactory *factory,
  CATSoftwareConfiguration *iConfig,
  CATFrFNurbsMultiForm *initialMultiForm);

// Constructor for Surface
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
  CATGeoFactory *factory,
  CATFrFNurbsBipar *initialBipar);

// Constructor for PNurbs
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
  CATGeoFactory *factory,
  CATFrFNurbsMultiForm *initialMultiForm,
  CATMathFunctionXY *supportXGlobalEquation,
  CATMathFunctionXY *supportYGlobalEquation,
  CATMathFunctionXY *supportZGlobalEquation);

//Do not use - Use the constructors with CATSoftwareConfiguration
// Constructor for 3D Nurbs Curve
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
  CATGeoFactory *factory,
  CATFrFNurbsMultiForm *initialMultiForm);

#endif /* CATIPGMNurbsQuality_h_ */
