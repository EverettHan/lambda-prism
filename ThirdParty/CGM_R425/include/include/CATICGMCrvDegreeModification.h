#ifndef CATICGMCrvDegreeModification_h_
#define CATICGMCrvDegreeModification_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATDataType.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMCrvDegreeModification;

/**
 * Class defining an operator that modifies the degree of a curve.
 * The CATICGMCrvDegreeModification operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATICGMCrvDegreeModification operator is created with the <tt>CATCGMCreateCrvDegreeModification</tt> global function 
 * and must be directly released with the <tt>Release</tt> method after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt> mode,
 * the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt> mode,
 * options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMCrvDegreeModification: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMCrvDegreeModification();

  /** 
   * Runs <tt>this</tt> operator. 
   */
  virtual void Run() = 0;

  /**
   * Specifies the new degree.
   * @param iNewDegree
   * The new degree.
   */
  virtual void SetDegree(const CATLONG32 &iNewDegree) = 0;

  /**
  * Returns the maximum deviation between the initial and the new curve. 
  * This method should be used when decreasing the degree.
  * @return
  * The maximum deviation value.
  */
  virtual double GetMaxDeviation() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMCrvDegreeModification(); // -> delete can't be called
};

#endif /* CATICGMCrvDegreeModification_h_ */
