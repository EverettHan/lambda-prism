// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATPositionPtLoop
// Class for operator of positionement point - loop
//
//===================================================================
// Dec. 97    Creation                                      X.Gourdon
// 28/11/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 05/12/08 NLD Mieux: afin d'eviter des impacts de compilation des applications appelantes,
//              on declare toujours Run() et on l'implemente avec CATCGMOperatorDebugRunResult()
// 11/12/08 NLD Ajout methode Init()
//              Detabulation
// 12/12/08 NLD Argument Imax a TryInclusion()
// 19/01/10 FDS Data "_CopyInputParameter" for performance
// 15/07/10 JSX Perfo multi run: Nouvelle methode SetMultiRunOptimization
// 17/12/20 R1Y Added DrawPointAndLoop() for displaying inputs.
//===================================================================

#ifndef CATPositionPtLoop_H
#define CATPositionPtLoop_H

#include "Y30C1XMM.h"
#include "CATGeoOperator.h"
//#include "CATCGMOperatorDebug.h"

class CATSurParam;
class CATPCurve;
class CATPointOnCurve;
class CATGeoFactory;
class CATSurface;

class CATMathInterval;
class CATMathFunctionX;
class CATSoftwareConfiguration;

#include "CATSurParam.h"
#include "CATCrvLimits.h"
#include "CATSurLimits.h"

#include "CATMathDef.h"
#include "CATMathLimits.h"
#include "CATMathInline.h"

#include "CATString.h"

#include "CATGeoOpTimer.h"
#include "CATExtCGMReplay.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"

class ExportedByY30C1XMM CATPositionPtLoop   : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATPositionPtLoop);
 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  // iCopyInputParameter : optimisation paramter for perfo , put this parameter to false
  // for performance , avoid copying "iPCrv" , "iStartParam" and "iEndParam".
  // In this case , theses paremeters have not to be distroyed until the end of the operator.
  CATPositionPtLoop(CATGeoFactory * iFactory,
        CATSoftwareConfiguration *iConfig,
        const CATSurParam & iSurParam,
        const CATLONG32 iNbPCrv,
        const CATPCurve ** iPCrv,
        const CATCrvParam * iStartParam,
        const CATCrvParam * iEndParam,
        const double iTol3D,
		const CATBoolean iCopyInputParameter = TRUE);

  CATPositionPtLoop(CATGeoFactory * iFactory,
        CATSoftwareConfiguration *iConfig,
        const CATSurParam & iSurParam,
        const CATLONG32 iNbPCrv,
        const CATPCurve ** iPCrv,
        const CATCrvParam * iStartParam,
        const CATCrvParam * iEndParam);

  // Don't use anymore
  CATPositionPtLoop(CATGeoFactory * iFactory,
        const CATSurParam & iSurParam,
        const CATLONG32 iNbPCrv,
        const CATPCurve ** iPCrv,
        const CATCrvParam * iStartParam,
        const CATCrvParam * iEndParam,
        const double iTol3D);
  CATPositionPtLoop(CATGeoFactory * iFactory,
        const CATSurParam & iSurParam,
        const CATLONG32 iNbPCrv,
        const CATPCurve ** iPCrv,
        const CATCrvParam * iStartParam,
        const CATCrvParam * iEndParam);
  virtual ~CATPositionPtLoop();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  /** @nodoc @nocgmitf */
  virtual int RunOperator();
  //NLD051208 Run() inconditionnel au lieu de CATCGMOperatorDebugDeclareRun(CATPositionPtLoop, CATGeoOperator);
  int Run();

  void SetBoxUV(CATSurLimits & iBoxUV);
  INLINE CATLONG32 GetPosition() const; // returns 1 if in, -1 if out, 0 if on frontier at iTol
  // If the point was found on frontier, return the pcurve index and the param on this pcurve
  void GetPositionOnFrontier(CATLONG32 & oPCrvIndex, CATCrvParam & oCrvParam) const;
  // If the point was found on frontiers, return the pcurve indexes and the params on these pcurves
  // +  oNbPCurves is equal to the number of PCurves on which lie the point
  // +  oPCrvIndex is an array of size oNbPCurves, and oPCrvIndex[i] represents the index of the i-th PCurve
  //    including the point
  // +  oCrvParam is an array of size oNbPCurves, and oCrvParam[i] represents the parameter on the i-th PCurve
  //    including the point
  //
  // Note : when oNbPCurves>0, the arrays oPcrvIndex and oCrvParam should be deleted by the caller.
  void GetPositionOnFrontiers(CATLONG32 & oNbPCurves, CATLONG32 *& oPCrvIndex, CATCrvParam *& oCrvParam) const;

  // Methode speciale pour booleen : renvoie true si le point a ete trouve frontiere sur un trou 
  // Spec validite avec ice/xdt le 30/04/02 a 15h43 : le point est dans le trou s'il est a plus de la 
  // resolution de ses deux extremites (sinon, il sera considere dans un vertex)
  // oGapIndex contient l'index de la PCurve qui precede le trou (dans l'ordre passe dans le constructeur)
  CATBoolean IsInGap(CATLONG32 & oGapIndex);
  // Methode speciale pour booleen : renvoie true si le point a ete trouve frontiere sur un vertex
  // extremite oGapIndex contient l'index de la PCurve qui precede le trou (dans l'ordre passe dans le constructeur)
  INLINE CATBoolean IsInVertex();


  // When the point is in, return 1 is the loop is positively oriented, -1 is negatively oriented
  // return 0 is GetPosition did not return 1
  CATLONG32 GetOrientation();

  void SetSurParam(const CATSurParam & iSurParam);

  INLINE void SetTolerance(double & iTol);

  /**
  *  @nodoc  
  *  Returns  the  Software  configuration  to  be  taken
  *  into  acccount  by  <tt>this</tt>  operator.
  *  @return  
  *  The  Software  configuration.
  */
  CATSoftwareConfiguration*  GetSoftwareConfiguration()  const;

  /**
  *  @nodoc  
  *  Keep extra data for optimisation
  * iopti = TRUE  : Data are kept for improving multirun performance
  *       = FALSE : No extra data are kept
  * Before Calling SetMultiRunOptimization, the otimization is OFF
  */
  void SetMultiRunOptimization(CATBoolean iOpti=TRUE);

  //-----------------------------------------------------------------------
  //- Protected methods
  //-----------------------------------------------------------------------
  
 protected:

 void Init                          (CATGeoFactory * iFactory,
                                     CATSoftwareConfiguration *iConfig,
                                     const CATSurParam & iSurParam,
                                     const CATLONG32 iNbPCrv,
                                     const CATPCurve ** iPCrv,
                                     const CATCrvParam * iStartParam,
                                     const CATCrvParam * iEndParam,
                                     const double iTol);

  CATBoolean ComputeGlobalAngle(double & oAngle);

  
  CATBoolean AngleOnPCrv(int iEdgeOnLoop, const CATPCurve * iPCrv, 
       const CATCrvParam & iStartParam,
       const CATCrvParam & iEndParam,
       double & ouStart, double & ovStart,
       double & ouEnd, double & ovEnd,
       double & oDeltaAngle);
  
  virtual CATLONG32 RAngleOnArc(
         const CATMathInterval & I, const CATMathInterval & Imax,
         CATBoolean & NoInclusionKnown,
         const CATMathFunctionX * fU, const CATMathFunctionX * fV,
         double & oDeltaAngle, const CATLONG32 iDepth);

  virtual double ComputeAngle(const double x0, const double y0,
            const double x1, const double y1);

  // integration sur I, sous-intervalle de Imax
  virtual CATBoolean TryInclusion(const CATMathInterval & I,
          const CATMathInterval & Imax,
          const CATMathFunctionX * fU,
          const CATMathFunctionX * fV);

  virtual CATBoolean GapTreatment(const double x0, const double y0,
          const double x1, const double y1,
          double & oDeltaAngle);

  CATBoolean BoxGapTreatment(const double iLimits[4],
           const double u0, const double v0,
           const double u1, const double v1,
           const CATLONG32 i, 
           double & ioAngle);

  //-----------------------------------------------------------------------
  //- Protected data
  //-----------------------------------------------------------------------

