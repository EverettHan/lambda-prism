#ifndef CATIPGMShellFromClosedWire_h_
#define CATIPGMShellFromClosedWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"

class CATBody;
class CATCGMJournalList;
class CATFace;
class CATGeoFactory;
class CATSurface;
class CATWire;
class EdgeFSFCW;
class LoopFSFCW;
class CATLISTP(CATSurface);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMShellFromClosedWire;

class ExportedByCATGMOperatorsInterfaces CATIPGMShellFromClosedWire: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMShellFromClosedWire();

  virtual int Run() = 0;

  //
  // this method is deprecated use SetCheckAutocrossing
  // Return number of auto - crossing problem found ( 0 if no auto crossing ).
  //
  // If this method is called before the "GetResult()" method and after the "Run()" method, 
  // in some situation the body can be repared 
  // ( In this case method return 0 , but warning can be output on demand ).
  //
  virtual CATLONG32 CheckAutoCrossing() = 0;

  //
  // To be called before run for modelisation organisation.
  //
  // It allows the computation of autocrossing during the Run method. It can 
  // repair the result
  // if this activated, the number of autocrossing can get after run
  // iAutoCrossing = 3 check on input with repair and inactivate the treatment
  //                 2 check on result without repair
  //                 1 check on result with repair of result
  //                 0 inactivated 
  //                 else error
  //
  virtual void SetCheckAutoCrossing(CATLONG32 iAutoCrossing) = 0;

  //
  // To be called after run .
  //
  // Get the number of autocrossing detected if setCheckAutoCrossing is activated
  //
  virtual CATLONG32 GetNbAutoCrossing() = 0;

  virtual void CheckBodyValidity(const CATBody *iBody) = 0;

  virtual CATBody *GetResult() = 0;

  virtual void Get_surfaces(CATLISTP(CATSurface) &SurfacesList) = 0;

  virtual void GetListOfWires(CATLISTP(CATBody) &WireBodiesList) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMShellFromClosedWire(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMShellFromClosedWire *CATPGMCreateShellFromClosedWire(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATBody *iBody,
  const CATSurface *iSupport);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMShellFromClosedWire *CATPGMCreateShellFromClosedWire(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) *iBodies,
  CATLISTP(CATSurface) *iSupports);

#endif /* CATIPGMShellFromClosedWire_h_ */
