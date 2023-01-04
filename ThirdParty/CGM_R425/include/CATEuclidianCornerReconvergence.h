//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
//
// CATEuclidianCornerReconvergence :
//
//==========================================================================
// Aug.2000 dad Creation
// Oct 2004 EAB Versionning Interne
// 24/06/16 NLD Numerotation des constructeurs
//              Suppression par flag de precompilation des constructeurs 1 et 2 sans configuration
//              et du constructeur 3 a rayon unique
//              apres migration de tous les appelants
// 01/07/16 NLD Suppression definitive des constructeurs 1, 2 et 3
//==========================================================================

#ifndef CATEuclidianCornerReconvergence_H
#define CATEuclidianCornerReconvergence_H

#include "Connect.h"
#include "CATCGMOperator.h"
#include "CATCGMOutput.h"

#include "CATBoolean.h"
#include "CATMathIntervalND.h"
#include "CATSurParam.h"
#include "CATCrvParam.h"
#include "CATSurLimits.h"
#include "CATCrvLimits.h"

class CATSurface;
class CATCurve;
class CATSoftwareConfiguration;

class ExportedByConnect CATEuclidianCornerReconvergence :public CATCGMOperator
{
public:

  // Constructor4
  // New constructor with two different radius
  //   Note that only iRadius1 can be equal to 0.
  //   If iRadus1 == iRadius2 the behavior is strictly equivalent with both constructors
  CATEuclidianCornerReconvergence(CATGeoFactory            *  iFactory,
                                  CATSoftwareConfiguration *  iConfig ,
                                  CATSurface               *  iSupport,
                                  CATCurve                 *  iCrv1   ,
                                  CATCurve                 *  iCrv2   ,
                                  double                      iRadius1,
                                  double                      iRadius2,
                                   CATSurLimits             & iSurLimits ,
                                   CATCrvLimits             & iCrv1Limits,
                                   CATCrvLimits             & iCrv2Limits,
                                   CATSurParam              & iCenterInit,
                                   CATCrvParam              & iCrv1Init,
                                   CATCrvParam              & iCrv2Init);

  ~CATEuclidianCornerReconvergence();
   
   // int Run();
   int        RunOperator();
   
   void       Beginning();
   CATBoolean Next();
   void       GetSolution(CATSurParam &ioCenterParam, CATCrvParam &ioCrv1Param, CATCrvParam &ioCrv2Param);
   CATLONG32  GetNbOfSolutions();
private:
   void       AddSolution(double iCenterU, double iCenterV, double iTCrv1, double iTCrv2);
   
   
private:
   CATSurface * _Support;
   CATCurve   * _Crv1;
   CATCurve   * _Crv2;
   double       _Radius1,
                _Radius2;
   CATSurParam  _CenterInit;
   CATCrvParam  _Crv1Init;
   CATCrvParam  _Crv2Init;
   double     * _CenterU;
   double     * _CenterV;
   double     * _TCrv1;
   double     * _TCrv2;
   CATLONG32    _NbOfSolutions;
   CATLONG32    _IndexSol;
   CATMathIntervalND _Domain;
   CATSoftwareConfiguration * _Config;

  //========================================================================
  // Gestion CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;

public:
          const CATString        * GetOperatorId();
                CATExtCGMReplay  * IsRecordable  (short & LevelOfRuntime, short &VersionOfStream);
  virtual       void               WriteInput    (CATCGMStream  & os);
  virtual       void               WriteOutput   (CATCGMStream & os);
  virtual       CATBoolean         ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual       void               Dump          (CATCGMOutput& os ) ;
  virtual       void               DumpOutput    (CATCGMOutput & os);
  virtual       void               DumpOutput    (CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual       CATCheckDiagnostic CheckOutput   (CATCGMOutput & os);
};

#endif

