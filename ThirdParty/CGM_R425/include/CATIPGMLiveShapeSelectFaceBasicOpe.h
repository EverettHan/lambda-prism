#ifndef CATIPGMLiveShapeSelectFaceBasicOpe_h_
#define CATIPGMLiveShapeSelectFaceBasicOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMAdvancedOperator.h"
#include "CATGMLiveShapeSelectFacePropagateMode.h"

class CATCellHashTable;
class CATGMLiveShapeSelectFaceBasicImpl;
class CATSoftwareConfiguration;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMLiveShapeSelectFaceBasicOpe;

/**
* This class is used to select faces with.<br>
**/
class ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeSelectFaceBasicOpe: public CATIPGMAdvancedOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMLiveShapeSelectFaceBasicOpe();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLiveShapeSelectFaceBasicOpe(); // -> delete can't be called
};

//==============================================================================
// Data
//==============================================================================
//==============================================================================
// CATGMLiveShapeSelectFaces
//==============================================================================
/**
* static methode to get the directly the ResultFaceList<br>
* <b>Legal Values</b>:<br>
*  <ul>
*    <li> <tt>iBody</tt> : The body of the face selection<br>
*   <li> <tt>iInputFaceList</tt> : The list of the fisrt faces selected<br>
*   <li> <tt>iPropagationMode</tt> : The type of propagation :<br>
*     <ul>
*     <li> PointContinuityPropagationMode,<br>
*     <li> TangencyContinuityPropagationMode,<br>
*     <li> DepressionPropagationMode,<br>
*     <li> ProtrusionPropagationMode,<br>
*      </ul>
*   <li> <tt>oResultFaceList</tt> : It's the result The list of the faces selected after propagation<br>
*   <li> <tt>iStoppingFaces</tt> : It's optional. The list of the face not to pass through. (Ribbon faces for exemple)<br>
*  </ul>
**/
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeSelectFacesBasic(
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  CATLISTP(CATFace) &oResultFaceList,
  CATLISTP(CATFace) *iStoppingFaces,
  CATBoolean iLiveBodyAllowed,
  CATSoftwareConfiguration *iConfig,
  CATBoolean iTestTypeMode = FALSE);

ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeSelectFacesBasic(
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  CATLISTP(CATFace) &oResultFaceList,
  CATLISTP(CATFace) &iSubBodyFilterFaceList,
  CATBoolean iLiveBodyAllowed,
  CATSoftwareConfiguration *iConfig);

//==============================================================================
// CATGMLiveShapeSelectFacesWithAnglePropagation
// For 2.3 degree, set 0.04 rad
// For 0.5 degree, set 0.0087 rad
// For 90  degree, set 1.57 rad
//==============================================================================
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeSelectFacesWithAnglePropagationBasic(
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATAngle iPropagationMaxRadAngle,
  CATLISTP(CATFace) &oResultFaceList,
  CATSoftwareConfiguration *iConfig,
  CATBoolean iLiveBodyAllowed = FALSE,
  CATLISTP(CATFace) *iSubBodyFilterFaceList = NULL);

//==============================================================================
// CATCreateLiveSelectFaceBasicOpe
//==============================================================================
/**
* Create operator, it call the constructor.<br>
* <b>Legal Values</b>:<br>
*  <ul>
*    <li> <tt>iTopData</tt> : It represents the information about the configuration and
*                the journal. If iTopData is NULL , the operator create it.<br>
*    <li> <tt>iBody</tt> : The body of the face selection<br>
*   <li> <tt>iInputFaceList</tt> : The list of the fisrt faces selected<br>
*   <li> <tt>iPropagationMode</tt> : The type of propagation :<br>
*     <ul>
*     <li> PointContinuityPropagationMode,<br>
*     <li> TangencyContinuityPropagationMode,<br>
*     <li> DepressionPropagationMode,<br>
*     <li> ProtrusionPropagationMode,<br>
*      </ul>
*   <li> <tt>iStoppingFaces</tt> : It's optional. The list of the face not to pass through. (Ribbon faces for exemple)<br>
*  </ul>
**/
// To be replaced by new constructor (I).
ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeSelectFaceBasicOpe *CATPGMCreateLiveSelectFaceBasicOpe(
  CATTopData *iTopData,
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  CATLISTP(CATFace) *iStoppingFaces = NULL);

// new constructor (I) with cells.
ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeSelectFaceBasicOpe *CATPGMCreateLiveSelectFaceBasicOpe(
  CATTopData *iTopData,
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  const CATLISTP(CATCell) *iStoppingCells);

#endif /* CATIPGMLiveShapeSelectFaceBasicOpe_h_ */
