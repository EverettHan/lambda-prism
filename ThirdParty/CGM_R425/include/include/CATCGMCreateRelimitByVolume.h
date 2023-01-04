#ifndef CATCGMCreateRelimitByVolume_h_
#define CATCGMCreateRelimitByVolume_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATICGMTopRelimitByVolume;

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
* The CATICGMTopRelimitByVolume operator is created with the <tt>CATCGMCreateRelimitByVolume</tt> 
* global function and is directly released with the <tt>Release</tt> method.
* It is is not streamable. 
* <p>
* The CATICGMTopRelimitByVolume operator is a multi-run operator: <br>
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
ExportedByCATGMModelInterfaces CATICGMTopRelimitByVolume *CATCGMCreateRelimitByVolume(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyToRelimit,
  CATBody *iSolidBody);

#endif /* CATCGMCreateRelimitByVolume_h_ */
