// COPYRIGHT DASSAULT SYSTEMES 1999
//===================================================================
//
// CATEdgeCrvSimplify
// Class for searching a simple EdgeCurve containing the given
// CATCurves in a multi-level EdgeCurve
//
//========================================================================================================
// Feb. 99    Creation                                                                           E. Guerin
// Oct. 09    Suppression "_Surfs" and creation of static method "IsEdgeCurveAlreadySimplified"  F. Dumas
//========================================================================================================

#ifndef CATEdgeCrvSimplify_H
#define CATEdgeCrvSimplify_H

//#define CATEdgeCrvSimplifyDbg               // pour le debug

#include "Y30UIUTI.h"
#include "CATCGMOperator.h"
#include "CATMathDef.h"
#include "CATListOfCATEdgeCurves.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATSurfaces.h"
#include "CATListOfCATPointOnEdgeCurves.h"
#include "CATMathSetOfLongs.h"
#include "CATTrace.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATExtCGMReplay.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"

class CATCurve;
class CATCurve;
class CATPCurve;
class CATSurface;
class CATCrvParam;
class CATCrvLimits;
class CATMapX;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATEdgeCrvSimplify : public CATCGMOperator
   {
   public:
      //-----------------------------------------------------------------------
      //- Object management
      //-----------------------------------------------------------------------

      CATEdgeCrvSimplify(CATGeoFactory* iFactory,CATSoftwareConfiguration * iConfig);
      ~CATEdgeCrvSimplify();

      //-----------------------------------------------------------------------
      //- Public Methods
      //-----------------------------------------------------------------------

      // Performance , static method to filter useless operator creation
      static CATBoolean IsEdgeCurveAlreadySimplified( CATEdgeCurve * iEdgeCurve , 
                                                      const int      iNbPCurves ,
                                                      CATPCurve   ** iPCurves   );

      // Adding new EdgeCrvs to search in
      // The associated Poecs should have a coherent orientation
      void AddMergedCurve(CATEdgeCurve* iECrv, 
                          CATPointOnEdgeCurve* iStartPoec=0,
                          CATPointOnEdgeCurve* iEndPoec=0);

      // Defining the PCrvs to look for, and give CATSurfaces associated with
      // each CATCurves.
      void SetEntries(CATCurve* iPCrv1, CATSurface* iSurf1,
                      CATCurve* iPCrv2, CATSurface* iSurf2);

      void AddEntry(CATCurve * iPCrv, CATSurface * iSupport);

      // SetSimulationMode : 
      // * permits to know if the edgecurve can be simplified or not
      // * Should be called before the run
      // * After the run, just call the IsEdgeCurveSimplifiable() to know if it can be simplified or not
      void SetSimulationMode();

      // SetForceFirstCurveToRefCurve
      // If this method is called before the run method, it permits to have the first specified Curve 
      // (in  SetEntries or AddEntry) as the RefCurve of the output EdgeCurve
      void SetForceFirstCurveToRefCurve();

      // Running the operator. The returned value is TRUE if the 2 PCurves could
      // be found in the EdgeCurves
      int RunOperator();

      // Getting result, eventually trying to create a new EdgeCurve 
      // (*oIsNew is then set to 1)
      // The returned Orientation is given according to Start/End Poecs. It can
      // be 1, -1, or 0 (not enough Poecs provided)
      CATEdgeCurve* GetResult(short* oOrientation=NULL, short* oIsNew=NULL );

      // Creating poecs on the resulting EdgeCurve, using the poecs which were
      // given with AddMergedCurve.
      // If 2 poecs could be created, the result is TRUE, FALSE otherwise.
      short GetPoecs(CATPointOnEdgeCurve** oStartPoec,
                     CATPointOnEdgeCurve** oEndPoec   );

      // IsEdgeCurveSimplifiable : if SetSimulationMode has been set before  the run, permits
      // to know if the simplification can be done or not
      CATBoolean IsEdgeCurveSimplifiable();

   private:
      //-----------------------------------------------------------------------
      //- Protected Methods
      //-----------------------------------------------------------------------
      short SearchPCrvs(CATEdgeCurve* iECrv,CATLONG32 iDepMCrv, CATMathSetOfLongs * SubIsPCrv=0);
      short SetResult(CATEdgeCurve* iECrv);
      short  GetMCrvLimitsOnCrv(CATLONG32 iMCrv,CATCurve* iCrv,CATCrvParam& oStart,CATCrvParam& oEnd);
      CATMapX* GetReportForNewEdgeCurve(     CATLONG32 IndexPCrv1,      CATLONG32 IndexPCrv2,
                                        const CATCrvLimits &iLim1, const CATCrvLimits &iLim2, 
                                        CATBoolean & IsLogicalMapX) const;

      CATBoolean IsLimitsIncluded(const CATTolerance & iTol, 
                                  const CATCrvLimits & iLimIncluded,
                                  const CATCrvLimits & iLimIncluding, 
                                  CATCurve * iCrv);

      CATBoolean ComputeResult(short* oOrientation=NULL,short* oIsNew=NULL, int iSimulMode=0);

   private:
      void ObsoleteAlgorithmForSharpnessTransfer();

      //-----------------------------------------------------------------------
      //- Data
      //-----------------------------------------------------------------------

   private:
      CATSoftwareConfiguration     * _Config;
      CATLISTP(CATEdgeCurve)        _EdgeCrvs;
      CATLISTP(CATPointOnEdgeCurve) _StartPoecs;
      CATLISTP(CATPointOnEdgeCurve) _EndPoecs;
      CATLISTP(CATCurve)            _PCrvs;

      CATBoolean _ForceFirstCurveToRefCurve;
      CATBoolean _SimulationMode;

      // Internal data
      CATLONG32 _NbPCrvs;

      CATMathSetOfLongs             _IndexECrv; // _IndexECrv[i] index dans CATEdgeCurve d'edge contenant a pcurve _Pcrves[i]

      CATEdgeCurve*                 _foundECrv;
      CATLONG32                     _foundIndexECrv;
      short                         _foundOrder;

      CATEdgeCurve * _SubECrv;

      // Data for output
      CATEdgeCurve*                 _EdgeCurve;

#ifdef CATEdgeCrvSimplifyDbg
      CATLONG32                    _nbDbgCols;
#endif


      //========================================================================
      // CGMReplay Implementation - VSJ Creation
      //========================================================================
   protected:
      friend class CATGeoStreamFactory; 

      // private static data
      static CATString _OperatorId;
      static CATGeoOpTimer _Timer;

   public:

      virtual const CATString * GetOperatorId();
      virtual CATGeoOpTimer * GetTimer();
      virtual CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

      virtual void WriteInput(CATCGMStream  & Str);
      virtual void Dump( CATCGMOutput& os ) ;
      virtual void WriteOutput(CATCGMStream & Str);
      virtual void DumpOutput(CATCGMOutput & os) ;
      virtual void DumpOutput(CATCGMStream& Str, CATCGMOutput& os,int VersionNumber=1);
      virtual CATBoolean ValidateOutput(CATCGMStream& Str, CATCGMOutput & os,int VersionNumber=1);  
      virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

   };
                                        
#endif
