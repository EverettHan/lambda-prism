/* -*-C++-*-*/
#ifndef CATCGMCompactObject_H
#define CATCGMCompactObject_H
//=============================================================================
// COPYRIGHT : DASSAULT SYSTEMES 2001
//
//  
//=============================================================================
// Abstract Class     : No
// Inline Functions   : No
//=============================================================================
//
// June 2001  TCX 
//
//=============================================================================
#include <stdlib.h>
#include <stddef.h>

#include "CATBaseUnknown.h"
#include "ExportedByGeometricObjects.h"
#include "CATCGMNewInterface.h"
#include "CATDataType.h"

#define CATCGMCompactObjectSizeInPointer ( ( sizeof(CATBaseUnknown) + sizeof(void *) - 1 ) / sizeof(void *) )

union CATCGMInterfaceForCompactObject
{
  struct CATCGMSimulateInterface
  {
    void           *vftable;
    CATBaseUnknown *impl;
    CATLONG32            m_cRef;
    CATBaseUnknown *delegate;
  } 
  CATCGMCompactItf;

  void *CATCGMCompactArray[ CATCGMCompactObjectSizeInPointer ]; 
};

//------------------------------------------------------------
// Overloaded operator new 
//------------------------------------------------------------
#if defined ( CATCGMCompactObject ) 

class CATCGMCompactObjectImplement : public CATBaseUnknown
{
public :
  CATULONGPTR _Container; // ...
  CATULONGPTR _DynObject; // Marqueur ...
};
 

#endif


#endif
