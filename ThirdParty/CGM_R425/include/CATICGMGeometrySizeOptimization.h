#ifndef CATICGMGeometrySizeOptimization_h_
#define CATICGMGeometrySizeOptimization_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMGeometrySizeOptimization;

/**
 * Class defining the operator that optimizes the size of a factory
 * by cleaning extrapolated geometries.
 */
class ExportedByCATGMOperatorsInterfaces CATICGMGeometrySizeOptimization: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMGeometrySizeOptimization();

  /**
   * Cleans the NURBS objects without keeping the original limits (only the useful limits will be kept).
   * <tt>Warning<tt> : This mode is not reversible, you may loose original creation data. 
   */
 virtual void                     SetForgetNURBSOriginalLimits() = 0;

  /**
   * Runs <tt>this</tt> operator.
   * @return
   * <tt>1</tt> if the computation failed, <tt>0</tt> otherwise.
   */
 virtual int                      Run                      () = 0;

  /**
   * Returns the diagnosis of the computation.
   * @return
   * The diagnosis of the computation.<br>
   * <tt>0</tt> : Geometry has not been modified<br>
   * <tt>1</tt> : Geometry has been modified (write required).
   */
 virtual int                      GetDiagnosis             () = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMGeometrySizeOptimization(); // -> delete can't be called
};

/**
* Creates a CATICGMGeometrySizeOptimization operator.
* @param iFactory
* The pointer to the factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration. 
* @return [out, IUnknown#Release]
* The pointer to the created operator. To delete with the usual <tt>delete</tt> C++ operator.
*/
ExportedByCATGMOperatorsInterfaces CATICGMGeometrySizeOptimization *CATCGMCreateGeometrySizeOptimization(
  CATGeoFactory * iFactory,
  CATTopData    * iTopData);

#endif /* CATICGMGeometrySizeOptimization_h_ */
