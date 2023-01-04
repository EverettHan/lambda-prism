#ifndef CATIPGMTopGeoSimplify_h_
#define CATIPGMTopGeoSimplify_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopGeoSimplify;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopGeoSimplify: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopGeoSimplify();

  /**
  * Defines the cells to simplify.
  * @param iCellsToSimplify
  * The list of cells to simplify. This restricts the simplification to these cells only.
  * This method is only currently available for faces.
  * If not called , the simplification will occurs on the whole body.
  */
  virtual void SetCellsToSimplify(CATLISTP(CATCell) &iCellsToSimplify) = 0;

  /**
   * Activate parameter for canonic, fillet & tabulated cylinder surfaces simplification only
   */
  virtual void DisableAllButCanonic() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopGeoSimplify(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopGeoSimplify operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyToSimplify
 * The pointer to the body to geometrically simplify.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopGeoSimplify *CATPGMCreateTopGeoSimplify(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToSimplify);

#endif /* CATIPGMTopGeoSimplify_h_ */
