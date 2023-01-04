#ifndef CATICGMTopSplineOperator_h_
#define CATICGMTopSplineOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopCurveOperator.h"
#include "CATDataType.h"
#include "CATSplineMode.h"
#include "CATIAV5Level.h"

class CATMathVector;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSplineOperator;

/**
* Class defining a topological operator that creates a spline body.
 * WARNING - If we build a spline on a support shell and part of it isn't G1 continuous, i.e.
 *           the normals to the faces aren't continous at the boundaries of the faces, the 
 *           result will be unpredictable.
 *
*<br> This operator follows the general scheme of the topological operators.
* For a basic use, use directly the global function
* <tt>CATCGMCreateTopSpline</tt>, that directly returns the resulting body.
* If you need to tune specific parameters, use the advanced scheme:
* <ul>
*<li> Create the operator with the global function <tt>CATCGMCreateTopSplineOperator</tt>
*<li> Set parameters
*<li> Run
*<li> Get the resulting body
*<li> Release the operator with the <tt>Release</tt> method.
*</ul>
*<br> Constaints can be imposed on each points in the following way:
*<dl>
*<dt>0<dt><dd>no constraint, neither on the tangent, nor on the curvature.
*<dt>1<dt><dd>the direction of the tangent is imposed.
*<dt>2<dt><dd>the tangent is imposed.
*<dt>4<dt><dd>the tangent and the direction of the curvature are imposed.
*<dt>6<dt><dd>the tangent and the curvature are imposed.
*</dl>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopSplineOperator: public CATICGMTopCurveOperator
{
public:
  /**
  * Constructor
  */
  CATICGMTopSplineOperator();

  /**
  * Sets new tangent contraints.
  * <br>This method resets already existing results 
  * (obtained by <tt>GetComputedTangents</tt> and <tt>GetComputedCurvatureVectors</tt>)
  * @param iTangents
  * The array of tangential constraints at each point. 
  * If some tangents are constraints, all
  * the array must be allocated.
  * @param iImposition
  * An array that defines the type of constraint for each point. 
  * <br>Legal values</b>:
  *<dl>
  *<dt>0<dt><dd>no constraint, neither on the tangent, nor on the curvature.
  *<dt>1<dt><dd>the direction of the tangent is imposed.
  *<dt>2<dt><dd>the tangent is imposed.
  *<dt>4<dt><dd>the tangent and the direction of the curvature are imposed.
  *<dt>6<dt><dd>the tangent and the curvature are imposed.
  *</dl>
  * If 4 and 6, the methof checks that the curvatures are already been imposed.
  */
  virtual CATLONG32 SetTangents(
    const CATMathVector *iTangents,
    const CATLONG32 *iImposition) = 0;

  /**
  * Sets new curvature contraints.
  *<br> If a curvature is imposed, the tangent at the same point point must also be imposed.
  * @param iCurvatures
  * The array of the curvature constraints at each point.
  * If some curvatures are constraints, all
  * the array must be allocated.
  * @param iImposition
  * An array that defines the type of constraint for each point.
  * <br>Legal values</b>:
  *<dl>
  *<dt>0<dt><dd>no constraint, neither on the tangent, nor on the curvature.
  *<dt>1<dt><dd>the direction of the tangent is imposed.
  *<dt>2<dt><dd>the tangent is imposed.
  *<dt>4<dt><dd>the tangent and the direction of the curvature are imposed.
  *<dt>6<dt><dd>the tangent and the curvature are imposed.
  *</dl>
  */
  virtual CATLONG32 SetCurvatureVectors(
    const CATMathVector *iCurvatures,
    const CATLONG32 *iImposition) = 0;

  /** 
  * Sets the type of spline computation.
  * @param iSplineConstruction
  * The type of interpolation.
  */
  virtual CATLONG32 SetSplineMode(CATSplineMode iSplineConstruction) = 0;

  /** 
  * Retrieves the tangent constraints, as put in the operator definition.
  * <br>The array must not be deallocated.
  * @param oTangents
  * The array of tangential constraints at each point. 
  * If some tangents are constraints, all
  * the array is allocated.
  * @param oImposition
  * An array that defines the type of constraint for each point.
  * @return
  * A diagnosis .
  * <br><b>Legal values:</b>:
  * 0 if tangents where defined, 1 otherwise.
  */
  virtual CATLONG32 GetImposedTangents(
    const CATMathVector *&oTangents,
    const CATLONG32 *&oImposition) = 0;


#if ! defined(CATIAV5R21) && ! defined(CATIAR209)
  /** 
  * Up to V5R21 and V6R209.
  * Retrieves the tangent constraints, as put in the operator definition.
  * <br>The array must not be deallocated.
  * @param oCurvatures
  * The array of the curvature constraints at each point.
  * If some curvatures are constraints, all
  * the array is allocated.
  * @param oImposition
  * An array that defines the type of constraint for each point.
  * @return
  * A diagnosis .
  * <br><b>Legal values:</b>:
  * 0 if curvatures where defined, 1 otherwise.
  */
  virtual CATLONG32 GetImposedCurvatureVectors(
    const CATMathVector *oCurvatures,
    const CATLONG32 *oImposition) = 0;
