#ifndef CATDatumManifoldCarrier_H
#define CATDatumManifoldCarrier_H

#include "CATDeclarativeManifoldCarrierBase.h"
#include "PersistentCell.h"
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


class ExportedByPersistentCell CATDatumManifoldCarrier : public CATDeclarativeManifoldCarrierBase
{
public:
  CATCGMDeclareManifoldAgent(CATDatumManifoldCarrier, CATDeclarativeManifoldCarrierBase);
	
	// Constructor
  CATDatumManifoldCarrier();
	
  // Destructor
	virtual ~CATDatumManifoldCarrier();

  virtual int GetPriority();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  INLINE virtual CATDatumManifoldCarrier * GetAsDatumManifoldCarrier();
};

INLINE CATDeclarativeManifoldAgent* CATDatumManifoldCarrier::Clone()
{
  return new CATDatumManifoldCarrier();
}
INLINE CATDatumManifoldCarrier * CATDatumManifoldCarrier::GetAsDatumManifoldCarrier()
{
  return this;
}
#endif
