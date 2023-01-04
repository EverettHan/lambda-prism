#ifndef CATIPGMSplitBySurfaceOperator_h_
#define CATIPGMSplitBySurfaceOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATSurface;

class CATSplitBySurfaceOperatorCXR19;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSplitBySurfaceOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMSplitBySurfaceOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSplitBySurfaceOperator();

  virtual CATBody *GetResult(CATCGMJournalList *ioJournal) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSplitBySurfaceOperator(); // -> delete can't be called
};

/**
 * Creates an operator to split a body by a surface.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside the
 * configuration is <tt>NULL</tt>, it is not filled. 
 * @param iSurface
 * The pointer to the surface used to split the body.
 * @param iBodySupport
 * The body to be split.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSplitBySurfaceOperator *CATPGMCreateSplitBySurfaceOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATSurface *iSurface,
  CATBody *iBodySupport);

#endif /* CATIPGMSplitBySurfaceOperator_h_ */
