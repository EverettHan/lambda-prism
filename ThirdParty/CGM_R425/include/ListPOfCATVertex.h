#ifndef ListPOfCATVertex_h
#define ListPOfCATVertex_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

class CATVertex;
/** 
 * @collection CATLISTP(CATVertex)
 * Collection class for pointers to (topological) vertices.
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
CATLISTPP_DECLARE_TS(CATVertex, 10)
/** @nodoc */
typedef CATLISTP(CATVertex) ListPOfCATVertex;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of the vertices of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATVertex& iToWrite);

#endif
