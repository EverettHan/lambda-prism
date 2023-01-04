#ifndef CATPGMCreateSkinBorderSorting_h_
#define CATPGMCreateSkinBorderSorting_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopSkinBorderSorting;
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

/** 
 * Creates the operator to compute the border edges of a skin .
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iBody
 * The pointer to the  body on which the edges are computed.
 * @param iInitialFaces
 * The pointer to the liste of faces  on which the edges are computed.
 * @param iWithSmoothPropagation
 * The boolean to decide whether the initial faces should be propagated
 * before border calculation.
 * @param iTopData
 * Data for this current operation. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSkinBorderSorting *CATPGMCreateSkinBorderSorting(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATLISTP(CATEdge) *iEdgesToSort,
  CATLISTP(CATFace) *iInitialFaces,
  CATLISTP(CATFace) *iPropagatedFaces);

#endif /* CATPGMCreateSkinBorderSorting_h_ */
