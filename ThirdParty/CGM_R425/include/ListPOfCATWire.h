#ifndef ListPOfCATWire_h
#define ListPOfCATWire_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
class CATWire;
/** 
 * @collection CATLISTP(CATWire)
 * Collection class for pointers to wires.
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
CATLISTPP_DECLARE_TS(CATWire, 10)
typedef CATLISTP(CATWire) ListPOfCATWire;

class CATCGMOutput;
/**
 * DO NOT USE
 * Writes the tags of the wires of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATWire& iToWrite);

#endif
