// COPYRIGHT DASSAULT SYSTEMES  2000
// EDS

#ifndef __ListPOfListPOfCATPersistentFaces_h__
#define __ListPOfListPOfCATPersistentFaces_h__

#include "CATCGMLISTPP_Declare.h"
#include "PersistentCell.h"
#include "ListPOfCATPersistentFaces.h"

CATCGMLISTPP_DECLARE(ListPOfCATPersistentFaces);

typedef CATLISTP(ListPOfCATPersistentFaces) ListPOfListPOfCATPersistentFaces;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of all the faces of the lists.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByPersistentCell CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATPersistentFaces& iToWrite);

#endif
