#ifndef CATProjectionCrvSurDisGen_h
#define CATProjectionCrvSurDisGen_h


#include "Y30E3PMG.h"
#include "CATGeoOperator.h"
#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"

// System
#include "CATBoolean.h"

// Mathematics
#include "CATMathPoint.h"
#include "CATMathSetOfPointsND.h"
#include "CATMathDirection.h"

// Geometric Objects
#include "CATCrvLimits.h"
#include "CATCrvParam.h"
#include "CATSurLimits.h"
#include "CATSurParam.h"
#include "CATListOfCATCrvParams.h"


// Mathematics
class CATSoftwareConfiguration;

// Geometric Objects
class CATCurve;
class CATGeoFactory;
class CATPCurve;
class CATPointOnSurface;
class CATSurface;
struct CATAnalysisPtSol;

// Geometric Operators


enum CATProjCrvSurDisAdm
{
   CATNone,
   CATUMin,
   CATUMax,
   CATVMin,
   CATVMax
};


//-----------------------------------------------------------------------------
class ExportedByY30E3PMG CATProjectionCrvSurDisGen : public CATGeoOperator
{

public:

   //-----------------------------------------------------------------
   //- Object management
   //-----------------------------------------------------------------

   CATProjectionCrvSurDisGen(CATGeoFactory * iFactory, CATSoftwareConfiguration *iConfig,
                             CATCurve * iCrv ,CATCrvLimits* iCrvLim, CATSurface * iSurface,
                             CATSurLimits* iSurLim, CATLONG32 iSampling);
   CATProjectionCrvSurDisGen (CATGeoFactory* iFactory,CATSoftwareConfiguration *iConfig,
                              CATSurface* iSurface, CATSurLimits* iSurLim ,
                              CATCurve* iCurve ,CATCrvLimits* iCrvLim ,
                              CATMathDirection* iDirection, CATLONG32 iSampling);
   ~CATProjectionCrvSurDisGen();

   //-----------------------------------------------------------------
   //- Set methods
   //-----------------------------------------------------------------

   void SetLimits(CATCrvLimits * iCrvLim);
   void SetLimits(CATSurLimits * iSurLim);
   void SetSampling(CATLONG32 iSampling);

   void SetDirection(CATMathDirection *iDir);
   void SetSurface(CATSurface * iOnNewSurface);
   void SetCurve  (CATCurve * iNewCurveToProject);
   
   void SetDeepAdmissibleAnal (CATProjCrvSurDisAdm iAdmAnal = CATNone);
   
   // To activate the display in cgmout
   void SetOutputDisplay (CATBoolean iOutputDisplay = TRUE);


   //-----------------------------------------------------------------
   //- Running methods
   //-----------------------------------------------------------------
   int RunOperator();
   int RunClassicalProj();
   int RunAdmissbleProj();

   //-----------------------------------------------------------------
   //- Get methods
   //-----------------------------------------------------------------
   CATSoftwareConfiguration* GetSoftwareConfiguration() const;
   void BeginningPoint();
   CATBoolean NextPoint();
   CATLONG32 GetCurrentIndex();
   CATPointOnSurface * GetPointOnSurface(CATLONG32 &oRank) const;
   // In Deep Admissible Analysis mode, Adm is the position relative to the border
   // 0: exactly on the border, 1 or -1 project at less than resolution, 2 or -2 project at more than resolution
   // sign means inside or outside
   CATPointOnSurface * GetPointOnSurfaceAdm(CATLONG32 &oRank, CATLONG32 &oAdm) const;
   
   CATLISTP(CATCrvParam) GetSampling();
   
   
   // private methods
private:
   // data handling methods
   void StorePointSol(CATAnalysisPtSol iPointSol, CATLONG32 iRank);
   void StorePointSolAdm(CATAnalysisPtSol iPointSol, CATLONG32 iRank, CATLONG32 iAdm);
   
   
   // Private data
   CATCurve * _Crv;
   CATSurface * _Surf;
   CATSoftwareConfiguration *_Config;

   CATCrvLimits _CrvLim;
   CATSurLimits _SurLim;

   CATMathDirection _Direction;
   CATBoolean _IsDirection;

   CATBoolean _OutputDisplay;
   
   CATLISTP(CATCrvParam) _SampleCrvPar;
   
   CATAnalysisPtSol * _PointSol;
   CATLONG32        * _AdmSol;
   CATLONG32        _SizeSol;
   CATLONG32        _SizeAllocSol;
   CATLONG32        _IndexSol;
   
   CATLONG32 _Sampling;
   
   CATProjCrvSurDisAdm _AdmissibleAnal;
   
   //========================================================================
   // Gestion CGMReplay
   //========================================================================
protected:
   friend class CATGeoStreamFactory; 

   // private static data
   static CATString _OperatorId;
   static CATGeoOpTimer _Timer;

   static const CATString * GetDefaultOperatorId() { return & _OperatorId; };

public:

   const CATString * GetOperatorId();
   //-----------------------------------------------------------------------
   //- Gestion timer 
   //-----------------------------------------------------------------------  
   CATGeoOpTimer * GetTimer();

   //-----------------------------------------------------------------------
   //- Gestion Mode Record 
   //-----------------------------------------------------------------------  

   CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   void WriteInput(CATCGMStream  & os);
   void WriteOutput(CATCGMStream & os);
   CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
   // dump de l'opérateur
   void Dump( CATCGMOutput& os ) ;
   // dump du resultat du run
   void DumpOutput(CATCGMOutput& os);
   // dump de la reference
   void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
   CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

   void ReadInput(CATCGMStream  & ioStream,int VersionOfstream);
};

#endif
