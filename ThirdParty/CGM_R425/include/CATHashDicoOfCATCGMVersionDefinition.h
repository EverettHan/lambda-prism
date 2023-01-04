// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
//	Class :		CATHashDicoOfCATCGMVersionDefinition
//	=====
//
//	Purpose :	Hash-Dico of instances of class CATCGMVersionDefinition
//	=======
//		  
//
//	Authors : 	Philippe	BAUCHER
//	=======
//
//
//	Abstract :	1- Generate a non-template collection-class with MACROS
//	========	   (documentation on "Hash-Coding Dictionnaries")
//
//=============================================================================
#ifndef	CATHashDicoOfCATCGMVersionDefinition_h
#define	CATHashDicoOfCATCGMVersionDefinition_h


// type of elements
class CATCGMVersionDefinition ;


// clean previous functions requests
#include "CATHDICO_Clean.h"

// require needed functions (except operator<< on ostream)
#include "CATHDICO_AllFunct.h"
#undef  CATHDICO_ostreamOP

// get macros
#include "CATHDICO_Declare.h"

// exporting module
#include "CGMObject.h"
#undef	CATCOLLEC_ExportedBy
#define	CATCOLLEC_ExportedBy	ExportedByCATCGMFusion

//
// generate interface of collection-class
// (functions declarations)
//
CATHDICO_DECLARE( CATCGMVersionDefinition )


#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy
#endif	// CATHashDicoOfCATCGMVersionDefinition_h
