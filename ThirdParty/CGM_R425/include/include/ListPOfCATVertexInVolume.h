#ifndef ListPOfCATVertexInVolume_h
#define ListPOfCATVertexInVolume_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATVertexInVolume;

/** 
 * @collection CATLISTP(CATVertexInVolume)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATVertexInVolume);

typedef CATLISTP(CATVertexInVolume) ListPOfCATVertexInVolume;

class CATCGMOutput;
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput&, const ListPOfCATVertexInVolume&);

#endif
