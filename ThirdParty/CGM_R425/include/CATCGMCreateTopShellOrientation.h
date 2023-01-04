#ifndef CATCGMCreateTopShellOrientation_h_
#define CATCGMCreateTopShellOrientation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"

class CATICGMTopShellOrientation;
class CATGeoFactory;
class CATTopData;
class CATBody;

/*
 * Constructs the CATICGMTopShellOrientation operator. The CATICGMTopShellOrientation operator
 * inverts the orientation of the faces of a shell as well as the underlying surfaces 
 * so that all the faces and surfaces have the same orientation as the shell. 
 * @param iFactory
 * A pointer to the factory of the resulting body.
 * @param iData
 * A pointer to the topological data.
 * @param inputBody
 * A pointer to the body which contains the shell to be processed.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopShellOrientation *CATCGMCreateTopShellOrientation(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *inputBody);

#endif /* CATCGMCreateTopShellOrientation_h_ */
