//#ifndef CATCGMCreateATessBody_h_
//#define CATCGMCreateATessBody_h_
//
//// COPYRIGHT DASSAULT SYSTEMES 2015
//
///**
// * @C_A_A_2_Level L1 // To be activated when moved to PublicInterfaces.(Remove the underscores '_' to activate)
// * @C_A_A_2_Usage U1
//*/
//
//#include "CATGMModelInterfaces.h"
//
//class CATCGMTessBody;
//class CATBody;
//class CATCGMTessellateParam;
//
///**
// * Creates an instance of CATCGMTessBody from a CATBody and the tessellation parameters.
// *
// * In the returned instance, the computation of the discrete data is done by tessellation.
// *
// * @param iBody
// *   The input CATBody to tessellate.
// * @param iTessellateParam
// *   The tessellation parameters.
// * @param iMode
// *   0: tessellation will be done immediately for the entire body.
// *   1: tessellation will be done cell by cell on demand (while calling serializer).
// * @return
// *   An instance of a CATCGMTessBody.
// *
// * Tessellation data is given back using Serializers : CATCGMTessBodySerializer/CATCGMTessBodyFaceSerializer/CATCGMTessBodyEdgeSerializer/CATCGMTessBodyVertexSerializer
// */
//ExportedByCATGMModelInterfaces CATCGMTessBody *CATCGMCreateATessBody(CATBody &iBody, const CATCGMTessellateParam &iTessellateParam, int iMode=0);
//
//
//#endif /* CATCGMCreateATessBody_h_ */
