#ifndef CATPGMCreateTopPoseSur_h_
#define CATPGMCreateTopPoseSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATIPGMHybProject;
class CATGeoFactory;
class CATTopData;
class CATBody;



// COPYRIGHT DASSAULT SYSTEMES  2000
//========================================================================
// 
//  PoseSur Operator Body onto Body : 
// 
//========================================================================
/**
* Constructs an operator that projects a domain on a domain and keep the solution only if the 
* distance is lower than the factory resolution.
* <br>This operator allows to project 
* <ul><li>a VertexInVolume on a wire or a shell
* <li> a wire on a shell.
* </ul>
* The body to project and the support body (on which the projection is made) can contain 
* several domains.
* <br><b>Orientation</b>:(In case of the projection of a wire on a shell).
* The orientation of two points on the resulting wire is the same as
* the orientation of the points from which they are projected.
* <br><b>Journal</b>: 
*<ul>
* <li>Edges are written as <tt>CATCGMJournal::Creation</tt> from their corresponding
* edge (in the body to project) and face (on the body support).
* <li>The first and last vertices are written as  <tt>CATCGMJournal::Creation</tt>.
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToProject
* A pointer to the body to project. If must only contain  one 
* domain.
* @param iBodySupport
* A pointer to the support body. It must only contain one
* domain.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMHybProject *CATPGMCreateTopPoseSur(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToProject,
  CATBody *iBodySupport);

#endif /* CATPGMCreateTopPoseSur_h_ */
