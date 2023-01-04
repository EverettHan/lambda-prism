#ifndef CATVertexInFace_H
#define CATVertexInFace_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATDomain.h" 
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATVertexInFace ;
#else
extern "C" const IID IID_CATVertexInFace ;
#endif

/**
 * Interface representing a vertex immersed 
 * into a face.<br> This is a case of non-manifold topology. A CATVertexInFace is created with 
 * the @href CATBody#CreateVertexInFace method and deleted with the @href CATICGMContainer#Remove method.
 */
class ExportedByCATGMModelInterfaces CATVertexInFace : public CATDomain
{

  CATDeclareInterface;

  public :

};

CATDeclareHandler(CATVertexInFace,CATDomain);

#endif // CATVertexInFace_H
