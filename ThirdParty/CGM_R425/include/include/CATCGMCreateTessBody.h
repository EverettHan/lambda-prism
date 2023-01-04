#ifndef CATCGMCreateTessBody_h_
#define CATCGMCreateTessBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @C_A_A_2_Level L1 // To be activated when moved to PublicInterfaces.(Remove the underscores '_' to activate)
 * @C_A_A_2_Usage U1
*/

#include "CATGMModelInterfaces.h"

class CATCGMTessBody;
class CATBody;
class CATCGMTessellateParam;
class CATSoftwareConfiguration;

/**
 * Creates an instance of CATCGMTessBody from a CATBody and the tessellation parameters.
 * Max Deviation (Sag) and Max Step should be greater than the container resolution value. 
 *
 * In the returned instance, the computation of the discrete data is done by tessellation.
 *
 * @param iBody
 *   The input CATBody to tessellate.
 * @param iSoftwareConfig
 *   The input Software Configuration.
 * @param iTessellateParam
 *   The tessellation parameters.
 * @param iMode
 *   0: tessellation will be done immediately for the entire body.
 *   1: tessellation will be done cell by cell on demand (while calling serializer).
 * @param iPrecision
 *   0: output vertex positions in float.
 *   1: output vertex positions in double.
 * @return
 *   An instance of a CATCGMTessBody. Null if creation issue.
 *
 * Tessellation data is given back using Serializers : CATCGMTessBodySerializer/CATCGMTessBodyFaceSerializer/CATCGMTessBodyEdgeSerializer/CATCGMTessBodyVertexSerializer
 */
ExportedByCATGMModelInterfaces CATCGMTessBody *CATCGMCreateTessBody(CATBody &iBody, CATSoftwareConfiguration* iSoftwareConfig, const CATCGMTessellateParam &iTessellateParam, int iMode=0, int iPrecision=1);


#endif /* CATCGMCreateTessBody_h_ */
