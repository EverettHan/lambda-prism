#ifndef CATICGMHybProject_h_
#define CATICGMHybProject_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMHybOperatorImp.h"
#include "CATDataType.h"
#include "ListPOfCATFace.h"
#include "CATIACGMLevel.h"

class CATExtHybProject;
class CATDomain;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHybProject;

/**
* Class defining the operator that projects a body on another one.
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>CATICGMHybProject is created with the <tt>CATCGMCreateTopProject</tt> global function.
* It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
* <li>The intersection can be restricted on a given domain on each body with the methods
* <tt>SetFirstDomainToIntersect</tt> and <tt>SetSecondDomainToIntersect</tt>
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATCGMCreateTopProject
*/
class ExportedByCATGMOperatorsInterfaces CATICGMHybProject: public CATICGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATICGMHybProject();

  /**
    * Defines which domain of the first body must be projected.
    * @param iDomain
    * The pointer to the domain to project.
    */
  virtual void SetDomainToProject(CATDomain *iDomain) = 0;

  /**
    * Defines on which domain of the second body the projection is done.
    * @param iDomain
    * The pointer to the domain on which to project.
    */
  virtual void SetDomainSupport(CATDomain *iDomain) = 0;

  /**
    * Returns the maximum distance of projection for a given domain of the resulting body.
    * @param iDomainOfResultBody
    * The pointer to the domain.
    * @return
    * The distance.
    */
  virtual double GetDistance(CATDomain *iDomainOfResultBody) = 0;

#ifdef CATIACGMR214CAA
  // In case LayDown Wire On Shell, we can precise the faces on the support
  // default is : all the faces are take into account
 /** 
   * Specifies the faces of the support body on which the projection should be done.
   * <br> By default, all faces are taken into account.
   * @param iCoveredFaces
   * The faces on which the projection should be done.
   */
  virtual void SetCoveredFaces(CATLISTP(CATFace) &iCoveredFaces) = 0;
#endif

  /**
    * Specify a maximum distance for the solution(s) to be kept. By default all the solutions
    * are returned.
    * @param iMaxDistance
    * The maximum distance.
    */
  virtual void SetMaxDistanceValue(double iMaxDistance) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHybProject(); // -> delete can't be called
};

#endif /* CATICGMHybProject_h_ */
