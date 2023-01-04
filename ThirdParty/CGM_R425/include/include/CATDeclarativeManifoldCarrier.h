#ifndef CATDeclarativeManifoldCarrier_H
#define CATDeclarativeManifoldCarrier_H

#include "CATDeclarativeManifoldCarrierBase.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATDeclarativeManifold.h"
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


class ExportedByPersistentCell CATDeclarativeManifoldCarrier : public CATDeclarativeManifoldCarrierBase
{
public:
  CATCGMDeclareManifoldAgent(CATDeclarativeManifoldCarrier, CATDeclarativeManifoldCarrierBase);

	// Constructor
  CATDeclarativeManifoldCarrier();
	
  // Destructor
	virtual ~CATDeclarativeManifoldCarrier();

  virtual int GetPriority();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  INLINE virtual CATDeclarativeManifoldCarrier * GetAsDeclarativeManifoldCarrier();
};

INLINE CATDeclarativeManifoldAgent* CATDeclarativeManifoldCarrier::Clone()
{
  return new CATDeclarativeManifoldCarrier();
}
INLINE CATDeclarativeManifoldCarrier * CATDeclarativeManifoldCarrier::GetAsDeclarativeManifoldCarrier()
{
  return this;
}
#endif
