#ifndef CATIPGMTopProjection_h_
#define CATIPGMTopProjection_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATDomain;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopProjection;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopProjection: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopProjection();

  /**
   * Run
   */
  virtual int Run() = 0;

  /**
	 * Returns all the computed projections in a single body.
	 * @return
	 * The pointer to the resulting body. If you do not want to keep it, use the @href CATICGMContainer#Remove method
	 * to remove it from the geometric factory after the <tt>delet</tt>ion</tt> of <tt>this</tt> operator.
	 */
  virtual CATBody *GetResult() = 0;

  virtual CATBody *GetResult(CATCGMJournalList *iJourn) = 0;

  /**
   * Defines which domain of the first body must be projected.
   * @param iDomain
   * The pointer to the domain to project
   */
  virtual void SetDomainToProject(CATDomain *iDomain) = 0;

  /**
   * Defines on which domain of the second body the projection is done.
   * @param iDomain
   * The pointer to the domain on which to project
   */
  virtual void SetDomainSupport(CATDomain *iDomain) = 0;

  /**
    * Permit to compute only solutions at a given distance from the point to project
    * @param iDistance
    * the distance.
    */
  virtual void SetMaxDistance(double iDistance) = 0;

  /**
   * Only compute the best solution, the closest from the original point
   * @param bestsol=1 to compute the best solution
   */
  virtual void SetBestSolWanted(CATLONG32 bestsol = 0) = 0;

  /**
    * Returns the maximum distance of projection for a given domain of the resulting body.
	* if no domain given, shortest distance is returned 
    * @param iDomainOfResultBody
    * The pointer to the domain.
    * @return
    * The distance.
    */
  virtual double GetDistance(CATDomain *iDomainOfResultBody = NULL) = 0;

  /**
    * Return the line between point to project and the given domain of the result
	* if no domain given, line between closest solution and point to project is returned 
    * @param iDomainOfResultBody
    * The pointer to the domain.
    * @return
    * The line.
    */
  virtual CATBody *GetLine(CATDomain *iDomainOfResultBody = NULL) = 0;

  /**
   * Retrieve distance max between BodyToProject and solutions
   */
  virtual double GetMaxDistance() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopProjection(); // -> delete can't be called
};

#endif /* CATIPGMTopProjection_h_ */
