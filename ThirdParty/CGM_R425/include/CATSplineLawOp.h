//==========================================================================
//
// CATSplineLawOp : 
//                    
//                    
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
//   /02/05 CWM Creation
// 20/03/20 Q48 Headers etc for math versioning
//========================================================================== 

#ifndef CATSplineLawOp_H
#define CATSplineLawOp_H

// ExportedBy
#include "Connect.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSplineLaw.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"

#include "CATMathSetOfLongs.h"
#include "CATMathSetOfPointsND.h"
#include "CATUnicodeString.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
//-----------------------------------------------------------------------------
class ExportedByConnect CATSplineLawOp : public CATGeoOperator
{    
public:
  ~CATSplineLawOp();

  CATSplineLawOp(CATGeoFactory * iFactory, 
                               CATSoftwareConfiguration * iConfig,
                               const CATLONG32 iNbrOfParameters, 
                               const CATLONG32 iClosed, 
                               const CATLONG32 iRadiusLawMode);

  CATSplineLawOp(CATGeoFactory * iFactory, 
                 CATSoftwareConfiguration * iConfig,
                 const CATLONG32 iNbrOfParameters, 
                 const double *iParams,
                 const double *iValues, 
                 const CATLONG32 iClosed, 
                 const CATLONG32 iRadiusLawMode);
  void SetPoint(const CATLONG32 iIndex, const double iParam, const double iValue);
  void SetTangent(const CATLONG32 iIndex, const double iTangent, const CATLONG32 iImpos = 1);
  void SetSecondDerivative(const CATLONG32 iIndex, const double iSecondDeriv, const CATLONG32 iImpos = 1);
  CATSplineLaw * GetSplineLaw();
  void SetContinuityMode(int iMode);
  void InsertData(const CATLONG32 iIndex, const double iParam, const double iValue, const double iTangent = 0, const CATLONG32 iTanImpos = 0,const double iSecondDeriv = 0, const CATLONG32 iSecImpos = 0);

  int RunOperator();
    
private:
  void Init();
  void Initialize(int iSize);

  void SetSplineLaw(CATSplineLaw * iLaw);
  void FindMonotoneAreas(void);
  int ComputeDerivatives(void);
  void MediateImpositions(double iValLeft, double iValRight, double * ioMediatedValue);
  void ComputeMidData(int iIndex, int iDirection, double ioData[4]);
 
  void SetDataArrays();
  void DisplayDataArraysTrace(CATUnicodeString iMessage);

  CATSoftwareConfiguration * _Config;
  
  CATLONG32 _NbrOfParameters;
  double * _Parameters;
  double * _Values;
  double * _Tangents;
  double * _SecondDerivatives;
  CATLONG32 * _TangentImpositions;
  CATLONG32 * _SecondDerivImpositions;

  CATMathSetOfPointsND * _SetOfParameters;
  CATMathSetOfPointsND * _SetOfValues;
  CATMathSetOfPointsND * _SetOfTangents;
  CATMathSetOfPointsND * _SetOfSecondDerivatives;
  CATMathSetOfLongs * _SetOfTangentImpositions;
  CATMathSetOfLongs * _SetOfSecondDerivImpositions;

  CATLONG32 _IsClosed;
  CATLONG32 _RadiusLawMode;
 CATBoolean _DataArraysSet;

  CATSplineLaw  *_SplineLaw;

  // pour CGMReplay on doit "bufferiser" les impositions externes

  int _ContinuityMode;


//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

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
  void WriteInput(CATCGMStream  & ioStream);
  void WriteOutput(CATCGMStream & ioStream);
  CATBoolean ValidateOutput(CATCGMStream& ioStream,CATCGMOutput &os,int VersionNumber=1);
  void Dump( CATCGMOutput& os ) ;
  void DumpOutput(CATCGMOutput& os);
  void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};
#endif
