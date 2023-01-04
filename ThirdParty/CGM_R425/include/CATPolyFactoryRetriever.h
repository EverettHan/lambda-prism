//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//==============================================================================================================
// CATPolyFactoryRetriever : class used to handle the single implementation of CATIPolyFactory
//==============================================================================================================
// Creation : CHU , june 2004
//==============================================================================================================

#ifndef CATPolyFactoryRetriever_H
#define CATPolyFactoryRetriever_H

#include "CATIAV5Level.h"
#ifdef CATIAV5R15

#include "PolyFactoryImpl.h"
#include "CATPolyDeprecated.h"

class CATIPolyFactory;
class CATPolyFactoryImpl;

/**
 * DEPRECATED. DO NOT USE.
 */ 

class ExportedByPolyFactoryImpl CATPolyFactoryRetriever
{

public:
 
  // DEPRECATED. DO NOT USE.
  // Get a new interface to the single CATPolyFactoryImpl object, and create this object if it does not exist
  // When the interface returned is no longer used, it should be released (releasing the factory interface
  // will not release the implementation)
  POLY_DEPRECATED("Do not use. Use CATPolyMeshImpl::New instead.", static CATIPolyFactory * GetPolyFactory());

  static void DestroyFactory();

private:

  static CATPolyFactoryImpl * _TheUniquePolyFactory;

};
#endif
#endif
