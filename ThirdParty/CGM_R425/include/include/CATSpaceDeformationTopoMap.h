#ifndef CATSpaceDeformationTopoMap_H
#define CATSpaceDeformationTopoMap_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATCrvLimits.h"

class CATMapFunctionXYZ;
class CATSpaceDeformationSplitTool;
class CATSpaceDeformationCldSplitTool;
class CATPointOnSurface;
class CATPCurve;


/**
 * Class defining the map of a topological deformation.
 * <br>A topological deformation is defined by:
 * <ul><li>The mathematical definition of the deformation ( @href CATMapFunctionXYZ ), a function
 * from R^3 to R^3
 * <li>The topological impact of the deformation ( @href CATSpaceDeformationSplitTool), defining the impacted
 * cells.
 * </ul>
 * CATSpaceDeformationTopoMap is directly created by dedicated operators, such as the @href CATBumpDefine operator,
 * according to the operation to process. 
 * It is then used by the @href CATTopDeformation operator, that really creates the resulting body.
 * CATMapFunctionXYZ must be deleted after use. During its deletion.
 */
class ExportedByCATGMOperatorsInterfaces CATSpaceDeformationTopoMap
{
  public:
	
    /** 
    * Get the number of map.
    *
    * @return
    * return the number of map.
    *
    */
    virtual int GetNumberOfMap() const = 0;
		
/**
 * Returns one mathematical definition of <tt>this</tt> topological deformation map.
 * @param iNum
 *   The numero (between 1 and   <tt>this->GetNumberOfMap()</tt>) of the map.
 * @return
 * The pointer to the mathematical definition of <tt>this</tt>. Must be deleted by the
 * user of <tt>this</tt> map.
 */		virtual const CATMapFunctionXYZ* GetXYZMap(const int iNum=1) const = 0;


/**
 * Set the mathematical definition of <tt>this</tt> topological deformation map.
 */
	  virtual void SetXYZMap(CATMapFunctionXYZ* iMap, const int iNum=1)=0;


    virtual void SetPolySplitTool(CATSpaceDeformationCldSplitTool* iPolySplitTool)=0;


    virtual const CATSpaceDeformationCldSplitTool* GetPolySplitTool() const=0;
  
/**
 * Returns the topological definition of the deformation.
 * @return
 */
		virtual CATSpaceDeformationSplitTool* GetSplitTool() const = 0;
		
/**
 * Returns the cutting option.
 * @return
 * The cutting option.
 * <br><b>Legal values</b>: <tt>TRUE</tt> to allow the split of the input body to keep
 * good quality surfaces, <tt>FALSE</tt> otherwise.
 */
		virtual	CATBoolean CuttingIsNecessary() const = 0;



    /** 
    * Add a point on surf as constraint
    *
    * <br><b>Role</b>: Allow to specify a tolerance for some points
    *        on an initial surface support.
    *        This methode must be use, in the "Define" step.
    *
    * @param iPoint [in]
    *   A point to localize the constraint
    * @param iTol [in]
    *   The tolerance to reach in the approximation.
    *
    * @return
    *   >0 : The point is added, its index is returned
    *   <=0 : The point is not added (ERROR)
    *
    */
    virtual int AddPointOnSurfConstraint(CATPointOnSurface* iPoint, const double iTol=0.0) = 0;

    /** 
    * get the number of punctual constaints
    * @return
    *   The number of point on surface defined as constraint.
    *
    */
    virtual int GetNumberOfPointOnSurf() const = 0;

    /** 
    * Get a punctual constraint.
    *
    * <br><b>Role</b>: Define (for apply step) a specific tolerance for one point
    *
    * @param iIndex [in]
    *   The index of the punctal constraint in [1,.. GetNumberOfPointOnSurf()]
    * @param oPoint [out]
    *   The constriant's point.
    * @param oTol [out]
    *    The constraint's tolerances.
    *
    * @return
    *   0 : OK
    *  >0 : One error has occured.
    *
    */
    virtual int GetPointOnSurfConstraint(const int iIndex, CATPointOnSurface*& oPoint, double& oTol) const = 0;

