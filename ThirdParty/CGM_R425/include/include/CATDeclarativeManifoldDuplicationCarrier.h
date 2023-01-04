#ifndef CATDeclarativeManifoldDuplicationCarrier_H
#define CATDeclarativeManifoldDuplicationCarrier_H

//Oct 2013 Creation EYL
#include "CATDeclarativeManifoldCarrierBase.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATCollec.h"
#include "CATMathInline.h"

class CATCellManifoldsManager;
class CATBody;
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);
class CATGeoFactory;
class CATSoftwareConfiguration;


class CATDeclarativeManifoldDuplicationCarrier : public CATDeclarativeManifoldCarrierBase
{
public:
  CATCGMDeclareManifoldAgent(CATDeclarativeManifoldDuplicationCarrier, CATDeclarativeManifoldCarrierBase);
	
	// Constructor
  CATDeclarativeManifoldDuplicationCarrier();
	
  // Destructor
	virtual ~CATDeclarativeManifoldDuplicationCarrier();

  virtual int GetPriority();
  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  INLINE virtual CATDeclarativeManifoldDuplicationCarrier * GetAsDuplicationManifoldCarrier();
};

INLINE CATDeclarativeManifoldAgent* CATDeclarativeManifoldDuplicationCarrier::Clone()
{
  return new CATDeclarativeManifoldDuplicationCarrier();
}
INLINE CATDeclarativeManifoldDuplicationCarrier * CATDeclarativeManifoldDuplicationCarrier::GetAsDuplicationManifoldCarrier()
{
  return this;
}
#endif
