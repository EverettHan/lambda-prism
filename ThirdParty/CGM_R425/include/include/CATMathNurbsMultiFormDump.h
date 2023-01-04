#ifndef CATMathNurbsMultiFormDump_H   
#define CATMathNurbsMultiFormDump_H
// COPYRIGHT DASSAULT SYSTEMES 2015
//==========================================================================
//
// CATMathNurbsMultiFormDump: Dump utility for CATMathNurbsMultiForm
//------------------------------------------------------------------
// utilitaire de Dump
//
// N.B il faut un tout petit peu ruser pour introduire un Dump sur une sortie parametrable
//     car       CATMathNurbsMultiForm est dans PublicInterfaces
//     alors que CATCGMOutput          est dans ProtectedInterfaces
//
//     on cache donc le vrai utilitaire de Dump()           NLD200715
//-------------------------------------------------------------------
// 20/07/15 NLD Creation
// 21/07/17 NLD Ajout export et extern pour utilisation externe
//==========================================================================
#include "YP00IMPL.h"

#include "CATCGMOutput.h"
#include "CATMathNurbsMultiForm.h"

extern "C" ExportedByYP00IMPL
void         CATMathNurbsMultiFormDump(CATMathNurbsMultiForm* iNurbsMultiForm,
                                       CATCGMOutput         & os             );

#endif