    /** 
    * Add a parametric curve as constraint
    *
    * <br><b>Role</b>: Allow to specify a tolerance (in Apply step) for some curve
    *        on an initial surface support.
    *        This methode must be use, in the "Define" step.
    *
    * @param iCurve [in]
    *   A curve to localize the constraint
    * @param iTol [in]
    *   The tolerance to reach in the approximation.
    *
    * @return
    *   >0 : The curve is added, its index is returned
    *   <=0 : The curve is not added (ERROR)
    *
    */
    virtual int AddCurveOnSurfConstraint(CATPCurve* iCurve, CATCrvLimits& iLimits, const double iTol=0.0, const int iOrder=0) = 0;

    /** 
    * get the number of curve's constaints
    * @return
    *   The number of curves on surface defined as constraint.
    *
    */
    virtual int GetNumberOfCurveOnSurf() const = 0;

    /** 
    * Get a curve constraint.
    *
    * <br><b>Role</b>: Define (for apply step) a specific tolerance for one Curve
    *
    * @param iIndex [in]
    *   The index of the punctal constraint in [1,.. GetNumberOfCurveOnSurf()]
    * @param oCurve [out]
    *   The constraint's Curve.
    * @param oTol [out]
    *    The constraint's tolerances.
    * @param oOrder [out]
    *    The constraint's order. (G0,G1,G2...)
    *
    * @return
    *   0 : OK
    *  >0 : One error has occured.
    *
    */
    virtual int GetCurveOnSurfConstraint(const int iIndex, CATPCurve*& oPCurve, CATCrvLimits& oLimits, double& oTol, int& oOrder) const = 0;

  /**
   * Increments the reference count of the instance.
   */
   virtual void AddRef()=0;

  /**
   * Decrements the reference count of the instance.  When the counter reaches 0, the instance is deleted.
   */
   virtual void Release()=0;

   protected:
		virtual ~CATSpaceDeformationTopoMap();
};	
/**
 * Constructs a topological deformation map.
 * @param iMapFunctionXYZ
 * @param iFDFSplitTool
 * @param iCuttingIsNecessary
 * The cutting option.
 * <br><b>Legal values</b>: <tt>TRUE</tt> to allow the split of the input body to keep
 * good quality surfaces, <tt>FALSE</tt> otherwise.
 *
 * @return [out, IUnknown#Release]
 *   The created  map of a topological deformation. (one AddRef is done)
 *
*/
ExportedByCATGMOperatorsInterfaces CATSpaceDeformationTopoMap* CATCreateSpaceDeformationTopoMap(
                                                              CATMapFunctionXYZ *iMapFunctionXYZ,
                                                              CATSpaceDeformationSplitTool* iFDFSplitTool,
                                                              CATBoolean			 iCuttingIsNecessary);

/** 
* Constructs a topological deformation multi map.
*
* <br><b>Role</b>: Create a topological deformation multi map in case of piecewise definition of the map. 
*
* @param iFDFXYZMap [in]
*   The mathematical maps, wich define the geometric deformation
* @param iNumberOfMap [in]
*   The Number of map, wich define the geometric deformation
* @param iFDFSplitTool [in]
*   The topological definition of the deformation.
*
* @return [out, IUnknown#Release]
*   The created  map of a topological deformation. (one AddRef is done)
*
*/
ExportedByCATGMOperatorsInterfaces CATSpaceDeformationTopoMap * CATCreateSpaceDeformationTopoMap(
                                                                CATMapFunctionXYZ**		iFDFXYZMap,
                                                                const int iNumberOfMap,
                                                                CATSpaceDeformationSplitTool* iFDFSplitTool);
#endif
