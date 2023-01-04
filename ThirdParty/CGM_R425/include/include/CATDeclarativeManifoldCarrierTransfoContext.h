#ifndef CATDeclarativeManifoldCarrierTransfoContext_H
#define CATDeclarativeManifoldCarrierTransfoContext_H

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
class CATCell;
class CATLISTP(CATCell);
class CATGeoFactory;
class CATSoftwareConfiguration;


class CATDeclarativeManifoldCarrierTransfoContext : public CATDeclarativeManifoldCarrierBase
{
public:
  CATCGMDeclareManifoldAgent(CATDeclarativeManifoldCarrierTransfoContext, CATDeclarativeManifoldCarrierBase);

	// Constructor
  CATDeclarativeManifoldCarrierTransfoContext();
	
  // Destructor
  virtual ~CATDeclarativeManifoldCarrierTransfoContext();

  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone();
  INLINE void SetCreationMode(CATBoolean iCreationMode);

  virtual CATDeclarativeManifoldCarrierTransfoContext * GetAsDeclarativeManifoldCarrierTransfoContext();

private:
  CATBoolean _CreationMode;
};
// EYL : Sorry, I didn't find better way to choose between modificaiton and creation. 
// Do not forget to reset it ti FALSE after use 
INLINE void CATDeclarativeManifoldCarrierTransfoContext::SetCreationMode(CATBoolean iCreationMode)
{
  _CreationMode=iCreationMode;
}
#endif
