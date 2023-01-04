#ifndef CATCGMPointerPList_h
#define CATCGMPointerPList_h

/**
* @COPYRIGHT DASSAULT SYSTEMES 2019
*/
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************

#include "CATMathematics.h"

#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATMathematics

CATLISTPP_DECLARE_TNS(void, CGMVoidP, 10)
typedef CATListPtrCGMVoidP CATCGMPointerPList;

#endif
