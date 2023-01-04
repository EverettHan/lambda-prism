#ifndef CATIPGMFrFConvertCCVToWire_h_
#define CATIPGMFrFConvertCCVToWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATBoolean.h"

class CATBody;
class CATGeoFactory;
class CATWire;
class CATTopData;
class CATFrFCompositeCurve;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFrFConvertCCVToWire;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMFrFConvertCCVToWire: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFConvertCCVToWire();

  virtual void Run() = 0;

  //  Getting the Wire result  
  virtual CATWire *GetWire() const = 0;

  //  Getting the Body result  
  virtual CATBody *GetBody() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFConvertCCVToWire(); // -> delete can't be called
};

// there are to ways to make a body with several domains:
// iMaxGapInDomain : if positive, a new domain is generated when 
// gap between consecutive curves is superior to iMaxGapInDomain
// iRefBody : if  exists, describes topology to be obtained
// (output wire will have same number of domains and same number
// of cells in each domain)
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFConvertCCVToWire *CATPGMCreateFrFConvertCCVToWire(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATFrFCompositeCurve *iCCV,
  CATBoolean iFreezeMode = CATBoolean(1),
  double iMaxGapInDomain = -1.,
  CATBody *iRefBody = NULL);

#endif /* CATIPGMFrFConvertCCVToWire_h_ */
