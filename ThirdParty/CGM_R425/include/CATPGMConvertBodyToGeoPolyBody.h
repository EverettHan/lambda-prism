/* -*-C++-*-*/
#ifndef CATPGMConvertBodyToGeoPolyBody_H
#define CATPGMConvertBodyToGeoPolyBody_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2022
//
// CATPGMConvertBodyToGeoPolyBody 
//
// DESCRIPTION :
// Utility class to convert CATBody with matrix into CATGeoPolyBody instance
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
class CATBody;

class ExportedByCATGMOperatorsInterfaces CATPGMConvertBodyToGeoPolyBody
{
public:

  /**
  * Destructor
  */
  virtual ~CATPGMConvertBodyToGeoPolyBody();


  //=============================================================================
  // Settings
  //=============================================================================
   


  //=============================================================================
  // Computation
  //=============================================================================


  /**
  * @param iBodyToConvert
  * The input CATBody to convert into a CATGeoPolyBody
  * In case of continuous (exact) CATBody, a default tessellation will be applied.
  * @param iMatrix
  * The optional matrix associated to iBodyToConvert which will be included in the output CATGeoPolyBody.
  * @param iExclusiveMode
  * In default mode (not exclusive), the converter will retain the input CATBody and its associated CATPolyBody 
  *    in order to reuse it if the Run is recalled with another matrix associated to the same input CATBody.
  * In exclusive mode, the data won't be retained by the converter, the association won't be recorded, 
  *    a new CATPolyBody will be generated and won't be shared with any other CATGeoPolyBody.
  * @return [CATGeoPolyBody*]
  * The pointer to the generated CATGeoPolyBody,
  * to be removed after use from the CATGeoFactory with its Remove() API.
  */
  virtual CATGeoPolyBody * Run(CATBody * iBodyToConvert, const CATMathTransformation * iMatrix=NULL, CATBoolean iExclusiveMode=FALSE) = 0;

};

/**
* Creates a CATPGMConvertBodyToGeoPolyBody.
* @param iTargetFactory
* The factory used to build the output CATGeoPolyBody
* can be different from the factory attached to the CATBody to convert
* @param iSoftwareConfig
* The pointer to the SoftwareConfiguration in order to drive the versionning of future modifications
* opened configuration (CGMVersion=LastCGMLevel) will be considered if iSoftwareConfig is set to null
* @return [out]
* The pointer to the created operator. To be deleted after use.
*/
ExportedByCATGMOperatorsInterfaces CATPGMConvertBodyToGeoPolyBody * CATPGMCreateConvertBodyToGeoPolyBody(CATGeoFactory * iTargetFactory, CATSoftwareConfiguration * iSoftwareConfig); 



#endif
