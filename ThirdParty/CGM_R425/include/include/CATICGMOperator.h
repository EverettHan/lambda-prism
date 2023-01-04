#ifndef CATICGMOperator_h_
#define CATICGMOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGeometricObjects.h"
#include "CATICGMVirtual.h"

class CATBaseUnknown;
class CATCGMOutput;
class CATCGMStream;
class CATCloneManager;
class CATError;
class CATExtCGMReplay;
class CATExtGeoOperator;
class CATGeoFactory;
class CATICGMObject;
class CATSoftwareConfiguration;
class CATString;
class CATTolerance;
class CATICGMTopOperator;

extern ExportedByCATGeometricObjects IID IID_CATICGMOperator;

//=======================================================================================================================
/**
 * Base class for all the CGM operators.
 * <br>To use a CGM operator:
 * <ul><li>Create it with the corresponding <tt>CreateXxx</tt> global method
 * <li>Tune some parameters if needed
 * <li>Run it
 * <li>Read the results
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGeometricObjects CATICGMOperator: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMOperator();

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  /**
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

  /**
 * Returns the factory of <tt>this</tt> operator. 
 * @return
 * The pointer to the geometric factory that creates the output objects.
 */
  virtual CATGeoFactory *GetFactory() const = 0;

  /**
 * Retrieves the name of <tt>this</tt> operator.
 * @return
 * The name. This output string is part of the class and will be deleted at its deletion.
 */
  virtual const CATString *GetOperatorId() = 0;

  /** 
 * Defines the name of <tt>this</tt> operator.
 * @param iOperatorName
 * The name of the operator.
 */
  virtual void SetOperatorId(const CATString iOperatorName) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMOperator(); // -> delete can't be called
};

#endif /* CATICGMOperator_h_ */
