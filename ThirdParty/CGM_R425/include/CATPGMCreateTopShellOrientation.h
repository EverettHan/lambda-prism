#ifndef CATPGMCreateTopShellOrientation_h_
#define CATPGMCreateTopShellOrientation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATIPGMTopShellOrientation;
class CATGeoFactory;
class CATTopData;
class CATBody;

/**
 * @level Protected
 * @usage U1
 */
/*
 * Constructs the CATTopShellOrientation operator. The CATTopShellOrientation operator
 * inverts the orientation of the faces of a shell as well as the underlying surfaces 
 * so that all the faces and surfaces have the same orientation as the shell. 
 * @param iFactory
 * A pointer to the factory of the resulting body.
 * @param iData
 * A pointer to the topological data.
 * @param inputBody
 * A pointer to the body which contains the shell to be processed.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopShellOrientation *CATPGMCreateTopShellOrientation(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *inputBody);

#endif /* CATPGMCreateTopShellOrientation_h_ */
