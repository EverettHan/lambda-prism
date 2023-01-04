#ifndef CATIPGMEdgeOperator_h_
#define CATIPGMEdgeOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMGeoToTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATCurve;
class CATDomain;
class CATEdge;
class CATGeoFactory;
class CATLoop;
class CATSurface;
class CATVertex;
class CATCrvLimits;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMEdgeOperator;

//-------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMEdgeOperator: public CATIPGMGeoToTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMEdgeOperator();

  virtual int Run() = 0;

  // return the edge matching the last added curve
  virtual CATEdge *GetEdge() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMEdgeOperator(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMEdgeOperator *CATPGMCreateEdgeOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATCurve *iCurve,
  const CATCrvLimits &iCrvLims);

// Creates a face bounded by pcurves
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMEdgeOperator *CATPGMCreateEdgeOperator(
  CATGeoFactory *factory,
  CATCurve *curve,
  CATBody *bodyforcellcreation = NULL,
  CATBodyFreezeMode bodyfreezemode = CATBodyFreezeOn,
  CATCGMJournalList *report = NULL);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMEdgeOperator *CATPGMCreateEdgeOperator(
  CATGeoFactory *factory,
  CATTopData *iData,
  CATCurve *curve,
  CATBody *bodyforcellcreation = NULL);

#endif /* CATIPGMEdgeOperator_h_ */
