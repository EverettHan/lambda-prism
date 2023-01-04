#ifndef CATIPGMTopRibbonHomotopy_h_
#define CATIPGMTopRibbonHomotopy_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"

class CATBody;
class CATCurve;
class CATPlane;
class CATMathPoint;
class CATBlendParams;
class CATDynFilletRadius;
class CATEdgeRibbon;
class CATEdge;
class CATDynEdgeFilletRibbon;
class CATIPGMConnectTool;
class CATSoftwareConfiguration;
class CATMathVector;
class CATLISTP(CATDynFilletRibbon);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopRibbonHomotopy;

// Decoupe une super arete selon la convexite
class ExportedByCATGMOperatorsInterfaces CATIPGMTopRibbonHomotopy: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopRibbonHomotopy();

  virtual int Run() = 0;

  virtual CATCurve *GetCurve() = 0;

  virtual CATBoolean GetNormal(CATMathVector &oNormal) = 0;

  virtual CATBody *GetResult() = 0;

  virtual CATLONG32 GetDiagnostic() = 0;

  virtual void SetRibbonParams(CATBlendParams &iRibbonParams) = 0;

  virtual CATBody *GetCrescentBody() = 0;

  //---------------------------------------------------------------------------
  // CreateCircularBody
  // Crée un body "circulaire" de centre iCentre et de rayon iRadius
  // posé sur le plan iPlane.
  // La donnée iTopData est optionnelle et NULL par défaut.
  //---------------------------------------------------------------------------
  virtual CATBody *CreateCircularBody(
    CATMathPoint &iCentre,
    CATPlane *iPlane,
    double iRadius,
    CATTopData *iTopData = NULL) = 0;

  static CATIPGMConnectTool *GetToolFromSpecs(
    CATSoftwareConfiguration *iConfig,
    CATBody *iCreationBody,
    CATBody *iInitialBody,
    CATLISTP(CATDynFilletRibbon) &iFilletSpecs,
    CATEdge *iEdge);

  static HRESULT GetRadiusAtPoint(
    CATSoftwareConfiguration *iConfig,
    CATBody *iCreationBody,
    CATBody *iInitialBody,
    CATLISTP(CATDynFilletRibbon) &iFilletSpecs,
    CATDynFilletRadius *&ioRadius);

  static CATEdgeRibbon *GetEdgeRibbonFromSpecs(
    CATSoftwareConfiguration *iConfig,
    CATBody *iResult,
    CATBody *iSpecsBody,
    CATEdge *iEdge,
    CATLISTP(CATDynFilletRibbon) &iEdgeFilletsSpecs,
    CATLISTP(CATDynFilletRibbon) *iEdgeFilletsNotToLookAt,
    CATBoolean &iTestWithoutParting,
    CATDynEdgeFilletRibbon *&oFoundSpec,
    CATListPV &oRadiusAlloues,
    CATBoolean &oVariable);

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopRibbonHomotopy(); // -> delete can't be called
};

#endif /* CATIPGMTopRibbonHomotopy_h_ */
