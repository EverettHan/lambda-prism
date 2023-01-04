#ifndef CATICGMSurDegreeModification_h_
#define CATICGMSurDegreeModification_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATDataType.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSurDegreeModification;

/**
 * Class defining an operator that modifies the degree of a Nurbs surface.
 * The CATICGMSurDegreeModification operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATICGMSurDegreeModification operator is created with 
 * the <tt>CATCGMCreateSurDegreeModification</tt> global function 
 * and must be directly released with the <tt>Release</tt> method after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt> mode,
 * the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt> mode,
 * options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMSurDegreeModification: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMSurDegreeModification();

  /** 
   * Runs <tt>this</tt> operator. 
   */
  virtual void Run() = 0;

  /**
   * Specifies the new degree along U.
   * @param iNewDegreeU
   * The new degree along U.
   */
  virtual void SetDegreeU(const CATLONG32 &iNewDegreeU) = 0;

  /**
   * Specifies the new degree along V.
   * @param iNewDegreeV
   * The new degree along V.
   */
  virtual void SetDegreeV(const CATLONG32 &iNewDegreeV) = 0;

  /**
  * Returns the maximum deviation between the initial and the new surface. 
  * This method should be used when decreasing the degree.
  * @return
  * The maximum deviation value.
  */
  virtual double GetMaxDeviation() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSurDegreeModification(); // -> delete can't be called
};

#endif /* CATICGMSurDegreeModification_h_ */
