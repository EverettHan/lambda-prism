#ifndef CATPGMCellSupportOfConstraintService_h_
#define CATPGMCellSupportOfConstraintService_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"

class CATBody;
class CATEdge;
class CATSoftwareConfiguration;
class CATVertex;

class ExportedByCATGMModelInterfaces CATPGMCellSupportOfConstraintService
{
public:
  /**
   * Constructor
   */
  CATPGMCellSupportOfConstraintService();

  /**
   * Destructor
   */
  virtual ~CATPGMCellSupportOfConstraintService();

  //If TRUE :
  // the input edge can be moved or constraints can be set on it.
  virtual CATBoolean IsEdgeSupportOfConstraint(CATBody *iBody, CATEdge *iEdge) = 0;

   //If TRUE :
  // the input vertex can be moved or constraints can be set on it.
  virtual CATBoolean IsVertexSupportOfConstraint(CATBody * iBody, CATVertex * iVertex) = 0;

};

// ----------------------------
// CATCreateCellSupportOfConstraintService
// ----------------------------
ExportedByCATGMModelInterfaces CATPGMCellSupportOfConstraintService *CATPGMCreateCellSupportOfConstraintService(
  CATSoftwareConfiguration *iConfig);

#endif /* CATPGMCellSupportOfConstraintService_h_ */
