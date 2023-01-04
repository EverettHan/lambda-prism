#ifndef ListPOfCATCldBody_h
#define ListPOfCATCldBody_h

// COPYRIGHT DASSAULT SYSTEMES  2017


class CATCldBody;
/** 
 * @collection CATLISTP(CATCldBody)
 * Collection class for pointers to (topological) bodies.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"
//
// generate interface of collection class
// (functions declarations)
#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
/** @nodoc */
CATLISTPP_DECLARE_TS(CATCldBody, 10)
/** @nodoc */
typedef CATLISTP(CATCldBody) ListPOfCATCldBody;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the bodies of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCldBody& iToWrite);

#endif
