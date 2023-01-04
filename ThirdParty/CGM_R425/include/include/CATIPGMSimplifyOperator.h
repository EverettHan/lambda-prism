#ifndef CATIPGMSimplifyOperator_h_
#define CATIPGMSimplifyOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATSimplifyOperatorDef.h"

class CATBody;
class CATCGMJournalList;
class CATCellTagHashTable;
class CATDomain;
class CATGeoFactory;
class CATTopData;
class CATCellHashTable;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSimplifyOperator;

/**
* Class representing the operator that simplifies a whole body or selected cells of a body.
*
* This operator does not follow the general scheme of topological operator :
* - He takes a modifiable body as input and modify it.
* - He is in fact a sub operator to be called as the last step of another operator
*   to simplify the result before the "freeze" operation.
*
* The external view of the operator is the CATIPGMTopSimplify CAA operator which follow the
* general scheme of the topological operator.
*/
class ExportedByCATGMModelInterfaces CATIPGMSimplifyOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSimplifyOperator();

  //  Run
  virtual int Run() = 0;

  // Set Body and optionnaly domain to simplify
  // ( this service is mandatory and has to be called first )
  virtual void SetBody(CATBody *iBody, CATDomain *iDomain = NULL) = 0;

  // Defines the cells to simplify.
  // This restricts the simplification to these cells only.
  // ( this service is exclusive with the SimplifyByCells service ).
  virtual void SimplifyCells(CATCellHashTable *iCellsToSimplify) = 0;

  // Defines the cells to remove during simplification.
  // This restricts the simplification to the cells bounded to these cells only.
  // ( this service is exclusive with the SimplifyCells service ).
  virtual void SimplifyByCells(CATCellHashTable *iCellsToRemove) = 0;

  // Define the cells which will be used as reference for geometric simplification :
  // - This means that the geometry of theses cells will be considered as reference and
  // used for support of the new simplified cells.
  // - If this geometry can not be used , simplification will not be done locally.
  // - This service is restricted today to faces ( for selection of surfaces to used
  // as support of the simplified faces )
  virtual void SetReferenceCells(CATCellHashTable *iReferenceCells) = 0;

  // Define a specific journal for edge simplification reporting
  virtual void SetEdgeReporting(CATCGMJournalList *iEdgeReport) = 0;

  /* do not use */
  virtual void SetSpecialMode(const int iSpecialMode) = 0;

  // When replacing canonical supports during geometric simplification step
  // the geometric replacement will be only local to the simplified cells
  // and not global.
  // This option is not recommanded because we try to reduce the total number
  // of differents surfaces within a part.
  // This option is only useful for specific performance needs when adding new geometric
  // ( Draft / Fillet case ).
  virtual void SetLocalGeometricSimplificationMode() = 0;

  // SetDimensionToSimplify :
  // - set Mask for specific dimension simplification 
  // - This is a combinaison of MASK_SIMPLIFY_EDGE , MASK_SIMPLIFY_FACE and MASK_SIMPLIFY_VOLUME
  // - by default , all dimension are simplified
  virtual void SetDimensionToSimplify(const unsigned int iMaskForDimensionToSimplify) = 0;

  // HandleRemoteEdgesWithSameGeometry :
  // - Set a flag to have the simplify operator to attempt simplification of edge(s) 
  // - in the equivalence class that share the same underlying geometry with edge(s)
  // - outside of the given equivalence class (e.g. topologically disconnected edges)
  virtual void HandleRemoteEdgesWithSameGeometry(
    CATBoolean iHandleRemoteEdgesWithSameGeometry) = 0;

  // EnableTolerantSimplification :
  // - Set a flag to have the simplify operator to attempt to run in tolerant simplify mode
  virtual void EnableTolerantSimplification(double iRelativeTolerance) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSimplifyOperator(); // -> delete can't be called
};

// Constructor
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSimplifyOperator *CATPGMCreateSimplifyOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData);

#endif /* CATIPGMSimplifyOperator_h_ */
