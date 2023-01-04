#ifndef CATIPGMLiveShapeSelectFaceOpe_h_
#define CATIPGMLiveShapeSelectFaceOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMLiveShapeSelectFaceBasicOpe.h"

class CATBody;
class CATFace;
class CATFaceHashTable;
class CATGMLiveShapeSelectFaceImpl;
class CATPersistentBody;
class CATPersistentCellInfra;
class CATSoftwareConfiguration;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMLiveShapeSelectFaceOpe;

/*
// In order to update GMOperatorsInterfaces/ProtectedInterfaces/CATIPGMLiveShapeSelectFaceOpe.h:
class CATGMLiveShapeSelectFacePropagateMode;
class CATAngle;
*/
/**
* This class is used to select faces with.<br>
**/
class ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeSelectFaceOpe: public CATIPGMLiveShapeSelectFaceBasicOpe
{
public:
  /**
   * Constructor
   */
  CATIPGMLiveShapeSelectFaceOpe();

  // Set math transformation (for extended selection mode)
  virtual void SetMathTransformation(const CATMathTransformation *ipTransfo) = 0;

  //==============================================================================
  // GetFaceListResult
  //==============================================================================
  virtual void GetFaceListResult(CATLISTP(CATFace) &oResultFaceList) = 0;

  static const char *GetPropagationName(
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode);

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLiveShapeSelectFaceOpe(); // -> delete can't be called
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
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeSelectFaces(
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  CATLISTP(CATFace) &oResultFaceList,
  CATLISTP(CATFace) *iStoppingFaces,
  CATBoolean iLiveBodyAllowed,
  CATSoftwareConfiguration *iConfig,
  CATBoolean iTestTypeMode = FALSE);

//==============================================================================
// CATGMLiveShapeSelectFacesWithAnglePropagation
// For 2.3 degree, set 0.04 rad
// For 0.5 degree, set 0.0087 rad
// For 90  degree, set 1.57 rad
//==============================================================================
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeSelectFacesWithAnglePropagation(
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATAngle iPropagationMaxRadAngle,
  CATLISTP(CATFace) &oResultFaceList,
  CATSoftwareConfiguration *iConfig,
  CATBoolean iLiveBodyAllowed = FALSE);

//==============================================================================
// CATGMLiveShapeSelectFacesWithAngleByConvexityPropagation
//==============================================================================
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeSelectFacesWithAngleByConvexityPropagation(
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATAngle iPropagationMaxRadConvexAngle,
  CATAngle iPropagationMaxRadConcaveAngle,
  CATLISTP(CATFace) &oResultFaceList,
  CATSoftwareConfiguration *iConfig,
  CATBoolean iLiveBodyAllowed = FALSE,
  CATLISTP(CATFace) *iStoppingFaces = NULL);

//==============================================================================
// CATGMLiveShapeSelectFacesInRangeRibbons
/**
* Static method to get the directly the ResultFaceList
* @Param iBody
*    Mandatory : Must be a CATLiveBody. 
*
* CATGMLiveShapeSelectFacesRangeRibbons operates on all faces of the body and doesn't compute any propagation.
* It returns a list of ribbbon faces with radiuses between iMinRadius and iMaxRadius.
* 
* @Param iSubBodyFaceList 
*		 Optional. If set, only thoses faces will be considered for the computation. 
*/
//==============================================================================
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeSelectFacesInRangeRibbons(
  CATSoftwareConfiguration *iConfig,
  CATBody *iBody,
  double iMinRadius,
  double iMaxRadius,
  CATLISTP(CATFace) &oResultFaceList,
  const CATLISTP(CATFace) *iSubBodyFaceList = NULL);

//==============================================================================
// CATGMLiveShapeSelectFacesWithMoveExtension
/**
* Static method to get the directly the ResultFaceList
* 
* @Param	iBody
*    Mandatory : Must be a CATLiveBody.
* @Param	iInputFaceList
*		List of input selected faces.
* @Param	ipMathTransformation
*		Mandatory : input math transformation applied to selected faces.
* @Param	oResultFaceList
*		List of suggested faces to be added to the selection.
*
* CATGMLiveShapeSelectFacesWithMoveExtension extends the selection to faces which 
* can be impacted by the math transformation.
* 
* The selected and suggested face are returned in an output list of faces (oResultFaceList).
* 
* @author YSY2
* @date		w06-y2020
*/
//==============================================================================
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeSelectFacesWithMoveExtension(
  CATSoftwareConfiguration *iConfig,
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  const CATMathTransformation *ipMathTransformation,
  CATLISTP(CATFace) &oResultFaceList);

//==============================================================================
// CATCreateLiveSelectFaceOpe
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
ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeSelectFaceOpe *CATPGMCreateLiveSelectFaceOpe(
  CATTopData *iTopData,
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  CATLISTP(CATFace) *iStoppingFaces = NULL);

// new constructor (I) with cells.
ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeSelectFaceOpe *CATPGMCreateLiveSelectFaceOpe(
  CATTopData *iTopData,
  CATBody *iBody,
  const CATLISTP(CATFace) &iInputFaceList,
  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  const CATLISTP(CATCell) *iStoppingCells);

// Constructor with HashTable
ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeSelectFaceOpe *CATPGMCreateLiveSelectFaceOpe(
  CATTopData *iTopData,
  CATBody *iBody,
  const CATFaceHashTable &iInputFaceHT,
  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  const CATCellHashTable *iStoppingCells = NULL);

// Constructor with a "Limiting Body" for CLSSF_DFT_LIMITING_DETECTION
ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeSelectFaceOpe * CATPGMCreateLiveSelectFaceOpe(
  CATTopData                            * iTopData,
  CATBody                               * iInputBody,
  CATBody                               * iLimitingBody,
  CATGMLiveShapeSelectFacePropagateMode   iPropagationMode=CLSSF_DFT_LIMITING_DETECTION,
  const CATLISTP(CATFace)               * iSubFaceList=NULL); // List to limit the scope to this list of faces

//==============================================================================
// CATLiveSelectFaceReverseDepressionProtrusion
//
//    October 2018
//    IT'S A PROTOTYPE FOR  A PATTERN. DON'T CALL IT.
//
//==============================================================================
// If return TRUE, the application should invert the notion of Depression and Protrusion
// when it calls the LiveShapeSelectFaceOpe.
//
// Parameters
//   i3DClickPoint   : It's the last point (x,y,z) of the click associated with the selected ipFace.
//   iSightDirection : Should comes from GetSightDirection().
//
// Example
//   1) The User wants a Depression propagation.
//   2) CATLiveSelectFaceReverseDepressionProtrusion returns TRUE.
//   3) The application calls the LiveShapeSelectFaceOpe with CLSSF_PROTRUSION.
// -----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBoolean CATPGMLiveSelectFaceReverseDepressionProtrusion(
  CATBody *ipBody,
  CATFace *ipFace,
  CATSoftwareConfiguration *ipConfig,
  CATMathPoint &i3DClickPoint,
  CATMathDirection &iSightDirection);

#endif /* CATIPGMLiveShapeSelectFaceOpe_h_ */
