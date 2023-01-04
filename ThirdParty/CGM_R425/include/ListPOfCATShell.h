#ifndef ListPOfCATShell_h
#define ListPOfCATShell_h
// COPYRIGHT DASSAULT SYSTEMES  2008

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

class CATShell;
//
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
CATLISTPP_DECLARE_TS(CATShell, 10)
/** @nodoc */
typedef CATLISTP(CATShell) ListPOfCATShell;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the shells of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput&, const ListPOfCATShell&);

#endif
