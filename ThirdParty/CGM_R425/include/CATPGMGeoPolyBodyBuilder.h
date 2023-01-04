/* -*-C++-*-*/
#ifndef CATPGMGeoPolyBodyBuilder_H
#define CATPGMGeoPolyBodyBuilder_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2022
//
// CATPGMGeoPolyBodyBuilder 
//
// DESCRIPTION :
// Utility class to convert CATPolyBody / CATIPolySurface instances ...
// ... with matrix into CATGeoPolyBody instances
// The conversion of a same entity with several matrices will lead to generate
// several CATGeoPolyBody instances referencing a common shared CATPolyBody
//
//=============================================================================

// For Windows NT export
#include "CATGMOperatorsInterfaces.h" // ExportedBy
#include "CATErrorDef.h"              // HRESULT
#include "CATTopDefine.h"             // CATOrientation
#include "CATSysDataType.h"           // NULL

#include "CATBoolean.h" 
#include "CATSysBoolean.h" 

class CATSoftwareConfiguration;
class CATMathTransformation;
class CATGeoFactory;
class CATGeoPolyBody;
class CATPolyBody;
class CATIPolySurface;


class ExportedByCATGMOperatorsInterfaces CATPGMGeoPolyBodyBuilder
{
public:

  /**
  * Destructor
  */
  virtual ~CATPGMGeoPolyBodyBuilder();


  //=============================================================================
  // Settings
  //=============================================================================
   


  //=============================================================================
  // Computation
  //=============================================================================


  /**
  * @param iPolyBodyToConvert
  * The input CATPolyBody to convert into a CATGeoPolyBody
  * If the input CATPolyBody is not native, a duplication will be applied into a native one.
  * @param iMatrix
  * The optional matrix associated to iPolyBodyToConvert which will be included in the output CATGeoPolyBody.
  * @param iExclusiveMode
  * In default mode (not exclusive), if the input CATPolyBody is not native, 
  *    the builder will retain the input CATPolyBody and its associated native CATPolyBody 
  *    in order to reuse it if the Run is recalled with another matrix.
  * In exclusive mode, the data won't be retained by the builder, the association won't be recorded, 
  *    a new CATPolyBody will be generated and won't be shared with any other CATGeoPolyBody.
  * The exclusive mode will be ignored in case of native CATPolyBody.
  * @return [CATGeoPolyBody*]
  * The pointer to the generated CATGeoPolyBody,
  * to be removed after use from the CATGeoFactory with its Remove() API.
  */
  virtual CATGeoPolyBody * Run(CATPolyBody * iPolyBodyToConvert, const CATMathTransformation * iMatrix=NULL, CATBoolean iExclusiveMode=FALSE) = 0;

    
  /**
  * @param iPolySurfaceToConvert
  * The input mesh to convert into a CATGeoPolyBody
  * If the input CATIPolySurface is not native, a duplication will be applied into a native one.
  * @param iMatrix
  * The optional matrix associated to iPolySurfaceToConvert which will be included in the output CATGeoPolyBody.
  * @param iExclusiveMode
  * In default mode (not exclusive), the builder will retain the input CATIPolySurface and its associated CATPolyBody 
  *    in order to reuse it if the Run is recalled with another matrix associated to the same input CATIPolySurface.
  * In exclusive mode, the data won't be retained by the builder, the association won't be recorded, 
  *    a new CATPolyBody will be generated and won't be shared with any other CATGeoPolyBody.
  * @return [CATGeoPolyBody*]
  * The pointer to the generated CATGeoPolyBody,
  * to be removed after use from the CATGeoFactory with its Remove() API.
  */
  virtual CATGeoPolyBody * Run(CATIPolySurface * iPolySurfaceToConvert, const CATMathTransformation * iMatrix=NULL, CATBoolean iExclusiveMode=FALSE) = 0;

};

/**
* Creates a CATPGMGeoPolyBodyBuilder.
* @param iTargetFactory
* The factory used to build the output CATGeoPolyBody
* @param iSoftwareConfig
* The pointer to the SoftwareConfiguration in order to drive the versionning of future modifications
* opened configuration (CGMVersion=LastCGMLevel) will be considered if iSoftwareConfig is set to null
* @return [out]
* The pointer to the created operator. To be deleted after use.
*/
ExportedByCATGMOperatorsInterfaces CATPGMGeoPolyBodyBuilder * CATPGMCreateGeoPolyBodyBuilder(CATGeoFactory * iTargetFactory, CATSoftwareConfiguration * iSoftwareConfig); 



#endif
