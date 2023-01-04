//===================================================================
// COPYRIGHT Dassault Systemes 2011
//===================================================================
// CATCDMContinuity.h
//===================================================================
//
//

//===================================================================
#ifndef CATCDMContinuity_H
#define CATCDMContinuity_H

#include "CATCDMBaseInterfaces.h"
#include "CATBaseUnknown.h"

class ExportedByCATCDMBaseInterfaces CATCDMContinuity
{
public:

  enum ContinuityType {
    Undefinied = 0
    ,G0
    ,G1
    ,G2
  };

  // Standard constructors and destructors
  // -------------------------------------
  CATCDMContinuity ();
  CATCDMContinuity (ContinuityType ContinuityTypeValue, double Tolerance);
  virtual ~CATCDMContinuity ();


  HRESULT GetContinuityType (CATCDMContinuity::ContinuityType & oContType);
  HRESULT GetContinuityTolerance (double & oTolerance);

  HRESULT SetContinuityType(CATCDMContinuity::ContinuityType iContinuityTypeValue);
  HRESULT SetContinuityTolerance(double iTolerance);


  // Copy constructor and equal operator
  // -----------------------------------
  CATCDMContinuity (const CATCDMContinuity &);
  CATCDMContinuity& operator=(const CATCDMContinuity &);
  bool operator==(const CATCDMContinuity & iContinuityValue);
  bool operator!=(const CATCDMContinuity & iContinuityValue);

private:


  double					_Tolerance;
  ContinuityType	_ContType;
};

#endif
