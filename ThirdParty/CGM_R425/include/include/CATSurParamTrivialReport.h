// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
// Aug 99 Creation                       XGN
//
//=============================================================================
// Usage notes:
//  Abstract class to report parameters on surfaces
//=============================================================================
#ifndef CATSurParamTrivialReport_H
#define CATSurParamTrivialReport_H

#include "Y30A3HGG.h"

#include "CATCGMOperator.h"

#include "CATMathDef.h"

#include "CATIsoParameter.h"
#include "CATSurParamReport.h"

class CATSurface;
class CATSurParam;

class ExportedByY30A3HGG CATSurParamTrivialReport : public CATSurParamReport
{
 public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATSurParamTrivialReport (CATSurface * iFromSurf, CATSurface * iToSurf,
                            const CATIsoParameter iIsopar,
                            const double iVarFrom, const double iVarTo);
  virtual ~CATSurParamTrivialReport();

  //-----------------------------------------------------------------------
  //- Report method
  //-----------------------------------------------------------------------

  // Report from isopar iIsopar==iVarFrom on iFromSurf to iIsopar==iVarTo on iToSurf
  virtual void DirectReport(const CATSurParam & iFromParam, CATSurParam & oToParam);
  // Reverse report
  virtual void ReverseReport(const CATSurParam & iFromParam, CATSurParam & oToParam);
  // automatic report on the CoIsopar
  // Warning : the call to this method is valid only when iFromSurf==iToSurf
  virtual void Report(const CATSurParam & iFromParam, CATSurParam & oToParam);

protected:
  CATSurface * _FromSurf, * _ToSurf;
  CATIsoParameter _Isopar;
  double _VarFrom, _VarTo;
};

#endif

