// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
// Aug 99 Creation                       XGN
//
//=============================================================================
// Usage notes:
//  Abstract class to report parameters on surfaces
//=============================================================================
#ifndef CATSurParamReport_H
#define CATSurParamReport_H

#include "Y30UIUTI.h"

#include "CATCGMOperator.h"

#include "CATMathDef.h"
#include "CATCGMVirtual.h"

class CATSurParam;

class ExportedByY30UIUTI CATSurParamReport : public CATCGMVirtual
{
 public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATSurParamReport () {};
  virtual ~CATSurParamReport() {};

  //-----------------------------------------------------------------------
  //- Report method
  //-----------------------------------------------------------------------
  
  virtual void DirectReport(const CATSurParam & iFromParam, CATSurParam & oToParam)=0;
  // Reverse report
  virtual void ReverseReport(const CATSurParam & iFromParam, CATSurParam & oToParam)=0;
  // automatic report on the CoIsopar
  // Warning : the call to this method is valid only when iFromSurf==iToSurf
  virtual void Report(const CATSurParam & iFromParam, CATSurParam & oToParam)=0;

};

#endif