#else
  /** 
  * From V5R21 and V6R209.
  * Retrieves the tangent constraints, as put in the operator definition.
  * <br>The array must not be deallocated.
  * @param oCurvatures
  * The array of the curvature constraints at each point.
  * If some curvatures are constraints, all
  * the array is allocated.
  * @param oImposition
  * An array that defines the type of constraint for each point.
  * @return
  * A diagnosis .
  * <br><b>Legal values:</b>:
  * 0 if curvatures where defined, 1 otherwise.
  */
  virtual CATLONG32 GetImposedCurvatureVectors(
    const CATMathVector *&oCurvatures,
    const CATLONG32 *&oImposition) = 0;
#endif

  /**
  * Returns the number of points defined at the operator construction.
  * @return
  * The number of points.
  */
  virtual CATLONG32 GetNbPoints() = 0;

  /**
  * Returns the spline mode construction.
  * @param ioSplineConstruction
  * The spline mode.
  */
  virtual CATLONG32 GetSplineMode(CATSplineMode &ioSplineConstruction) = 0;

  /** 
  * Retrieves, after a Run, the computed tangents at each point.
  * <br>The array must not be deallocated.
  * @param oTangents
  * The computed tangents. 
  * @return
  * A diagnosis .
  * <br><b>Legal values:</b>:
  * 0 if tangents are computed, 1 otherwise.
  */
  virtual CATLONG32 GetComputedTangents(const CATMathVector *&oTangents) = 0;


#if ! defined(CATIAV5R21) && ! defined(CATIAR209)
  /** 
  * Up to V5R21 and V6R209.
  * Retrieves, after a Run, the computed curvatures at each point.
  * <br>The array must not be deallocated.
  * @param oCurvatures
  * The computed curvatures.
  * @return
  * A diagnosis .
  * <br><b>Legal values:</b>:
  * 0 if curvatures are computed, 1 otherwise.
  */
  virtual CATLONG32 GetComputedCurvatureVectors(
    const CATMathVector *oCurvatures) = 0;
#else
  /** 
  * From V5R21 and V6R209.<br>
  * Retrieves, after a Run, the computed curvatures at each point.
  * <br>The array must not be deallocated.
  * @param oCurvatures
  * The computed curvatures.
  * @return
  * A diagnosis .
  * <br><b>Legal values:</b>:
  * 0 if curvatures are computed, 1 otherwise.
  */
  virtual CATLONG32 GetComputedCurvatureVectors(
    const CATMathVector *&oCurvatures) = 0;
#endif

protected:
  /**
  * Destructor
  */
  virtual ~CATICGMTopSplineOperator(); // -> delete can't be called
};

/**
* Creates a topological operator that builds a spline body.
* <br> After creating the operator, use the </tt>Setxxx</tt> methods to tune
* your parameters. Then run it, retrieve the resulting body, and delete the operator.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iNbpts
* The number of points to take into account for the computation of the spline.
* @param iListOfpoints
* The array of pointers to bodies that uniquely contain one point as CATVertexInVolume. 
* These points
* are taken into account for the computation of the spline.
* @param iTangents
* The array of tangential constraints at each point. 
* <tt>NULL</tt> if the tangents are globally not constraint. 
* If some tangents are constraints, all
* the array must be allocated.
* @param iCurvatures
* The array of the curvature constraints at each point.
* <tt>NULL</tt> if the curvatures are globally not constraint. 
* If some tangents are constraints, all
* the array must be allocated.
* @param iImposition
* The array that defines the type of constraint for each point.
*<tt> NULL</tt> if nothing is imposed.
*<dl>
*<dt>0<dt><dd>no constraint, neither on the tangent, nor on the curvature.
*<dt>1<dt><dd>the direction of the tangent is imposed.
*<dt>2<dt><dd>the tangent is imposed.
*<dt>4<dt><dd>the tangent and the direction of the curvature are imposed.
*<dt>6<dt><dd>the tangent and the curvature are imposed.
*</dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopSplineOperator *CATCGMCreateTopStableSplineOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLONG32 iNbpts,
  CATBody **iListOfPoints,
  const CATMathVector *iTangents = NULL,
  const CATMathVector *iCurvatures = NULL,
  const CATLONG32 *iImposition = NULL);

/**
* Creates a spline body.
* <br> This basic mode direclty creates the resulting body.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iNbpts
* The number of points to take into account for the computation of the spline.
* @param iListOfpoints
* The array of pointers to bodies that uniquely contain one point as CATVertexInVolume. 
* These points
* are taken into account for the computation of the spline.
* @param iTangents
* The array of tangential constraints at each point. 
* <tt>NULL</tt> if the tangents are globally not constraint. 
* If some tangents are constraints, all
* the array must be allocated.
* @param iCurvatures
* The array of the curvature constraints at each point.
* <tt>NULL</tt> if the curvatures are globally not constraint. 
* If some tangents are constraints, all
* the array must be allocated.
* @param iImposition
* The array that defines the type of constraint for each point.
*<dl>
*<dt>0<dt><dd>no constraint, neither on the tangent, nor on the curvature.
*<dt>1<dt><dd>the direction of the tangent is imposed.
*<dt>2<dt><dd>the tangent is imposed.
*<dt>4<dt><dd>the tangent and the direction of the curvature are imposed.
*<dt>6<dt><dd>the tangent and the curvature are imposed.
*</dl>
* <tt>NULL</tt> if nothing is imposed.
* @return
* The pointer to the created line body. To remove with the @href CATICGMContainer#Remove method.
*/
ExportedByCATGMOperatorsInterfaces CATBody *CATCGMCreateTopStableSpline(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLONG32 iNbpts,
  CATBody **iListOfPoints,
  const CATMathVector *iTangents = NULL,
  const CATMathVector *iCurvatures = NULL,
  const CATLONG32 *iImposition = NULL);

