#ifndef CATSTypeLaw_h
#define CATSTypeLaw_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATLaw.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSTypeLaw ;
#else
extern "C" const IID IID_CATSTypeLaw ;
#endif


class ExportedByCATGMGeometricInterfaces CATSTypeLaw : public CATLaw
{
  CATDeclareInterface;

public:

  //-------------------------------------------------------------------------
  //- Read the limit constraints.
  //-------------------------------------------------------------------------
  virtual void GetLimitConstraints (double & oTMin,
				    double & oValueAtTMin,
				    double & oTMax,
				    double & oValueAtTMax) const = 0 ;

  //-------------------------------------------------------------------------
  //- Read Null Derivative Order at limit parameters.
  //-------------------------------------------------------------------------
  virtual void GetLimitNullDerivOrder (CATLONG32 & oOrderAtTMin,
				       CATLONG32 & oOrderAtTMax) const = 0 ;

  //-------------------------------------------------------------------------
  //- Change the limit constraints.
  //-------------------------------------------------------------------------
  virtual void SetLimitConstraints (const double iNewTMin,
				    const double iNewValueAtTMin,
				    const double iNewTMax,
				    const double iNewValueAtTMax) = 0 ;

  //-------------------------------------------------------------------------
  //- Change Null Derivative Order at limit parameters.
  //-------------------------------------------------------------------------
  virtual void SetLimitNullDerivOrder (const CATLONG32 iOrderAtTMin,
				       const CATLONG32 iOrderAtTMax) = 0 ;

};
CATDeclareHandler(CATSTypeLaw,CATLaw);

#endif

