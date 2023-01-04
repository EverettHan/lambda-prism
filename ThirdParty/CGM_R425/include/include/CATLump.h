#ifndef CATLump_H
#define CATLump_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATDomain.h"    // Class derivation
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATLump ;
#else
extern "C" const IID IID_CATLump ;
#endif

/**
 * Interface representing a topological domain of dimension 3.
 *<br> It contains connected CATVolume.
 * A CATLump is created with the @href CATBody#CreateLump or @href CATBody#CreateDomain methods
 * and deleted with the @href CATICGMContainer#Remove method.
 */
class ExportedByCATGMModelInterfaces CATLump : public CATDomain
{

  CATDeclareInterface;

  public :

};

CATDeclareHandler(CATLump,CATDomain);

#endif // CATLump_H
