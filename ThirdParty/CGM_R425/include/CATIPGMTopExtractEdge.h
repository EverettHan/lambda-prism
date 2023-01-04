#ifndef CATIPGMTopExtractEdge_h_
#define CATIPGMTopExtractEdge_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCloneManager;
class CATCurve;
class CATEdge;
class CATEdgeCurve;
class CATIPGMHybOperator;
class CATIPGMTopWire;
class CATIPGMTopologicalOperator;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopExtractEdge;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMTopExtractEdge: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopExtractEdge();

  //-------------------------------------------------------------------------
  // Operator management
  //-------------------------------------------------------------------------
  virtual int Run() = 0;

  virtual void DoEdgeAssembly() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopExtractEdge(); // -> delete can't be called
};

// Supression le 11/02/05 Coverage ALV (remplacé par des #define)
// short                    show_trace; // while debugging, set this value to 1 and ...
// you will see .. heaven 
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopExtractEdge *CATPGMCreateTopExtractEdge(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATEdge *iEdge,
  CATBodyFreezeMode iMode = CATBodyFreezeOff);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopExtractEdge *CATPGMCreateTopExtractEdge(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATCell) *iEdges,
  CATBodyFreezeMode iMode = CATBodyFreezeOff);

#endif /* CATIPGMTopExtractEdge_h_ */
