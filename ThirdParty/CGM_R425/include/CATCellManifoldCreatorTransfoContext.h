#ifndef CATCellManifoldCreatorTransfoContext_H
#define CATCellManifoldCreatorTransfoContext_H

#include "CATDeclarativeManifoldAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATListOfInt.h"
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
class CATCGMHashTable;


class ExportedByPersistentCell CATCellManifoldCreatorTransfoContext : public CATDeclarativeManifoldAgent
{
public:

  CATCGMDeclareManifoldAgent(CATCellManifoldCreatorTransfoContext, CATDeclarativeManifoldAgent);
	
	// Constructor
  CATCellManifoldCreatorTransfoContext();
	
  // Destructor
	virtual ~CATCellManifoldCreatorTransfoContext();

  virtual HRESULT CreateImageManifolds();
  virtual int GetPriority();
  INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();
};

INLINE CATBoolean CATCellManifoldCreatorTransfoContext::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return FALSE;
}
INLINE CATDeclarativeManifoldAgent* CATCellManifoldCreatorTransfoContext::Clone()
{
  return new CATCellManifoldCreatorTransfoContext();
}
/*
INLINE CATCellManifoldCreatorTransfoContext* CATCellManifoldCreatorTransfoContext::GetAsCellManifoldCreator()
{
  return this;
}
*/

#endif
