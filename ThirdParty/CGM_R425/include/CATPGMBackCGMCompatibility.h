#ifndef CATPGMBackCGMCompatibility_h_
#define CATPGMBackCGMCompatibility_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"

class CATICGMObject;
class CATICGMContainer;

/**
 * @brief     Tool class to check compatibilty of CGM objects or CGM container inside the CATBack process.
 * @date      W17-Y2021
 * @author    YL3 and LAP
 */
class ExportedByCATGMModelInterfaces CATPGMBackCGMCompatibility
{
public:
  /**
  * @brief   Check designed for CATBack as Result with the level from VersionManagement.<br>
   *          CATBack as Result : From level to lower level. The body will be associated with datum feature only.<br>
   *          It's used by CDM and inside the CATBodyDatumiser.
   * @param   iObject
   *          Object to check. It is often a CATBody, but it could be an other type.
   * @return
   *          TRUE  : If the object is compatible for a CATBack.<br>
   *          FALSE : Otherwise. For example if the CATBody is a Polyhedral, it is not allowed to be streamed in V5.
   */
  static CATBoolean IsCompatible(CATICGMObject *iObject);

  /**
   * @brief   Check designed for CATBack as Spec with the level from VersionManagement.<br>
   *          CATBack as Spec : From 3DEXPERIENCE to synchronized V5.<br>
   *          Only use for fast detection of only compatible objects.<br>
   *          Warning : Some incompatible objects could be not pointed by feature, for example temporary bodies not involed in the stream process.<br>
   *          So if it return FALSE, you have to check all features of the tree to check only objects involed in the stream process.
   * @param   iCGMContainer
   *          The container to check. It should be the explicit factory.
   * @return
   *          TRUE : If we are sure that all CATBody are compatible.<br>
   *          FALSE : Otherwise. For example if there is an Polyhedral CATBody in the container, it returns FALSE because it is not allowed in V5.<br>
   *          An other example, if there is a CATGeoPolyBody in the container, it returns FALSE.
   */
  static CATBoolean IsCompatible(CATICGMContainer* iCGMContainer);
};

#endif /* CATPGMBackCGMCompatibility_h_ */
