#ifndef CATCGMConcatenateNurbsTool_h_
#define CATCGMConcatenateNurbsTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "CATDataType.h"

class CATKnotVector;
class CATMathGridOfPoints;
class CATMathSetOfPoints;
class CATLISTP(CATSurface);
class CATLISTP(CATCurve);

/**
* Computes the data required for the C0-concatenation of a list of Nurbs curves. 
* @param iCurveList
* The list of Nurbs curves to be concatenated. The input curves must be of
* CATNurbsCurve type and C0 connected. In the input curve list, the curves must be
* sorted according to their parametrization,
* from the smallest to the biggest parameter.
* @param ioControlPoints
* The output set of control points. 
* @param ioWeights
* The output array of weights.
* @param ioKnotVector
* The output knot vector.  
* @return
* The returned diagnosis.
* <br><b>Legal values</b>:
* <dl><dt><tt>TRUE</tt> <dd> Concatenation is OK
*     <dt><tt>FALSE</tt> <dd> Concatenation failed</dl>
*/
ExportedByCATGMModelInterfaces CATBoolean CATCGMConcatenateNurbsCurves(
  CATLISTP(CATCurve) *iCurveList,
  CATMathSetOfPoints *&ioControlPoints,
  double *&ioWeights,
  CATKnotVector *&ioKnotVector);

/**
* Computes the data required for the C0-concatenation of a list of Nurbs curves. 
* @param iSurfList
* The list of Nurbs surfaces to be concatenated. The input surfaces 
* must be of CATNurbsCurve type and C0 connected. The surface list 
* defines a matrix of surfaces in which 
* lines correspond to U direction, sorted from smallest U to biggest U, and 
* rows correspond to V direction, sorted from smallest V to biggest V.
* The list is filled row after row.
* @param iNbSurfacesU
* The number of surfaces along the U direction.
* @param iNbSurfacesV
* The number of surfaces along the V direction.
* @param ioControlPoints
* The grid of control points. 
* @param ioWeights
* The array of weights.
* @param ioKnotVectorU
* The knot vector along the U direction.
* @param ioKnotVectorV
* The knot vector along the V direction.
* @return
* The returned diagnosis. 
* <br><b>Legal values</b>:
* <dl><dt><tt>TRUE</tt> <dd> Concatenation is OK
*     <dt><tt>FALSE</tt> <dd> Concatenation failed </dl>
*/
ExportedByCATGMModelInterfaces CATBoolean CATCGMConcatenateNurbsSurfaces(
  CATLISTP(CATSurface) *iSurfList,
  CATLONG32 iNbSurfacesU,
  CATLONG32 iNbSurfacesV,
  CATMathGridOfPoints *&ioControlPoints,
  double *&ioWeights,
  CATKnotVector *&ioKnotVectorU,
  CATKnotVector *&ioKnotVectorV);

#endif /* CATCGMConcatenateNurbsTool_h_ */
