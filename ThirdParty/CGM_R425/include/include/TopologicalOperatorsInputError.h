#ifndef TOPOLOGICALOPERATORSINPUTERROR_H
#define TOPOLOGICALOPERATORSINPUTERROR_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : TopologicalOperatorsInputError class declaration
//               
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInputError.h"

class ExportedByCATGMModelInterfaces TopologicalOperatorsInputError : public CATCGMInputError
{
  public:
    CATDeclareErrorClass(TopologicalOperatorsInputError, CATCGMInputError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};
//

#endif
