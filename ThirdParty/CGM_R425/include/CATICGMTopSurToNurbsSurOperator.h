#ifndef CATICGMTopSurToNurbsSurOperator_h_
#define CATICGMTopSurToNurbsSurOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATDataType.h"

class CATCell;
class CATFace;
class CATGeometry;
class CATTopData;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSurToNurbsSurOperator;

/**
 * Class defining a topological operator that converts the geometry of a surface to a NURBS surface.
 * This operator follows the general scheme of the topological operators:
 * <ul>
 *<li> Create the operator with the global function <tt>CATCGMCreateTopSurToNurbsSurOperator</tt>, which defines
 * the face to transform using a skin body
 *<li> Set the parameters
 *<li> Run
 *<li> Get the resulting body
 *<li> Release the operator with the <tt>Release</tt> method after use.
 *</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopSurToNurbsSurOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopSurToNurbsSurOperator();

  //
  // ADVANCED mode settings
  //-----------------------
  //
  // The following setting methods follow the creation of a CATICGMTopSurToNurbsSurOperator,
  // (see CATCGMCreateTopSurToNurbsSurOperator global function)
  //
   /**
  * Defines the fitting tolerance.
  * @param iTolerance
  * The tolerance value. By default, set to the factory resolution.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetTolerance(double iTolerance) = 0;

  /**
  * Defines the maximum degree allowed in U direction for the NURBS surface.
  * @param iMaxDegreeU
  * The maximum degree value.
  * If both methods <tt>SetMaxDegreeU</tt> and <tt>SetMaxArcsU</tt> are used, 
  * the priority is given to the maximum degree.
  * Default value is 5.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMaxDegreeU(CATLONG32 iMaxDegreeU) = 0;

  /**
  * Defines the maximum degree allowed in V direction for the NURBS surface.
  * @param iMaxDegreeV
  * The maximum degree value.
  * If both methods <tt>SetMaxDegreeV</tt> and <tt>SetMaxArcsV</tt> are used, 
  * the priority is given to the maximum degree.
  * Default value is 5.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMaxDegreeV(CATLONG32 iMaxDegreeV) = 0;

  /**
  * Defines the maximum number of arcs allowed in U direction for the NURBS surface.
  * @param iMaxArcsU
  * The maximum number of arcs.
  * If both methods <tt>SetMaxDegreeU</tt> and <tt>SetMaxArcsU</tt> are used, 
  * the priority is given to the maximum degree.
  * Default value is 3.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMaxArcsU(CATLONG32 iMaxArcsU) = 0;

  /**
  * Defines the maximum number of arcs allowed in V direction for the NURBS surface.
  * @param iMaxArcsV
  * The maximum number of arcs.
  * If both methods <tt>SetMaxDegreeV</tt> and <tt>SetMaxArcsV</tt> are used, 
  * the priority is given to the maximum degree.
  * Default value is 3.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMaxArcsV(CATLONG32 iMaxArcsV) = 0;

  /**
  * Defines whether the resulting surface is rational. 
  * @param iRationalAbility
  * <br><b>Legal values</b>:<tt>0</tt> to convert the surface to a non rational surface, <tt>1</tt>
  * to convert the surface to a rational surface.
  * Some canonic surfaces are transformed into rational CATNurbsSurface
  * but setting <tt>iRationalAbility = 0</tt> forces the conversion to a non rational surface.
  * The default mode is the conversion into rational (equivalent to <tt>iRationalAbility = 1</tt>).
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetRationalAbility(CATLONG32 iRationalAbility) = 0;

  /**
  * Retrieves whether the created surface has been approximated.
  * <br>To be called after the <tt>Run</tt> method.
  * @param ioIsExact
  * <tt>0</tt> if there is an approximation, not null otherwise.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 IsExactTransformation(CATLONG32 &oIsExact) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopSurToNurbsSurOperator(); // -> delete can't be called
};

//
// creation of operator (ADVANCED mode)
//-------------------------------------
/**
* Creates a topological operator to convert the geometry of a surface into a NURBS surface.
* @param iFactory
* The pointer to the factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iBody
* The body that contains the face <tt>iFaceCell</tt>.
* @param iFaceCell
* The face whose surface is transformed into a NURBS surface.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopSurToNurbsSurOperator *CATCGMCreateTopSurToNurbsSurOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATCell *iFaceCell);

/**
* Creates a topological operator to convert the geometry of a surface into a NURBS surface.
* @param iFactory
* The pointer to the factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iBody
* The body that contains the faces <tt>iFaceList</tt>.
* @param iFaceList
* The list of faces whose surface is transformed into a NURBS surface.
* Notice that all the faces must belong to the body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopSurToNurbsSurOperator *CATCGMCreateTopSurToNurbsSurOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATLISTP(CATFace) *iFaceList);

#endif /* CATICGMTopSurToNurbsSurOperator_h_ */
