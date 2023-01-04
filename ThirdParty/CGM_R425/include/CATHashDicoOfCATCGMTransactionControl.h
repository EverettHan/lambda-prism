// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
//	Class :		CATHashDicoOfCATCGMTransactionControl
//	=====
//
//	Purpose :	Hash-Dico of instances of class CATCGMTransactionControl
//	=======
//
//=============================================================================
#ifndef	CATHashDicoOfCATCGMTransactionControl_h
#define	CATHashDicoOfCATCGMTransactionControl_h

// type of elements
class CATCGMTransactionControl ;

// clean previous functions requests
#include "CATHDICO_Clean.h"
#include "CATHDICO_AllFunct.h"
#include "CATHDICO_Declare.h"

// exporting module
#include "ExportedByGeometricObjects.h"
#undef	CATCOLLEC_ExportedBy
#define	CATCOLLEC_ExportedBy	ExportedByGeometricObjects
//
// generate interface of collection-class
// (functions declarations)
//
CATHDICO_DECLARE( CATCGMTransactionControl )
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy

#endif	// CATHashDicoOfCATCGMTransactionControl_h
