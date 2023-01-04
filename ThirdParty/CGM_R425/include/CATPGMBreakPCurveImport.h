#ifndef CATPGMBreakPCurveImport_h_
#define CATPGMBreakPCurveImport_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"
#include "CATTolerance.h"

class CATFrFNurbsMultiForm;
class CATKnotVector;
class CATMathPoint;
class CATMathPolynomX;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurfaceImport;

//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATPGMBreakPCurveImport
{
public:
  /**
   * Constructor
   */
  CATPGMBreakPCurveImport();

  /**
   * Destructor
   */
  virtual ~CATPGMBreakPCurveImport();

  virtual CATLONG32 Run() = 0;

  virtual CATFrFNurbsMultiForm *GetNewMF() = 0;

  // attention, ces MF sont des donnees membres de la classe et
  // sont detruites par le destructeur de la classe.
  virtual void GetResultingMultiForms(
    CATLONG32 &nbNewMFs,
    CATFrFNurbsMultiForm **&newMFs,
    CATLONG32 *&iNumSupportingSurf) = 0;

  virtual void GetResultingPCurves(CATLONG32 &nbNewPCurves, CATPCurve **&newPCurves) = 0;
};

// Do not use
ExportedByCATGMModelInterfaces CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
  CATFrFNurbsMultiForm *mf,
  CATLONG32 nbKnotsU,
  double *knotsU,
  CATLONG32 nbKnotsV,
  double *knotsV,
  const CATTolerance &iTolObject = CATGetDefaultTolerance());

ExportedByCATGMModelInterfaces CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
  CATPCurve *initialPCurve,
  CATSurfaceImport *surfaceImport);

#endif /* CATPGMBreakPCurveImport_h_ */
