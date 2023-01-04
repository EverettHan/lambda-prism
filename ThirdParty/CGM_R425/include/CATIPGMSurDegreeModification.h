#ifndef CATIPGMSurDegreeModification_h_
#define CATIPGMSurDegreeModification_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATDataType.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSurDegreeModification;

/**
 * @level Protected
 * @usage U1
 */
/**
 * Class defining an operator that modifies the degree of a Nurbs surface.
 * The CATIPGMSurDegreeModification operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATIPGMSurDegreeModification operator is created with 
 * the <tt>CATPGMCreateSurDegreeModification</tt> global function 
 * and must be directly released with the <tt>Release</tt> method after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt> mode,
 * the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt> mode,
 * options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSurDegreeModification: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMSurDegreeModification();

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

  /**
  * @nodoc
  * Returns the maximum degree along U statisfying the tolerance and/or the
  * target degree. 
  * This method should be used when decreasing the degree
  * with a given tolerance.
  * @return
  * The new degree along U.
  */
  virtual CATLONG32 GetNewDegreeU() = 0;

  /**
  * @nodoc
  * Returns the maximum degree along V statisfying the tolerance and/or the
  * target degree. 
  * This method should be used when decreasing the degree
  * with a given tolerance.
  * @return
  * The new degree along V.
  */
  virtual CATLONG32 GetNewDegreeV() = 0;

  /**
  * @nodoc
  * Sets a new tolerance. 
  * This method should be used when decreasing the degree
  * with a given tolerance.
  * @param iTolerance
  * The new tolerance.
  */
  virtual void SetTolerance(const double iTolerance) = 0;

  /**
  * @nodoc
  * Imposes a given continuity at the surface extremities. Authorized values
  * are 0,1,2 for G0, G1 and G2 continuities. Default value is 0.
  * This method should be used when decreasing the degree
  * with a given tolerance.
  * @param iStartContinuityU
  * The continuity at the start extremity along U.
  * @param iEndContinuityU
  * The continuity at the end extremity along U.
  * @param iStartContinuityV
  * The continuity at the start extremity along V.
  * @param iEndContinuityV
  * The continuity at the end extremity along V.
  */
  virtual void SetContinuityAtEnds(
    CATLONG32 iStartContinuityU,
    CATLONG32 iEndContinuityU,
    CATLONG32 iStartContinuityV,
    CATLONG32 iEndContinuityV) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurDegreeModification(); // -> delete can't be called
};

#endif /* CATIPGMSurDegreeModification_h_ */
