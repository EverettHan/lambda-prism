#ifndef CATCGMCreateTopProject_h_
#define CATCGMCreateTopProject_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"

class CATICGMHybProject;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATMathDirection;

/**
* Constructs an operator that projects a domain on a domain.
* <br>This operator allows you to project 
* <ul><li>a VertexInVolume on a wire or a shell
* <li> a wire on a shell.
* </ul>
* <b>Orientation</b> in case of the projection of a wire on a shell:
* the orientation of two points on the resulting wire is the same as
* the orientation of the points from which they are projected.
* <br><b>Journal</b>: 
*<ul>
* <li>Edges are written as created (<tt>CATCGMJournal::Creation</tt> enumerated value) from their corresponding
* edge (in the body to project) and face (on the body support).
* <li>The first and last vertices are written as created (<tt>CATCGMJournal::Creation</tt> enumerated value).
* </ul>
* @param iFactory
* The pointer to the factory of the geometry.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iBodyToProject
* The pointer to the body to project. It can contain several 
* domains. In this case, the operator only projects the domains of highest dimension.
* @param iBodySupport
* The pointer to the support body. It can contain several 
* domains. In this case, the operator only projects on the domains of highest dimension.
* @param iDirection
* The direction of the projection. If <tt>NULL</tt>, the projection is normal to the surface.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybProject *CATCGMCreateTopProject(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToProject,
  CATBody *iBodySupport,
  CATMathDirection *iDirection = (CATMathDirection*)0);

#endif /* CATCGMCreateTopProject_h_ */