/**
* DO NOT USE - Use either of CATCGMCreateTopStableSpline functions.
* <br>
* Creates a topological operator that builds a spline body.
* <br> After creating the operator, use the </tt>Setxxx</tt> methods to tune
* your parameters. Then run it, retrieve the resulting body, and delete the operator.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iNbpts
* The number of points to take into account for the computation of the spline.
* @param iListOfpoints
* The array of pointers to bodies that uniquely contain one point as CATVertexInVolume. 
* These points
* are taken into account for the computation of the spline.
* @param iTangents
* The array of tangential constraints at each point. 
* <tt>NULL</tt> if the tangents are globally not constraint. 
* If some tangents are constraints, all
* the array must be allocated.
* @param iCurvatures
* The array of the curvature constraints at each point.
* <tt>NULL</tt> if the curvatures are globally not constraint. 
* If some tangents are constraints, all
* the array must be allocated.
* @param iImposition
* The array that defines the type of constraint for each point.
*<tt> NULL</tt> if nothing is imposed.
*<dl>
*<dt>0<dt><dd>no constraint, neither on the tangent, nor on the curvature.
*<dt>1<dt><dd>the direction of the tangent is imposed.
*<dt>2<dt><dd>the tangent is imposed.
*<dt>4<dt><dd>the tangent and the direction of the curvature are imposed.
*<dt>6<dt><dd>the tangent and the curvature are imposed.
*</dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopSplineOperator *CATCGMCreateTopSplineOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLONG32 iNbpts,
  CATBody **iListOfPoints,
  const CATMathVector *iTangents = NULL,
  const CATMathVector *iCurvatures = NULL,
  const CATLONG32 *iImposition = NULL);

/**
* DO NOT USE - Use either of the CATCGMCreateTopStableSpline function.
* <br>
* Creates a spline body.
* <br> This basic mode direclty creates the resulting body.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iNbpts
* The number of points to take into account for the computation of the spline.
* @param iListOfpoints
* The array of pointers to bodies that uniquely contain one point as CATVertexInVolume. 
* These points
* are taken into account for the computation of the spline.
* @param iTangents
* The array of tangential constraints at each point. 
* <tt>NULL</tt> if the tangents are globally not constraint. 
* If some tangents are constraints, all
* the array must be allocated.
* @param iCurvatures
* The array of the curvature constraints at each point.
* <tt>NULL</tt> if the curvatures are globally not constraint. 
* If some tangents are constraints, all
* the array must be allocated.
* @param iImposition
* The array that defines the type of constraint for each point.
*<dl>
*<dt>0<dt><dd>no constraint, neither on the tangent, nor on the curvature.
*<dt>1<dt><dd>the direction of the tangent is imposed.
*<dt>2<dt><dd>the tangent is imposed.
*<dt>4<dt><dd>the tangent and the direction of the curvature are imposed.
*<dt>6<dt><dd>the tangent and the curvature are imposed.
*</dl>
* <tt>NULL</tt> if nothing is imposed.
* @return
* The pointer to the created line body. To remove with the @href CATICGMContainer#Remove method.
*/
ExportedByCATGMOperatorsInterfaces CATBody *CATCGMCreateTopSpline(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLONG32 iNbpts,
  CATBody **iListOfPoints,
  const CATMathVector *iTangents = NULL,
  const CATMathVector *iCurvatures = NULL,
  const CATLONG32 *iImposition = NULL);

#endif /* CATICGMTopSplineOperator_h_ */
