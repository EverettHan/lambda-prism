#ifndef ListPOfCATManifoldAttribute_h
#define ListPOfCATManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2007

class CATManifoldAttribute;
/** 
 * @collection CATLISTP(CATManifoldAttribute)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"
#include "CATIACGMLevel.h"
//
// generate interface of collection class
// (functions declarations)
#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#ifdef CATIACGMV5R20
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
#else
#define CATCOLLEC_ExportedBy ExportedByYI00IMPL
#endif

/** @nodoc */
CATLISTPP_DECLARE_TS(CATManifoldAttribute, 2)
/** @nodoc */
typedef CATLISTP(CATManifoldAttribute) ListPOfCATManifoldAttribute;

#endif
