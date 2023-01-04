// COPYRIGHT DASSAULT SYSTEMES 2019
//================================================================================
// Creation DLR6  01/04/2019
//
// Class to create an operator that expands one (or several) volume(s)
// so that they fill a bigger space.
//
//================================================================================


#ifndef CATCreateExpandVolumeToSkins_H 
#define CATCreateExpandVolumeToSkins_H 

#include "ExportedByCATTopologicalObjects.h"

class CATTopExpandVolumeToSkins;
class CATGeoFactory;
class CATTopData;
class CATBody;


/**
 * Creates a CATTopExpandVolumeToSkins operator.
 * @param iFactory
 * The pointer to the geometry factory. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iTrimmingBody
 * The input body.
 * @param iSkinBody
 * The skin body to be sewn onto the input body. 
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */

ExportedByCATTopologicalObjects CATTopExpandVolumeToSkins *
CATCreateExpandVolumeToSkins(
      CATGeoFactory * ipFactory,    CATTopData  * ipTopData,
      CATBody       * ipSolidBody,  CATBody     * ipSkinBody);

#endif
