#ifndef CATVertexInVolume_H
#define CATVertexInVolume_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATDomain.h"
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATVertexInVolume ;
#else
extern "C" const IID IID_CATVertexInVolume ;
#endif

/**
 * Interface representing a vertex immersed 
 * into a volume or direcly referenced by a body.<br>A CATVertexInVolume is created with
 * the @href CATBody#CreateVertexInVolume method and deleted with the @href CATICGMContainer#Remove method.
 */
class ExportedByCATGMModelInterfaces CATVertexInVolume : public CATDomain
{

  CATDeclareInterface;

  public :

};

CATDeclareHandler(CATVertexInVolume,CATDomain);

#endif // CATVertexInVolume_H
