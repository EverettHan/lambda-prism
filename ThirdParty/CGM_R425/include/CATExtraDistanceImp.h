// COPYRIGHT DASSAULT SYSTEMES 2008
//===============================================================================================================
//
// CATExtraDistanceImp :
//  Operator to compute a "maximal" distance devoted to Sw
//

#ifndef CATExtraDistanceImp_H
#define CATExtraDistanceImp_H 

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATLocalDistanceType.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATListOfCATSurParams.h"
#include "CATListOfCATCrvParams.h"
// CGMReplay
#include "CATString.h"
#include "CATGeoOpTimer.h"

class CATGeoFactory ;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurLimits;
class CATCurve;
class CATCrvLimits;
class CATPoint;
class CATMathPoint;
class CATSurParam;

class ExportedByY30C3XGG CATExtraDistanceImp : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATExtraDistanceImp); 
public :
  //========================================================================
  //- Object Management
  //========================================================================
  CATExtraDistanceImp(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                      CATSurface * iSurf1, const CATSurLimits * iSurfLim1,CATSurface * iSurf2, const CATSurLimits * iSurfLim2, 
                      CATLocalDistanceType iType1, CATLocalDistanceType iType2);

  CATExtraDistanceImp(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                      CATSurface * iSurf, const CATSurLimits * iSurfLim, CATCurve * iCrv, const CATCrvLimits * iCrvLim,  
                      CATLocalDistanceType iType1, CATLocalDistanceType iType2);

  CATExtraDistanceImp(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                      CATSurface * iSurf, const CATSurLimits * iSurfLim,  CATMathPoint & iPt,CATLocalDistanceType  iType);

  CATExtraDistanceImp(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                      CATCurve * iCrv1, const CATCrvLimits * iCrvLim1,CATCurve * iCrv2, const CATCrvLimits * iCrvLim2,  
                      CATLocalDistanceType  iType1, CATLocalDistanceType  iType2);

  CATExtraDistanceImp(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                      CATCurve * iCrv, const CATCrvLimits * iCrvLim, CATMathPoint & iPt, CATLocalDistanceType  iType);


  ~CATExtraDistanceImp ();

public : 
  int RunOperator ();
  virtual void Get(CATLocalDistanceType & oType1, CATLocalDistanceType & oType2, CATListOfDouble & oMaxDistList, CATLISTP(CATSurParam) & oP1List,CATLISTP(CATSurParam) &  oP2List){};
  virtual void Get(CATLocalDistanceType & oType1, CATLocalDistanceType & oType2, CATListOfDouble & oMaxDistList, CATLISTP(CATSurParam) & oP1List,CATLISTP(CATCrvParam) &  oP2List){};
  virtual void Get(CATLocalDistanceType & oType1, CATListOfDouble & oMaxDistList, CATLISTP(CATSurParam) & oP1List){};
  virtual void Get(CATLocalDistanceType & oType1, CATLocalDistanceType & oType2, CATListOfDouble & oMaxDistList, CATLISTP(CATCrvParam) & oP1List,CATLISTP(CATCrvParam) &  oP2List){};
  virtual void Get(CATLocalDistanceType & oType1, CATListOfDouble & oMaxDistList, CATLISTP(CATCrvParam) & oP1List){};
  virtual void Get(CATLocalDistanceType & oType1, CATLocalDistanceType & oType2, CATBoolean & oIsConst){};
  HRESULT GetDiag();
protected:
  HRESULT  UndefOutput(CATLocalDistanceType & oType1, CATLocalDistanceType & oType2);
  virtual HRESULT RunSurSur()=0;
  virtual HRESULT RunSurCrv()=0;
  virtual HRESULT RunSurPt()=0;
  virtual HRESULT RunCrvCrv()=0;
  virtual HRESULT RunCrvPt()=0;

private:
  // Necessary to prevent unwanted automatic creation by the compiler
  CATExtraDistanceImp(const CATExtraDistanceImp & RecognizerOper);
  void operator = (const CATExtraDistanceImp & RecognizerOper);

  void Init(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig);
  HRESULT InitSur(CATSurface * iSurf, const CATSurLimits * iSurfLim,  CATSurface *& oSurf, CATSurLimits *& oSurLim);
  HRESULT InitCrv(CATCurve * iCrv, const CATCrvLimits * iCrvLim,  CATCurve *& oCrv, CATCrvLimits *& oCrvLim);
  HRESULT InitPt(CATMathPoint & it);
  void Reset(CATSurface *& ioSurf, CATSurLimits *& ioSurfLim);
  void Reset(CATCurve *& ioCrv, CATCrvLimits *& ioCrvLim);


protected : 
  CATGeoFactory                          *  _Factory;
  CATSoftwareConfiguration               *  _Config;
  CATULONG32                                _Mode; //1 Computation, 2 Recognition
  CATULONG32                                _GeoConfig; //1 SurSur, 2 SurCrv, 3 SurPt, 4 CrvCrv, 5 CrvPt
  const CATTolerance                    &  _TolObject;
  double                                   _Tol;
  CATSurface                            *  _Surf1;
  CATSurLimits                          *  _SurLim1;
  CATSurface                            *  _Surf2;
  CATSurLimits                          *  _SurLim2;
  CATCurve                              *  _Crv1;
  CATCrvLimits                          *  _CrvLim1;
  CATCurve                              *  _Crv2;
  CATCrvLimits                          *  _CrvLim2;
  CATMathPoint                             _Pt;
  CATLocalDistanceType                     _Type1;
  CATLocalDistanceType                     _Type2;
  HRESULT                                  _Diagnostic;

  //========================================================================
  // Gestion CGMReplay 
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 
  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;
public:
  // @nocgmitf
  const CATString * GetOperatorId();
  // Gestion timer  
  // @nocgmitf
  CATGeoOpTimer * GetTimer(); 
  // Gestion Mode Record 
  // @nocgmitf
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  // Stream de entrées de l'op 
  // @nocgmitf
  virtual void WriteInput(CATCGMStream  & Str);
  // Stream des sortie (= ref de validation) 
  // @nocgmitf
  virtual void WriteOutput(CATCGMStream & Str)=0;
  // Validation de du resultat
  // @nocgmitf
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1)=0;
  //dumps...
  // @nocgmitf
  void Dump(CATCGMOutput& os) ;
  // @nocgmitf
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1)=0;
  // @nocgmitf
  virtual void DumpOutput(CATCGMOutput & os)=0;
  // Check des sorties permets un stream conditionnels des CGMReplays 
  // @nocgmitf
  CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & Str);

protected:
  virtual   void DumpInput(CATCGMOutput& os)=0 ;
  //========================================================================
  // End section Gestion CGMReplay
  //========================================================================
};


#endif







