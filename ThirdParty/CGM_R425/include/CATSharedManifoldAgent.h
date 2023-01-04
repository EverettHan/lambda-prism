#ifndef CATSharedManifoldAgent_H
#define CATSharedManifoldAgent_H

#include "CATDeclarativeManifoldAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATCollec.h"
#include "CATMathInline.h"

class CATCellManifoldsManager;
class CATCellFollower;
class CATBody;
class CATDomain;
class CATShell;
class CATCell;
class CATLISTP(CATCell);
class CATEdge;
class CATLISTP(CATEdge);
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSetOfCellsParentManifolds;
class CATPAD;


class ExportedByPersistentCell CATSharedManifoldAgent : public CATDeclarativeManifoldAgent
{
public:

  CATCGMDeclareManifoldAgent(CATSharedManifoldAgent, CATDeclarativeManifoldAgent);

	// Constructor
  CATSharedManifoldAgent();
	
  // Destructor
	virtual ~CATSharedManifoldAgent();

  void SetCheckLevel(short iCheckLevel); // 0 : pas de verification, 
                                         // 1 : les cellules appartiennent au body resultat, 
                                         // 2 : niveau 1 + les cellules de dimension <= 1 n'appartiennent pas a plusieurs InputBodies,
                                         // 3 : les cellules appartiennent reportingcells du body resultat
  void SetDeclarativeManifoldsNotToBeShared(ListPOfCATDeclarativeManifold &iDeclarativeManifoldsNotToBeShared);

  virtual HRESULT CreateImageManifolds();
  
  virtual int GetPriority();
  INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();
  INLINE void SetNoSharedCellInInputDomains();

private:
  //HRESULT CreateImageManifoldsWithoutCheck(CATLiveBody &ioOutputLiveBody);
  CATBoolean CellForbidsToShareDM(CATCell* iCell, CATLISTP(CATDomain) & iNewOutDomList);
  //void FillInputDomainsCellsHTable(CATLISTP(CATDomain) & inputDomNotInOutputList);

  CATCGMHashTable * _DeclarativeManifoldsNotToBeSharedHT;
  short _CheckLevel;
  CATCellHashTable*  _OutputBodyCellsHTable;
  CATCellHashTable** _InputDomainsCellsHTable;
  int _NbInputDomains;
  CATBoolean _NoSharedCellInInputDomains;

  //CATPAD ** _PAD; // un PAD par input body
};

INLINE CATBoolean CATSharedManifoldAgent::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return FALSE;
}
INLINE CATDeclarativeManifoldAgent* CATSharedManifoldAgent::Clone()
{
  return new CATSharedManifoldAgent();
}
INLINE void CATSharedManifoldAgent::SetNoSharedCellInInputDomains()
{
  _NoSharedCellInInputDomains = TRUE;
}
#endif
