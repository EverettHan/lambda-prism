// COPYRIGHT DASSAULT SYSTEMES 1996
//=============================================================================
//
// CATSubdInternalError:
// Gestion des erreurs internes du framework TopologicalOperators
//
//=============================================================================
// Usage notes:
//
// 
//=============================================================================
// Oct. 96  Creation                          I. Chauvigne, X. Dupont, L. Laloy
//=============================================================================

#ifndef CATSubdInternalError_H
#define CATSubdInternalError_H

#include "CATErrors.h"
#include "CATSubdErrors.h"
#include "CATSubdBlockThrow.h"
#include "CATCGMInternalError.h"


#include "BOOERROR.h"

//-----------------------------------------------------------------------------
class ExportedByBOOERROR CATSubdInternalError : public CATCGMInternalError 
{
  public:
    //------
    // Constructors
    //------
    CATDeclareErrorClass(CATSubdInternalError, CATCGMInternalError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
