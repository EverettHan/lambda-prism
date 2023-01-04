//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//
// CATAutoIntersectionPCrv:
//  To detect AutoIntersection in one curve using its GlobalEquation
//
//
//=============================================================================
//
// Usage Notes:
// Jan. 2004    Versionning                                         E.Malgras
// 10/12/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
//              Detabulation
// 17/04/12 XMH Add SetMaximumNumSolutions
// 04/03/20 NLD Implementation de GetSoftwareConfiguration()
//              Mise au propre
// 11/03/20 Q48 Some C++11 keyword for derived methods
//=============================================================================

#ifndef CATAutoIntersectionPCrv_H
#define CATAutoIntersectionPCrv_H

// ExportedBy
#include "Y30C1XMM.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATSoftwareConfiguration.h"
#include "CATCreateAutoIntersectionPCrv.h"

class CATPCurve;
class CATMathSetOfPointsND;

#include "CATCrvLimits.h"

#include "CATCGMOperatorDebug.h"

class ExportedByY30C1XMM CATAutoIntersectionPCrv : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATAutoIntersectionPCrv);
public:
  //-------------------------
  // Object Management
  //-------------------------

                           CATAutoIntersectionPCrv(CATGeoFactory            *  iFactory  ,
                                                   CATSoftwareConfiguration *  iConfig   ,
                                                   CATPCurve                *  iPCrv     ,
                                                   CATCrvLimits              & iCrvLimits);
                          ~CATAutoIntersectionPCrv();
  
  // @nocgmitf
  CATCGMOperatorDebugDeclareRun(CATAutoIntersectionPCrv, CATGeoOperator);

  /** @nodoc @nocgmitf */
  int                       RunOperator();

  // Set a maximum number of solutions to be found
  // We stop looking for solutions as soon as we have obtained iMaximumNumSolutions solutions.
  // We might obtain more solutions because the solver can return multiple solutions.
  void                      SetMaximumNumSolutions( CATLONG32 iMaximumNumSolutions );
  
  CATSoftwareConfiguration* GetSoftwareConfiguration() const CATGEOOverride CATGEOFinal;
  
  //========================================================================
  // Management of Solutions
  //========================================================================
  CATLONG32                 GetNumberOfCuttingLimits();
  void                      BeginningCutout();
  CATBoolean                NextCuttingLimits();
  void                      GetCuttingLimits(CATCrvLimits &ioCrvLimits);
  
  CATLONG32                 GetNumberOfSelfIntersection();
  void                      BeginningSelfIntersection();
  CATLONG32                 NextSelfIntersection();
  void                      GetSelfIntersection(double * ioSelfIntersectionParam);
  
  
  
  //========================================================================
  // Gestion CGMReplay
  //========================================================================
  
  /** @nodoc @nocgmitf */
  const CATString         * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  CATGeoOpTimer           * GetTimer();
  
  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  
  
  /** @nodoc @nocgmitf */
  CATExtCGMReplay         * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void              WriteInput(CATCGMStream  & ioStream);
  /** @nodoc @nocgmitf */
  virtual void              WriteOutput(CATCGMStream & ioStream);
  /** @nodoc @nocgmitf */
  virtual CATBoolean        ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  //virtual void Dump( CATCGMOutput& os ) ;
  //virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os);
  //virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & ioStream);
  //virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & ioStream);
  
protected:
  friend class CATGeoStreamFactory;
  
  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;
  
  
  
private:
  CATPCurve                * _PCrv;
  CATCrvLimits               _CrvLim;
  CATCrvLimits             * _Cutout;
  CATMathSetOfPointsND     * _SelfIntersection;
  CATLONG32                  _NbOfCuttingLimits;
  CATLONG32                  _CutoutIndex;
  CATLONG32                  _MaximumNumSolutions;
  CATSoftwareConfiguration * _Config;
};

#endif


