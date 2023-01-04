#ifndef ListVOfCATFeaturePiece_h
#define ListVOfCATFeaturePiece_h

// COPYRIGHT DASSAULT SYSTEMES  2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATFeaturePiece.h"
#include "CATLISTV_Clean.h"
/** 
 * @collection CATLISTV(CATFeaturePiece)
 * Collection class for CATFeaturePiece objects.
 */
//
// generate interface of collection class
// (functions declarations)
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces


#define	CATLISTV_Append
#define	CATLISTV_AppendList

#include  "CATLISTV_Declare.h"

CATLISTV_DECLARE(CATFeaturePiece)

typedef CATLISTV(CATFeaturePiece) ListVOfCATFeaturePiece;

#endif
