/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATEdgeCurveOffset
//
// Class for offset of an edgecuve (pseudo-object)
//
//===================================================================
//   /12/97     Creation                                      J. Peter
//   /03/98     Add Attribute for PCurve Management           I. Levy
//   /06/98     Lifting (generic method)                      I. Levy
// 12/03/20 Q48 Headers etc for math versioning
//===================================================================

#ifndef CATEdgeCurveOffset_H
#define CATEdgeCurveOffset_H

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

//GeometricObjects libraries
#include "CATCrvParam.h"
#include "CATCrvLimits.h"
#include "CATListOfCATPCurves.h"
#include "CATCGMVirtual.h"

//Other libraries
#include "IUnknown.h"

class CATEdgeCurve;
class CATOffsetSurface;
class CATGeoFactory;
class CATSurface;
class CATPCurve;
class CATMathFunctionX;
class CATSoftwareConfiguration;
class CATMathTransformation2D;

class ExportedByY30C3XGG CATEdgeCurveOffset  : public CATGeoOperator
{

 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATEdgeCurveOffset(      CATGeoFactory    * iFactory,
         CATSoftwareConfiguration * iConfig,
		     const CATEdgeCurve     * iEC,
		     const CATOffsetSurface * iOffSur1,
		     const CATOffsetSurface * iOffSur2 = NULL);

  CATEdgeCurveOffset(      CATGeoFactory * iFactory,
         CATSoftwareConfiguration * iConfig,
         const CATEdgeCurve  * iEC,
		     const CATSurface    * iSurBase1, 
		     const CATSurface    * iSurBase2,
		     const CATSurface    * iSurOff1, 
		     const CATSurface    * iSurOff2);
  
  ~CATEdgeCurveOffset();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  void           SetUsefulLimits (CATCrvLimits & iLimits);

  int            RunOperator();
  
  CATEdgeCurve * GetEdgeCurveOffset();

  void           Report(const CATCrvParam & iParam, CATCrvParam & oParamOffset) const;

  void           ReportPCurve(CATPCurve*  iIn, CATPCurve* &oOut) const;

  short          GetRelativeOrientation() const;

  //-----------------------------------------------------------------------
  //- Post Run diagnostics on EdgeCurveOffset
  //-----------------------------------------------------------------------
  //
  //  Valid:                    Geometric check is OK
  //
  //  EqualExtremReportParams:  Reports from EdgeCurveOffset->RefCurve to OffsetPCurves[i]
  //                            gave equal extreme parameters, with use limits on EdgeCurveOffset
  //
  //  Unknown:                  Geometric check failed to return a pertinent diagnostic, or no check
  //                            has been performed
  //
  //
  enum CATEdgeCurveOffsetDiag {Unknown = -1, Valid, EqualExtremReportParams}; // to be continued

  //
  //  CheckECOffset()
  //
  //  Performs a check a posteriori on computed EdgeCurveOffset and returns a CATEdgeCurveOffsetDiag
  //
  CATEdgeCurveOffsetDiag CheckECOffset();

  //-----------------------------------------------------------------------
  //- Do not use
  //-----------------------------------------------------------------------
  CATEdgeCurve * CreateEdgeCurve();

private:

  int RunOperator1();
  int RunOperator2();
  // Re initialiser les donnees de l operateur
  void Initialisation();

  void Report1(const CATCrvParam & iParam, CATCrvParam & oParamOffset) const;
  void Report2(const CATCrvParam & iParam, CATCrvParam & oParamOffset) const;

  void ReportPCurve1(CATPCurve*  iIn, CATPCurve* &oOut) const;
  void ReportPCurve2(CATPCurve*  iIn, CATPCurve* &oOut) const;

  HRESULT OffsetPCurves(CATCloneManager & CM, short & NbOtherCurves);
  HRESULT OffsetEdgeCurve(CATCloneManager & CM, short NbOtherCurves);
  HRESULT SetUpForReport();
  HRESULT OffsetEdgeCurveByCloneAndSimplify(CATCloneManager & CM, short NbOtherCurves);
  HRESULT OffsetEdgeCurveByECC(CATCloneManager & CM, short NbOtherCurves);
  HRESULT OffsetPCByCloneAndMovePCurve(CATPCurve * PC, const CATCrvLimits & MyMaxLimits,
                                       double tol, CATPCurve *& PCO);
/*  HRESULT OffsetPCByTransfoManager(CATPCurve * PC, const CATCrvLimits & MyMaxLimits,
                                   double tol, CATPCurve *& PCO);*/
  short FatEdgeDetection(CATPCurve * PC);

  CATMathTransformation2D * IsNonisoparametricOffset(CATSurface * OffsetSurf, CATSurface *iRefSurf=NULL);

  // BQJ - Post Run method: if EdgeCurve offset has been computed by a clone 
  // operation this method checks if its maximum gap does not exceeds maximum
  // gap allowed ( = 0.1 ).
  // If so, it unextrapolates each of its components curves' mapping so has to
  // fit with UseLimits.
  void CheckMaxGapAndUnextrapolate();

  //-----------------------------------------------------------------------
  //- Data
  //-----------------------------------------------------------------------

  CATGeoFactory      * _Factory;
  CATEdgeCurve       * _ECrv, * _ECrvOffset, * _OldECOToRemove;
  CATPCurve          * _ECORep, * _ECORepSrc;
  CATSurface         * _OffSur1;
  CATSurface         * _OffSur2;
  CATSurface         * _RefSur1, * _RefSur2;
  CATMathFunctionX   * _Mapping;
  CATLISTP(CATPCurve)  _ListOfPCurves;
  CATLISTP(CATPCurve)  _ListOfOffsetPCurves;
  CATLISTP(CATPCurve)  _ListOfIgnoredPCurves;
  CATLISTP(CATPCurve)  _ListOfIgnoredPCurvesOffset;
  CATCrvLimits         _UseLimits;

  CATSoftwareConfiguration * _Config;

  CATMathTransformation2D * _Nonisoparametric[2];

  // *** Internal data dedicated to RunOperator2 (see EdgeCurveOffset_Level1) ***

  // OffsetEdgeCurveMethod
  // Gives an information on the method used to compute the edge curve offset:
  //      0 = no method launched or error during computation (default value)
  //      1 = EdgeCurveComputation method which takes account of _UseLimits
  //      2 = CreateSimCurve method (_UseLimits not managed)
  //      3 = CloneManager method (_UseLimits not managed)
  CATLONG32 _OffsetEdgeCurveMethod;
  
  // EdgeCurveOffset max gap
  double _ECOGap; // default value = -1. if not stored
  
  // ****************************************************************************

  //Attribute internal data
  int _AttrKey ;
  int _AttrLgth ;

  // CGMReplay integration
protected:
  friend class CATGeoStreamFactory; 
  static CATString _OperatorId;

public:
	const CATString * GetOperatorId();
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);


};


#endif
