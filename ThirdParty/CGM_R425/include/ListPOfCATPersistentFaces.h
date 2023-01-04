#ifndef ListPOfCATPersistentFaces_H
#define ListPOfCATPersistentFaces_H
//=============================================================================
// COPYRIGHT Dassault Systemes 2004
//=============================================================================
//
// ListPOfCATPersistentFaces.h
// 		
//=============================================================================
//  Sep 07, 2004        BPG
//      * (GetFacesRepresentationInContainer): New.
//  Feb 2004  Creation: JHG
//=============================================================================

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATPersistentFace;
class CATAutoBaseThreadContext;

/** 
 * @collection CATLISTP(CATPersistentFace)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATPersistentFace);

typedef CATLISTP(CATPersistentFace) ListPOfCATPersistentFaces;

class CATPersistentBody;


#endif // !ListPOfCATPersistentFaces_H
