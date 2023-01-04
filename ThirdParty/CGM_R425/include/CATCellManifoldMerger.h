#ifndef CATCellManifoldMerger_H
#define CATCellManifoldMerger_H

#include "CATCellManifoldCreator.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATMathInline.h"

class CATCellManifoldsManager;
class CATDomain;
class CATShell;
class CATCell;
class CATLISTP(CATCell);
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);


class ExportedByPersistentCell CATCellManifoldMerger : public CATCellManifoldCreator
{
public:
  CATCGMDeclareManifoldAgent(CATCellManifoldMerger, CATCellManifoldCreator);
	
	// Constructor
  CATCellManifoldMerger();
	
  // Destructor
	virtual ~CATCellManifoldMerger();

  virtual int GetPriority();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  INLINE virtual CATCellManifoldCreator* GetAsCellManifoldCreator();
  INLINE virtual CATCellManifoldMerger* GetAsCellManifoldMerger();

protected:
  virtual void CreateCellManifolds(CATDeclarativeManifoldAgent &iDMAgent, CATDomain &iDomain, CATLISTP(CATCell) &iDomainCells, 
    int iCellsDim, CATLISTP(CATCellManifold) &ioCreatedCellManifolds);

private:
  HRESULT GetConnectedAndConfusedDeclarativeManifold(CATDeclarativeManifold * iDM, CATLiveBody * iInputLiveBody, double iLengthTol, double iAngleTol,
    CATLISTP(CATDeclarativeManifold) &oConnectedAndConfusedDM);
};

INLINE CATDeclarativeManifoldAgent* CATCellManifoldMerger::Clone()
{
  return new CATCellManifoldMerger();
}

INLINE CATCellManifoldCreator* CATCellManifoldMerger::GetAsCellManifoldCreator()
{
  return NULL;
}
INLINE CATCellManifoldMerger* CATCellManifoldMerger::GetAsCellManifoldMerger()
{
  return this;
}

#endif