protected:
 
  double _u, _v;
  CATLONG32 _N;
  //const CATCrvParam * _StartParam, * _EndParam;
  CATCrvParam * _StartParam, * _EndParam;
  const CATPCurve ** _PCrv;
  double _Tol3D, _TolUV;
  CATSurface * _Surface;
  
  double * _uMin, * _uMax, * _vMin, *_vMax;
  CATLONG32 _IndexReached;

  CATBoolean _CopyInputParameter; // performance
  
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------

private:

  CATSoftwareConfiguration *_Config;
  int    *_LineInfoSaved;
  double *_LineInfo;

  double _GlobalParamOnFrontier;
  double _LocalTol;
  double _uBoxmin, _uBoxmax, _vBoxmin, _vBoxmax;


  CATCrvParam _CrvParamOnFrontier;

  CATLONG32 _Position, _Orientation;
  CATLONG32 _FrontierPCurveIndex;
  CATLONG32 _GapIndex; // si le point est trouve frontiere sur un trou, contient l'index de la PCurve qui precede le trou; =-1 par defaut

  CATBoolean _IsBoxUV;
  CATBoolean _IsInVertex;
  CATBoolean _KeepOptiData; // !! JSX Attention je ne renseigne pas cette donnée dans le CGMReplay (a faire
                            //    mais cela ne doit pas gener pour l'instant car le replay ne fait qu'un run

//========================================================================
// CGMReplay Implementation - VSJ Creation
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:
  
  /** @nodoc @nocgmitf */
  virtual const CATString * GetOperatorId();
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

  private:
    void DrawPointAndLoop();  // helper function to display the input point and loop
};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

//---------------------------------------------------------------------------------------------------
// returns 1 if in, -1 if out, 0 if on frontier
INLINE CATLONG32 CATPositionPtLoop::GetPosition() const
{
  return _Position;
}

//---------------------------------------------------------------------------------------------------
INLINE CATBoolean CATPositionPtLoop::IsInVertex()
{
  return _IsInVertex;
}

//---------------------------------------------------------------------------------------------------
INLINE void CATPositionPtLoop::SetTolerance(double & iTol)
{
   _Tol3D = iTol;
}



#endif
