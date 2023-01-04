//--------------------------------------------------------------
// VB7
//  W20 2018
//
//  Used by variational team to know if a constraint can be set on an edge or not
//
//  - W20 : only for Edges between a Draft and its context
//--------------------------------------------------------------
#ifndef CATGMCellSupportOfConstraintService_H
#define CATGMCellSupportOfConstraintService_H

#include "CATBoolean.h"
#include "CATPGMCellSupportOfConstraintService.h"
#include "PersistentCell.h"
#include "ListPOfCATFace.h"

class CATBody;
class CATEdge;
class CATGMCellSupportOfConstraintAttribute;
class CATSoftwareConfiguration;
class CATLiveBody;

class ExportedByPersistentCell CATGMCellSupportOfConstraintService : public CATPGMCellSupportOfConstraintService
{
public:
  
  //Constructor
  CATGMCellSupportOfConstraintService(CATSoftwareConfiguration *iConfig);

  //Destructor
  virtual ~CATGMCellSupportOfConstraintService();

  virtual CATBoolean IsEdgeSupportOfConstraint(CATBody * iBody, CATEdge * iEdge);

  virtual CATBoolean IsVertexSupportOfConstraint(CATBody * iBody, CATVertex * iVertex);

private:
  CATGMCellSupportOfConstraintAttribute * ComputeAttribute(CATBody & iBody, CATEdge   & iEdge);
  CATGMCellSupportOfConstraintAttribute * ComputeAttribute(CATBody & iBody, CATVertex & iVertex);

  //ComputeAttribute methods
  CATBoolean ComputeConstraintAllowed(CATBody & iBody, CATEdge   & iEdge);
  CATBoolean ComputeConstraintAllowed(CATBody & iBody, CATVertex & iVertex);

  CATBoolean ComputeConstraintAllowedFromAdjacentFaceList(CATLiveBody & iLiveBody, ListPOfCATFace & iAdjacentFaceList);

  CATSoftwareConfiguration * _Config;
};

// ----------------------------
// CATCreateCellSupportOfConstraintService
// ----------------------------

ExportedByPersistentCell CATGMCellSupportOfConstraintService * CATCreateCellSupportOfConstraintService(CATSoftwareConfiguration *iConfig);

#endif 


