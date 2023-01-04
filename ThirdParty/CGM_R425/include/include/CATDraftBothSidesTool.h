//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATDraftBothSidesTool:
//
//=============================================================================
// Usage notes:
// 23/10/14  Q48  Implement X-scale in CGM-replay
// Mars 16 JSX : Tool with CATsoftwareconfiguration 
// Apr 21  SME31  Implement GetCutterDimension()
//=============================================================================
#ifndef CATDraftBothSidesTool_h
#define CATDraftBothSidesTool_h

#include "Connect.h"

#include "CATConnectTool.h"
#include "CATMathDef.h"

#include "CATMathVector.h"
#include "CATMathInterval.h"

#include "CATCGMStream.h"
#include "CATString.h"

#include "CATSurLimits.h"

class CATGeometry;
class CATCurve;
class CATSurface;
class CATMathFunctionRN;
class CATSoftwareConfiguration;


class ExportedByConnect CATDraftBothSidesTool : public CATConnectTool
{
 public:
   enum CATMixingFunctionType { MasterSlave, SlaveMaster, Ideal };

   CATDraftBothSidesTool(CATSoftwareConfiguration * iConfig,
                         const CATMathVector & iDirection1,
                         const CATMathVector & iDirection2, 
                         double alpha0, double beta0,
                         CATMixingFunctionType  iMixingFunctionType,
                         double iSmoothParameter=0.);
   
   ~CATDraftBothSidesTool();

  CATLONG32 GetType() const;
  CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

  void SetAlphaLimits(double alphaMin, double alphaMax);
  void SetBetaLimits(double betaMin, double betaMax);


  CATDraftBothSidesTool::CATMixingFunctionType GetMixingFunctionType() const;
  void GetMinimumAngles(double & alpha0, double & beta0) const;
  double GetSmoothParameter() const;
  CATMathInterval GetAlphaLimits() const ;
  CATMathInterval GetBetaLimits() const;
  void GetDirections(CATMathVector & oDirection1, CATMathVector & oDirection2) const;

  CATMathFunctionRN * CreateMixingFunction(CATGeometry ** iSupports, CATLONG32 iNbSupports);

  CATMathFunctionRN * CreateMixingFunction(CATCurve* iSupport1, CATCurve* iSupport2, CATSurface* iSupport3);//SOU

  // pkc : adaptation CGMReplay
  // Methodes de stream et de unstream ( cf architecture CATCGMOperator )
  CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  void WriteInput(CATCGMStream  & Str);
  static CATString _OperatorId;
  const CATString * GetOperatorId();

 private:

  double _alpha0, _beta0;
  CATMathInterval _alphaLimits, _betaLimits;
  CATDraftBothSidesTool::CATMixingFunctionType _MixingFunctionType;
  double _SmoothParameter;    // Parametre R pour la fonction de melange dans le cas ideal
  CATMathVector _Direction1, _Direction2;
};

#endif
