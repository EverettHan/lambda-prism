/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATSurContAnalysis :
//=============================================================================
//=============================================================================
// Feb 03  Creation                          AAD
// Oct 03  Move to GeometricObjects          PKC 
//=============================================================================
#ifndef CATSurContAnalysis_H 
#define CATSurContAnalysis_H 

#include "CATContinuityQuery.h"
#include "YP00IMPL.h"

class CATSurParam;
class CATSoftwareConfiguration;

class ExportedByYP00IMPL CATSurContAnalysis
{
public :
  virtual ~CATSurContAnalysis();
  virtual void SetMaxLevel(CATContinuityQuery::ContinuityLevel iMaxLevel) = 0;
  virtual void SetIsoParameter(CATIsoParameter iIsoParameter) = 0;
  virtual void SetValueComputation() = 0;
  virtual void SetConfusionTolerance(double iTol) = 0;
  virtual void SetNoDiscontinuityOnProcSurface() = 0;
  virtual int Run() = 0;
  virtual void GetMaxDiscontinuity(CATIsoParameter iIsoParameter, CATContinuityQuery::ContinuityLevel & oLevel, 
                                   CATSurParam & oParam, double & oValue) = 0;
  virtual int GetNbDiscontinuities(CATIsoParameter iIsoParameter) = 0;
  virtual void GetDiscontinuity(CATIsoParameter iIsoParameter, int iRank, 
                                CATContinuityQuery::ContinuityLevel & oLevel, CATSurParam & oParam, double & oValue) = 0;
  
protected:
  CATSurContAnalysis();
  
private:
  CATSurContAnalysis(const CATSurContAnalysis &);
  void operator = (const CATSurContAnalysis &);
  
};

ExportedByYP00IMPL
CATSurContAnalysis * CATCreateSurContAnalysis(CATSoftwareConfiguration * iSoftwareConfiguration, const CATSurface * iSurface, const CATSurLimits & iLimits);


#endif


