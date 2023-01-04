/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATCrvContAnalysis :
//=============================================================================
//=============================================================================
// Feb 03  Creation                          AAD
// Oct 03  Move to GeometricObjects          PKC 
//=============================================================================
#ifndef CATCrvContAnalysis_H 
#define CATCrvContAnalysis_H 

#include "CATContinuityQuery.h"
#include "YP00IMPL.h"

class CATCrvParam;
class CATSoftwareConfiguration;

class ExportedByYP00IMPL CATCrvContAnalysis
{
public :
  virtual ~CATCrvContAnalysis();
  virtual void SetMaxLevel(CATContinuityQuery::ContinuityLevel iMaxLevel) = 0;
  virtual void Set2DAnalysis() = 0;
  virtual void SetValueComputation() = 0;
  virtual void SetConfusionTolerance(double iTol) = 0;
  virtual void SetNoDiscontinuityOnProcCurve() = 0;
  virtual int Run() = 0;
  virtual void GetMaxDiscontinuity(CATContinuityQuery::ContinuityLevel & oLevel, CATCrvParam & oParam, double & oValue) = 0;
  virtual int GetNbDiscontinuities() = 0;
  virtual void GetDiscontinuity(int iRank, CATContinuityQuery::ContinuityLevel & oLevel, CATCrvParam & oParam, double & oValue) = 0;
  
  
protected:
  CATCrvContAnalysis();
  
private:
  CATCrvContAnalysis(const CATCrvContAnalysis &);
  void operator = (const CATCrvContAnalysis &);
  
};

ExportedByYP00IMPL
CATCrvContAnalysis * CATCreateCrvContAnalysis(CATSoftwareConfiguration * iSoftwareConfiguration, 
                                              const CATCurve * iCurve, const CATCrvLimits & iLimits);


#endif


