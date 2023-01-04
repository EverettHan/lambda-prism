// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// Creation EDS  08/01/2002
//
// Methode permettant la creation d'une instance de l'operateur de relimitation
// d'elements d'un body (volumes, shells, wires, vertex in volume) par des
// volumes d'un autre body.
//
//=============================================================================

#ifndef __CATCreateRelimitByVolume_h__ 
#define __CATCreateRelimitByVolume_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopRelimitByVolume;
class CATGeoFactory;
class CATTopData;
class CATBody;


/**
* Global function to create an operator that trims a shell or a wire by a volume.
* The generated result is made up of the portions of the input shell or wire which are
* inside or outside the input volume. <br>
* The body to be trimmed can be a multi-domain body. The domains making up the input body do 
* not have necessarily to be of the same type. For example, the input body can contain a mixture of shells
* and lumps.<br>
* All the cells of the input body are trimmed by the volume and the portions to be kept
* are to be specifed by using the <tt>SetSelectionType</tt> method. Resulting sub-elements
* can be merged.
* <p>
* The CATTopRelimitByVolume operator is created with the <tt>CATCreateRelimitByVolume</tt> 
* global function and is directly released with the <tt>Release</tt> method.
* It is is not streamable. 
* <p>
* The CATTopRelimitByVolume operator is a multi-run operator: <br>
* the methods to set parameters as well as the <tt>Run</tt> and <tt>GetResult</tt> methods
* can be called several times from the same operator.
*  @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBodyToRelimit
* A pointer to the body to be trimmed or relimited.
* @param iSolidBody
* A pointer to the solid used as trimming object.
* @return [out, IUnknown#Release]
*/
ExportedByCATTopologicalObjects CATTopRelimitByVolume *
CATCreateRelimitByVolume(CATGeoFactory * iFactory,
                         CATTopData    * iTopData,
                         CATBody       * iBodyToRelimit,
                         CATBody       * iSolidBody);

#endif






