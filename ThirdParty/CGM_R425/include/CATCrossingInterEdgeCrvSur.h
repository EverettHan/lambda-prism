// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCrossingInterEdgeCrvSur :
// Class for crossing intersections between an EdgeCurve and a Surface used
// by the Shell and Thickness operators
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
//   /01/99     Creation                                 X. Gourdon
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

#ifndef CATCrossingInterEdgeCrvSur_H
#define CATCrossingInterEdgeCrvSur_H

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATMathDef.h"
#include "CATIntersectionSign.h"
#include "CATCreateCrossingInterEdgeCrvSur.h"

class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATSoftwareConfiguration;

#include "CATSurParam.h"
#include "CATCrvParam.h"
#include "CATSurLimits.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATExtCGMReplay.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"

struct CrossingPointStock
{
  CATSurParam * SurParam;
  CATCrvParam * CrvParam;
  CATPointOnEdgeCurve * POEC;
  CATIntersectionSign Signature;
};

struct ConfusionStock
{
  CATPCurve * PCrv;
  CATEdgeCurve * EdgeCrv;
  CATSurParam StartSurParam, EndSurParam;
  CATPointOnEdgeCurve * StartPOEC, * EndPOEC;
  CATPointOnEdgeCurve * RelatedStartPOEC, * RelatedEndPOEC;
};

class ExportedByY30C3XGG CATCrossingInterEdgeCrvSur : public CATGeoOperator
{

public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  CATCrossingInterEdgeCrvSur(CATGeoFactory * iFactory,
                             CATSoftwareConfiguration * iConfig,
                             CATEdgeCurve * iECrv, 
                             CATPointOnEdgeCurve * iStartPOEC,
                             CATPointOnEdgeCurve * iEndPOEC,
                             CATSurface * iSurface,
                             CATSurLimits & iSurLimits);
      
  ~CATCrossingInterEdgeCrvSur();
  
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  // Setting methods
  void SetAllConfusions(CATBoolean iAllConfusions=1);
  void SetTolerance(const double iTolerance);
	//
	// Pour Perfos, Ne pas lancer le ComputeMaxGap
	//
	void SetComputeMaxGap();
  void SetExtremityAdjust(CATBoolean iAdjust=1);
  void SetBorderSolutions(CATBoolean iBorderSolution=1);
  
  // Getting crossing point solution
  void BeginningPoint();
  
  CATBoolean NextPoint();
  CATPointOnEdgeCurve * GetPointOnEdgeCurve();
  // Get the SurParam with respect to a given subcurve of the EdgeCurve,
  // get the associated CrvParam in oCrvParamOnComponent if not null. 
  void GetSurParam(CATCurve * iComponent, CATSurParam & oSurParam, CATCrvParam * oCrvParamOnComponent=0);
  // Get the signature with respect to the EdgeCurve orientation
  CATIntersectionSign  GetSignature() const;
  //
  // Error handling methods
  //
  void CheckIndexConfusion(char * iMethod) const;
  // Getting confusion between admissible solutions 
  // (not between crossing solution)
  void BeginningCurve();
  CATBoolean NextCurve();
  CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve *& oStart,
                              CATPointOnEdgeCurve *& oEnd);
  CATPCurve * GetPCurve();
  // Return the POEC on the input EdgeCurve in the same order as the POECs in
  // the GetEdgeCurve method
  void GetRelatedInit(const CATPointOnEdgeCurve * & oStart, 
                      const CATPointOnEdgeCurve * & oEnd) const;
  void GetExtremitiesOnSurface(CATSurParam & oSurParamStart,
                               CATSurParam & oSurParamEnd) const;
  
  // Running the operator
  int RunOperator();


  CATBoolean IsMixedSolution();// = 1 when a mixed solution has been found 
  void SetMixedSolutionsTreatment();// Special Treatment for Booleen (Not Eliminate Mixed Solutions)
  CATLONG32 GetNumberOfCurves  () const;
  // Returns 1 is a confusion exists, independantly of the length of the curves
  CATBoolean GetTotalConfusion() const;
  //-----------------------------------------------------------------------
  //- Private Methods
  //-----------------------------------------------------------------------
private:

  
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
private:
  
  CATEdgeCurve * _ECrv;
  CATPointOnEdgeCurve * _StartPOEC, * _EndPOEC;
  CATSurface * _Surf;
  CATSurLimits _SurLim;

  // Parameters
  CATBoolean _ExtremityAdjust;
	CATBoolean _BorderSolutions;
  double _Tolerance;
  CATBoolean _AllConfusions, _ComputeMaxGap;
  CATBoolean _TotalConfusion;
  // Data for output
  CATLONG32 _NbSubCrv;
  const CATCurve ** _SubCrv;

  CATLONG32 _NbPointSol, _NbConfusionSol;
  CrossingPointStock * _PointSol;
  ConfusionStock * _ConfusionSol;
  CATSoftwareConfiguration * _Config;

  CATLONG32 _IndexPoint, _IndexConfusion;  
  CATBoolean _MixedSolution; // = 1 when a mixed solution has been found 
  CATBoolean _MixedSolutionTreatment; // Special Treatment for CATCrossingInterEdgeCrvSur.

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
