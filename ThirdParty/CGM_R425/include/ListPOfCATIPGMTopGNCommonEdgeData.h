#ifndef ListPOfTCATIPGMTopGNCommonEdgeData_h
#define ListPOfTCATIPGMTopGNCommonEdgeData_h

// COPYRIGHT DASSAULT SYSTEMES  2011

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATIPGMTopGNCommonEdgeData;

/**
 * @collection CATLISTP(CATIPGMTopGNCommonEdgeData)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia.
 */

CATCGMLISTPP_DECLARE(CATIPGMTopGNCommonEdgeData);

typedef CATLISTP(CATIPGMTopGNCommonEdgeData) ListPOfCATIPGMTopGNCommonEdgeData;
//
//class CATCGMOutput;
///**
// * @nodoc
// * Writes the tags of the cell manifolds of the list.
// * @param iWhereToWrite
// * The output.
// * @param  iToWrite
// * The list to dump.
// */
//ExportedByCATGMModelInterfaces CATCGMOutput & operator<<(CATCGMOutput & iWhereToWrite, const ListPOfTCATIPGMTopGNCommonEdgeData & iToWrite);

#endif
