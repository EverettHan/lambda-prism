#ifndef CATPGMCreateTopProjection_h_
#define CATPGMCreateTopProjection_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATMathDirection;
class CATIPGMTopProjection;
class CATGeoFactory;
class CATTopData;
class CATBody;

/**
* Constructs an operator that projects a domain on a domain.
* <br>This operator allows you to project in 3D
* <ul><li>a VertexInVolume on a wire or a shell
* <li> a wire on a shell,
* <li> and to compute geodesic projection of a VertexInVolume on a wire
* <li> laid on a shell.
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
* @param iBodyShell
* The pointer to the shell body on which point and wire are laid down. Needed for geodesic projection.
* If <tt>NULL</tt>, the projection will be euclidean
* @param iDirection
* The direction of the projection. If <tt>NULL</tt>, the projection is normal to the surface.
* Not used by geodesic projection
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopProjection *CATPGMCreateTopProjection(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToProject,
  CATBody *iBodySupport,
  CATBody *iBodyShell = NULL,
  CATMathDirection *iDirection = (CATMathDirection*)0);

#endif /* CATPGMCreateTopProjection_h_ */
