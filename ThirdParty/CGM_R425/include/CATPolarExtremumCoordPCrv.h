//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//
// CATPolarExtremumCoordPCrv:
//  
//
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================

#ifndef CATPolarExtremumCoordPCrv_H
#define CATPolarExtremumCoordPCrv_H

// ExportedBy
#include "Y30C1XMM.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCrvLimits.h"
#include "CATSurParam.h"
#include "CATMathVector2D.h"
#include "CATMathInterval.h"

#include "CATBoolean.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"

class CATGeoFactory;
class CATPCurve;
class CATPlane;
class CATSoftwareConfiguration;


class ExportedByY30C1XMM CATPolarExtremumCoordPCrv : public CATGeoOperator
{
   public:
      //-------------------------
      // Object Management
      //-------------------------
      CATPolarExtremumCoordPCrv(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig,
                                CATPCurve *iPCrv, CATCrvLimits &iCrvLimits,
                                CATPlane *iPlaneSupport, CATSurParam &iOrigin,
                                CATMathVector2D &iDirection);

      ~CATPolarExtremumCoordPCrv();

      //-------------------------
      // Set Methods
      //-------------------------
      void SetAllMode();
      void SetRadiusMinMode(CATBoolean iMode = TRUE);
      void SetRadiusMaxMode(CATBoolean iMode = TRUE);
      void SetAngleMinMode(CATBoolean iMode = TRUE);
      void SetAngleMaxMode(CATBoolean iMode = TRUE);


      //-------------------------
      // Run
      //-------------------------
      int RunOperator();

      //-------------------------
      // Get Methods
      //-------------------------
      double GetRadiusMin(CATCrvParam &ioResultParam);
      double GetRadiusMax(CATCrvParam &ioResultParam);
      double GetAngleMin(CATCrvParam &ioResultParam);
      double GetAngleMax(CATCrvParam &ioResultParam);


      //========================================================================
      // Gestion CGMReplay
      //========================================================================

      const CATString * GetOperatorId();
      //-----------------------------------------------------------------------
      //- Gestion timer 
      //-----------------------------------------------------------------------  
      CATGeoOpTimer * GetTimer();

      //-----------------------------------------------------------------------
      //- Gestion Mode Record 
      //-----------------------------------------------------------------------  

      CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
      virtual void WriteInput(CATCGMStream  & ioStream);
      virtual void WriteOutput(CATCGMStream & ioStream);
      virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
      virtual void Dump( CATCGMOutput& os ) ;
      virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
      //virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & ioStream);
      //virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & ioStream);

protected:
      int RunRadius();
      int RunAngle();

      int ComputeISide(const CATMathInterval& domain, CATLONG32& iSide);

      friend class CATGeoStreamFactory;
private:

      int RunAnglePCircle();
      void ComputeSamplingOnArc(int &nbSample,double *&SampleParam);


      //-------------------------
      // Data
      //-------------------------

   protected :
  //  static data
      static CATString _OperatorId;
      static CATGeoOpTimer _Timer;

   private:
      // Input Data
      CATSoftwareConfiguration *_Config;

      CATPCurve    * _PCrv;
      CATCrvLimits   _CrvLimits;
      CATPlane     * _PlaneSupport;
      CATSurParam    _Origin;
      CATMathVector2D _DirectionIN;
      CATMathVector2D _Direction;

      // Mode
      CATBoolean _RadiusMinMode;
      CATBoolean _RadiusMaxMode;
      CATBoolean _AngleMinMode;
      CATBoolean _AngleMaxMode;

      // OutPut
      double _RadiusMinVal;
      double _RadiusMaxVal;
      double _AngleMinVal;
      double _AngleMaxVal;
      CATCrvParam _RadiusMinPar;
      CATCrvParam _RadiusMaxPar;
      CATCrvParam _AngleMinPar;
      CATCrvParam _AngleMaxPar;

      // working data
      double LowVal, HighVal;
      CATMathInterval Domain;
      const CATTolerance & tol ;
      double _PlaneScale;   // Scale du plan support
      double _MaxRadius;

      //debug visu
      CATBoolean _DEBUG_GeoOfReferenceResultCreated;
   };

#endif

