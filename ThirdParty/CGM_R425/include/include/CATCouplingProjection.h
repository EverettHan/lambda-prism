// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATCouplingProjection :
// Class for coupling Projection between an EdgeCurve and a Shell
//
//=============================================================================
// Usage notes:
//
//=============================================================================
//   /12/05 RHA Creation
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================
#ifndef CATCouplingProjection_H
#define CATCouplingProjection_H

// ExportedBy
#include "Y30E3PMG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

// FRAMEWORK Other
// Mathematics
#include "CATCGMVirtual.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"

// Geometric Objects
#include "CATGeoDef.h"

// SpecialAPI
#include "CATDataType.h"

class CATPCurve;
class CATGeoFactory;
class CATPointOnEdgeCurve;
class CATEdgeCurve;
class CATMathDirection;
class CATSoftwareConfiguration;
class CATCurveParam;
class CATCurveLimits;

class ExportedByY30E3PMG CATCouplingProjection  : public CATGeoOperator
{
public:

   //-----------------------------------------------------------------------
   //- Object management
   //-----------------------------------------------------------------------

   CATCouplingProjection(CATGeoFactory * iFactory,
                         CATSoftwareConfiguration * iConfig,
                         CATEdgeCurve * iECrvToProject,
                         CATPointOnEdgeCurve * iPOEC_Init1_ECrv_ToProject,
                         CATPointOnEdgeCurve * iPOEC_Init2_ECrv_ToProject,
                         CATEdgeCurve * iECrv_Bord,
                         CATPointOnEdgeCurve * iPOEC_Init1_Bord,
                         CATPointOnEdgeCurve * iPOEC_Init2_Bord,
                         CATPCurve * iBord1,
                         CATPCurve * iBord2,
                         CATMathDirection  *iDirection );


   ~CATCouplingProjection();

   //-----------------------------------------------------------------------
   //- Public Methods
   //-----------------------------------------------------------------------

   //-----------------------------------------------------------------------
   //- Running the operator
   //-----------------------------------------------------------------------
   int  RunOperator();
   //-----------------------------------------------------------------------
   //- Reading the results
   //-----------------------------------------------------------------------
   //
   // Returns TRUE if points are considered as coupled, FALSE else
   //
   CATBoolean GetCoupling();
   // If points are coupled and a Edge curve should be created between the two input
   // POECS, return this EdgeCurve together with the TwoPCurve 
   // 0 is returned if no such EdgeCurve exists.
   CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd);
   //
   // Give the Correspondant POEC in the EdgeCurve To project 
   //
   CATPointOnEdgeCurve * GetPOECToProject();
   //
   // Setting method
   //
   void SetLimits(CATEdgeCurve * iEdgeCurve, CATPointOnEdgeCurve * iStartPOEC, CATPointOnEdgeCurve * iEndPOEC);
    
private:

   //-----------------------------------------------------------------------
   //- Private data
   //-----------------------------------------------------------------------

   CATGeoFactory * _Factory;
   CATSoftwareConfiguration * _Config;
   CATEdgeCurve * _ECrvToProject;
   CATPointOnEdgeCurve * _POEC1_ToProject, * _POEC2_ToProject;

   CATPointOnEdgeCurve * _POEC1_Bord, *_POEC2_Bord, *_POEC_Conv_Bord, *_POEC_Conv_ToProject;
   CATEdgeCurve * _ECrvBord;
   CATPCurve * _Bord1, *_Bord2;
   CATMathDirection  _Direction;
   CATBoolean _isDirection;

   CATBoolean _Coupling,  _MergedCurveToCreate;
   CATPointOnEdgeCurve * _LimECrvToProject[2];
   CATPointOnEdgeCurve * _LimECrv_Bord[2];
   //-----------------------------------------------------------------------
   //- Private methods
   //-----------------------------------------------------------------------
   // Original computation based on Projection on Surface
   CATBoolean TestCoupling();
   CATBoolean TestBetweenTwoPOEC(short            & iCGMLevel             ,
                                 CATCrvLimits     & iMaxLim1              ,
                                 CATCrvLimits     & iMaxLimBord1          ,
                                 CATCrvLimits     & iMaxLimBord2          ,
                                 CATCrvParam        iCrvParam_ToProject[2],
                                 CATCrvParam        iCrvParam_Border1  [2],
                                 CATCrvParam        iCrvParam_Border2  [2]);

   CATBoolean TestFromOnePOEC   (short            & iCGMLevel             ,
                                 CATLONG32          iIdPOEC               ,
                                 CATCrvLimits     & iMaxLim1              ,
                                 CATCrvLimits     & iMaxLimBord1          ,
                                 CATCrvLimits     & iMaxLimBord2          ,
                                 CATCrvParam      & iCrvParam_ToProject   ,
                                 CATCrvParam      & iCrvParam_Border1     ,
                                 CATCrvParam      & iCrvParam_Border2     );

   // New computation based on ProjectionCrvCrv
   CATBoolean RunCoupling();
   
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

   //-----------------------------------------------------------------------
   //- Gestion timer 
   //-----------------------------------------------------------------------  
   CATGeoOpTimer * GetTimer();
   const CATString * GetOperatorId();

   //-----------------------------------------------------------------------
   //- Gestion Mode Record 
   //-----------------------------------------------------------------------  

   CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   void WriteInput(CATCGMStream  & os);
   void WriteOutput(CATCGMStream & os);
   CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
   CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
   // dump de l'opérateur
   void Dump( CATCGMOutput& os ) ;
   // dump du resultat du run
   void DumpOutput(CATCGMOutput& os);
   // dump de la reference
   void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
   void ReadInput(CATCGMStream  & ioStream,int VersionOfstream);
};

#endif
