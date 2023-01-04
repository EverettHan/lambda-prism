#ifndef TOPOLOGICALOPERATORSINTERNALERROR_H
#define TOPOLOGICALOPERATORSINTERNALERROR_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : TopologicalOperatorsInternalError class declaration 
//               
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInternalError.h"

class  ExportedByCATGMModelInterfaces TopologicalOperatorsInternalError : public CATCGMInternalError
{
  public:
    CATDeclareErrorClass(TopologicalOperatorsInternalError, CATCGMInternalError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
