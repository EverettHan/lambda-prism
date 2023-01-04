//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================

#ifndef		CATListOfCATCGMCreateVersion_h
#define		CATListOfCATCGMCreateVersion_h

////////////////////////////////////////////////////////////////////////////////
//
//	Class :		CATListOfCATCGMCreateVersion 
//	=====
//
//	Purpose :	List of pointers to static member s
//	=======		
//		  
//
//	Authors : 	Philippe	BAUCHER
//	=======
//
//
////////////////////////////////////////////////////////////////////////////////

#include  "CATCollec.h"

#include  "CATRCOLL_Clean.h"
#include  "CATRCOLL_AllFunct.h"
//
#undef	CATRCOLL_ValCompare
#undef	CATRCOLL_ValQuickSort
#define	CATRCOLL_RemoveNulls
#define	CATRCOLL_PtrCompare
#define	CATRCOLL_PtrQuickSort
#define	CATRCOLL_PtrApplyGlobalFunct

#include  "ExportedByCATCGMFusion.h"
#undef	CATCOLLEC_ExportedBy
#define	CATCOLLEC_ExportedBy	ExportedByCATCGMFusion

#include  "CATRCOLL_Declare.h"
CATRCOLL_DECLARE( CATCGMCreateVersion )

typedef     CATRCOLL( CATCGMCreateVersion )     CATListOfCATCGMCreateVersion ;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy

#endif		/* CATListOfCATCGMCreateVersion_h */
//automate:07/09/99:suppression include de CATCGMVersionDefinition.h
