#ifndef CATICGMDistanceMinPtSur_h_
#define CATICGMDistanceMinPtSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMGeoOperator.h"
#include "CATBoolean.h"
#include "CATMathDiagnostic.h"

class CATGeoFactory;
class CATMathPoint;
class CATPoint;
class CATPointOnSurface;
class CATSurParam;
class CATSurLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMDistanceMinPtSur;

/**
* Class defining the operator of the minimum distance between
* a point and a surface.
*<ul>
*<li>The CATICGMDistanceMinPtSur operator is created with the <tt>CATCGMCreateDistanceMin</tt> method and 
* directly released with the <tt>Release</tt> method.
* It is is not streamable. 
*<li>In case of <tt>BASIC</tt>
* mode, the operation is automatically performed at the operator creation. 
* In case of <tt>ADVANCED</tt>
* mode, options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
* run the same operator with different points.
*<li>In both cases, the result is accessed with specific methods.
*</ul>
*/
class ExportedByCATGMModelInterfaces CATICGMDistanceMinPtSur: public CATICGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDistanceMinPtSur();

  /**
	* Returns the parameter of a point realizing the minimum distance
	* between a surface and a point.
	*<br>Note that only one point is proposed, even multiple solutions exist.
	* @return
	* The parameter on the surface.
	*/
  virtual CATSurParam GetSurParam() const = 0;

  /**
	* Creates a CATPointOnSurface realizing the minimum distance
	* between a surface and a point.
	*<br>Note that only one point is proposed, even multiple solutions exist.
	* @return
	* The pointer to the created point. A new point is created each time this method is called.
	* If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
	*/
  virtual CATPointOnSurface *GetPointOnSurface() const = 0;

  /**
	* Returns the minimum distance between a surface and a point.
	* @return
	* The distance.
	*/
  virtual double GetDistance() const = 0;

  /**
	* In the case of SetPointAndInit usage, the algorithm is limited to a maximum number of iterations.
	* If a maximum number of iterations is reached, the returned point is not fully reconverged but
	* can be used as a new init, using the SetPointAndInit method.
	* @return
	* The diagnostic (CATMathOK or CATMathMaxIteration)
	*/
  virtual CATMathDiagnostic GetDiagnostic() const = 0;

  /**
	* Defines the new domain of the surface to take into account for <tt>this</tt> operator    
	* (<tt>ADVANCED</tt> mode).
	* @param iLimits
	* The limitations on the surface.
	*/
  virtual void SetLimits(const CATSurLimits &iLimits) = 0;

  /**
	* Sets a new point from which the distance to the same surface is evaluated
	* (<tt>ADVANCED</tt> mode).
	* @param iNewPointToOperate
	* The pointer to the new point to take into account. 
	*/
  virtual void SetPoint(CATPoint *iNewPointToOperate) = 0;

  /**
	* Sets a new point from which the distance to the same surface is evaluated
	* (<tt>ADVANCED</tt> mode).
	* @param iNewMathPointToOperate
	* The new point to take into account. 
	*/
  virtual void SetPoint(CATMathPoint &iNewMathPointToOperate) = 0;

  /** 
	* Sets a new point and an initialization
	* (<tt>ADVANCED</tt> mode).
	*<br>This is usefull for computing the distance to a new point near a another one, whose CATSurParam
	* solution is already known. 
	* @param iNewPointToOperate
	* The pointer to the new point to take into account. 
	* @param iSolutionInit
	* The parameter of a point close from the solution.
	*/
  virtual void SetPointAndInit(
    CATPoint *iNewPointToOperate,
    const CATSurParam &iSolutionInit) = 0;

  /** 
	* Sets a new point and an initialization
	* (<tt>ADVANCED</tt> mode).
	*<br>This is usefull for computing the distance to a new point near a another one, whose CATSurParam
	* solution is already known. 
	* @param iMathNewPointToOperate
	* The new point to take into account. 
	* @param iSolutionInit
	* The parameter of a point close from the solution.
	*/
  virtual void SetPointAndInit(
    CATMathPoint &iNewPointToOperate,
    const CATSurParam &iSolutionInit) = 0;

  /**
	* Defines whether the boundaries are taken into account or not (<tt>ADVANCED</tt> mode). 
	* @param iSearchMode
	* The type of search.
	* <br><b>Legal values</b>:
	*  <dl><dt><tt>FALSE</tt><dd> the operator is equivalent to an orthogonal
	* projection which realizes the minimum distance.
	*<dt><tt>TRUE</tt><dd> the operator always return a solution realizing minimum
	* distance even if it is not a projection.</dl> 
	*/
  virtual void SetSearchOnBoundary(CATBoolean iSearchOnBoundary) = 0;

  /**
	* Tests whether a solution exists in case of an 
	* excluded boundary seach (<tt>iSearchOnBoundary=FALSE</tt>).
	* <br>To use after the run.
	* @return
	* The result of the test.
	*<dl><dt><tt>TRUE</tt><dd> the solution exists inside the surface,
	*(with excluded boundary). 
	*    <dt><tt>FALSE</tt><dd> the solution exists only on the surface 
	* boundary.</dl>
	*/
  virtual CATBoolean IsASolution() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDistanceMinPtSur(); // -> delete can't be called
};

#endif /* CATICGMDistanceMinPtSur_h_ */
