#ifndef CATICGMProjectionPtSur_h_
#define CATICGMProjectionPtSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMGeoOperator.h"
#include "CATDataType.h"
#include "CATBoolean.h"

class CATCartesianPoint;
class CATGeoFactory;
class CATPointOnSurface;
class CATSurLimits;
class CATSurParam;
class CATMathPoint;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMProjectionPtSur;

/**
* Class defining the operator of projection of a CATPoint onto a
* CATSurface.
*<br> The projection can be orthogonal or directional.
* The resulting objects are points. 
*<ul>
*<li>The CATICGMProjectionPtSur operator is created with the <tt>CATCGMCreateProjection</tt> method and 
* directly released with the <tt>Release</tt> method.
* It is is not streamable. 
* <li>In case of <tt>BASIC</tt>
* mode, the operation is automatically performed at the operator creation. 
* In case of <tt>ADVANCED</tt>
* mode, options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
* run the same operator with different points.
* <li>In both cases, the result is accessed with a specific interator. Note
* that the resulting projection depends on the limitations specified. For example, 
* the operator may find no projection when using the current limitations while it may return
* a projection when using the maximum limitations.
*</ul>
*/
class ExportedByCATGMModelInterfaces CATICGMProjectionPtSur: public CATICGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATICGMProjectionPtSur();

  /**
	* Returns the distance between the CATPoint and its Projection on the CATSurface.
	* @return
	* The distance.
	*/
  virtual double GetDistance() const = 0;

  /**
	* Returns the number of solution points of <tt>this</tt> CATICGMProjectionPtSur operator.
	* @return
	* The number of solution points.
	* <br>WARNING: the operator may find no projection when using the current limitations while it may return
    * a projection when using the maximum limitations. Therefore, when using the ADVANCED mode, it is recommended 
	* to specify the max limits of the surface by using the UseLimits method.
	*/
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  /**
	* Initializes the iterator of the resulting points.
	* <br>By default, the initialization is performed once the operator runs, 
	* and this is therefore only used to read the solutions again.
	*/
  virtual void BeginningPoint() = 0;

  /**
	* Skips to the next solution point of <tt>this</tt> CATICGMProjectionPtSur operator.
	* <br>After <tt>BeginningPoint</tt>, it skips to the first point. 
	* @return
	* The existence of the next solution.
	* <br><b>Legal values</b>:
	*<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
	*    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
	*/
  virtual CATBoolean NextPoint() = 0;

  /**
	* Creates the next solution point of <tt>this</tt> CATICGMProjectionPtSur operator.
	* @return
	* The pointer to the created point. A new point is created each time this method is called.
	* If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
	*/
  virtual CATCartesianPoint *GetCartesianPoint() const = 0;

  /**
	* Creates the next solution as a point on surface.
	* @return
	* The pointer to the created point on curve. A new point is created each time this method is called.
	* If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
	*/
  virtual CATPointOnSurface *GetPointOnSurface() const = 0;

  /**
	* Returns the parameter on the surface of the next solution point of <tt>this</tt> CATICGMProjectionPtSur operator.
	* @return
	* The parameter.
	*/
  virtual CATSurParam GetParam() const = 0;

  /**
	* Modifies the surface domain to be taken into account for <tt>this</tt> CATICGMProjectionPtSur
	* operator (<tt>ADVANCED</tt> mode).
	* <br>It does not change the current surface 
	* limitations.  
	* @param iNewLimits
	* The new limitations of the surface, <tt>NULL</tt> to take the current limitations. Note
	* that the resulting projection depends on the limitations specified. For example, 
	* the operator may find no projection when using the current limitations while it may return
	* a projection when using the maximum limitations.
	*/
  virtual void UseLimits(CATSurLimits *iLimitsToTakeForSurface) = 0;

 /**
 * Defines a new point to project (<tt>ADVANCED</tt> mode).
 * @param iPoint
 * The new point.
 */
  virtual void SetPoint(const CATMathPoint &iPoint) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMProjectionPtSur(); // -> delete can't be called
};

#endif /* CATICGMProjectionPtSur_h_ */
