#ifndef CATAgentRelationNode_H
#define CATAgentRelationNode_H

#include "CATCGMVirtual.h"
#include "CATPersistentCell.h"
#include "ListPOfCATAgentRelationNode.h"
#include "CATManifoldNavigator.h"
#include "CATDeclarativeType.h"


class ExportedByPersistentCell CATAgentRelationNode : public CATCGMVirtual
{
public:
  // Constructor
  CATAgentRelationNode(CATDeclarativeType iType);
  // Destructor
  virtual ~CATAgentRelationNode();
  void GetForbiddendNodes(ListPOfCATAgentRelationNode &ioForbiddenNodes);
  void GetMandatoryNodes(ListPOfCATAgentRelationNode &ioMandatoryNodes);
  CATBoolean IsCompatible(CATAgentRelationNode &NodeToTest);
  CATDeclarativeType GetDeclarativeType();
  
private:
  HRESULT ExpandUpwards();
  HRESULT ExpandDownwards();
  CATDeclarativeType _DeclarativeType;
  CATBoolean _Expanded;
  CATAgentRelationNode * _Generalized;
  ListPOfCATAgentRelationNode _Specified;
  ListPOfCATAgentRelationNode _RootDependancies;

};

ExportedByPersistentCell CATAgentRelationNode * CATCreateAgentRelationNode(CATDeclarativeType iType); 

ExportedByPersistentCell void CleanupAgentRelationNode(CATAgentRelationNode *ioOriginNode);

#endif
