#ifndef __CATCreateRecomposeShells_h__ 
#define __CATCreateRecomposeShells_h__ 

// COPYRIGHT DASSAULT SYSTEMES  2003

/**
* @level Protected
* @usage U1
*/ 

#include "ExportedByCATTopologicalObjects.h"

class CATRecomposeShells;
class CATGeoFactory;
class CATBody;
class CATTopData;

/**
 * Creates a CATRecomposeShells operator.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBodyToRecompose
 * The pointer to the body to be recomposed.
 * @return
 * The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator after use.
 * @see CATRecomposeShells
 */
ExportedByCATTopologicalObjects CATRecomposeShells *
CATCreateRecomposeShells(CATGeoFactory * iFactory,
                         CATTopData    * iData,
                         CATBody       * iBodyToRecompose);

#endif






