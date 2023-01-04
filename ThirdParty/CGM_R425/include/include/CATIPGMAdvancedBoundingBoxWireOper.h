#ifndef CATIPGMAdvancedBoundingBoxWireOper_h_
#define CATIPGMAdvancedBoundingBoxWireOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATMathDef.h" // CATLength

class CATBody;
class CATGeoFactory;
class CATMathAdvancedBox;
class CATMathDirection;
class CATMathPoint;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMAdvancedBoundingBoxWireOper;

class ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedBoundingBoxWireOper: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMAdvancedBoundingBoxWireOper();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
  Max Deviation settings
  By default, the operator will compute a max deviation value depending on the scale, = 1.000.000 times the model resolution
  The input value must be greater than a minimum value = 10.000 times the model resolution, depending on the current scale
*/
  virtual HRESULT SetFixedMaxDeviation(CATLength iFixedMaxDeviationValue) = 0;

  /**
  Direction settings
  Force result boxes to be extruded in a given canonical direction
  with the possibility to inflate each box up to infinite
  only 3 possible values for iCATMathIJK
  see const CATMathDirection CATMathI, CATMathJ, CATMathK defined in CATMathDirection.h
*/
  virtual HRESULT SetCanonicalDirection(
    const CATMathDirection &iCATMathIJK,
    CATBoolean iUpToLowInfinite = FALSE,
    CATBoolean iUpToHighInfinite = FALSE) = 0;

  /**
  Direction settings
  Build boxes in any given direction iDirection within a distance range along this direction.
  Distances are considered from the point iOrigin.
  One or two distances may be defined (notice that distances may be positive or negative here) :
  - If two distances are defined : boxes extremities in Direction iDirection are located at iSignedDistance1 and iSignedDistance2 from iOrigin.
  - If one distance is defined : the distance defined overrides the size of boxes resulting from the other specifications.
  - If no distance is defined : boxes are built according to the other specifications.
*/
  virtual HRESULT SetDirectionWithLimits(
	  const CATMathDirection & iDirection, 
	  const CATMathPoint & iOrigin, 
	  double * iSignedDistance1 = NULL, 
	  double * iSignedDistance2 = NULL) = 0;

  /**
  Inflate value settings
  By default, the inflate value will be applied in the 3 directions of each
  Oriented Box, excepted if a specific direction has been defined.
  In this case, the inflate will be applied in the 2 other directions only.
  A specific inflate can be applied to the bottom and top faces of the box,
  according to the defined oriented direction.
  These specifications will be ignored if the option “up to infinite” has been requested by SetCanonicalDirection()
*/
  virtual HRESULT SetInflateValues(
    CATLength iDefaultInflateValue,
    CATLength *iBottomInflateValue = NULL,
    CATLength *iTopInflateValue = NULL) = 0;

  //=============================================================================
  // Get additional information after Run
  //=============================================================================
  /**
* The pointer to the CATMathAdvancedBox, to be deleted by the caller after use
* Null if the request doesn't make sense because the input topological object doesn't define any bounding box
* 3 possible types (CATMathAdvancedBoxType) for the returned CATMathAdvancedBox
* CATMathAABBType     Axis Aligned Bounding Box
* CATMathOBBType      Oriented Bounding Box
* CATMathOBBCloudType Oriented Bounding Box Tree
*(CATMathOBB2DType    not supported by this function)
*/
  virtual CATMathAdvancedBox *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMAdvancedBoundingBoxWireOper(); // -> delete can't be called
};

/**
* CATCreateAdvancedBoundingBoxOper() function
* This function creates a CATIPGMAdvancedBoundingBoxWireOper to compute the advanced bounding box of a topological object.
* The CATMathAdvancedBox returned by GetAdvancedBox() might wrap an OBB, an OBBCloud or an AABB according to the specification of the smallest bounding box.
* See CATMathAdvancedBoxTypeEnum.h for the different types (CATMathOBB2DType is not supported by this function).
* This service is available for both exact and polyhedral objects.
* @param iFactory
* The pointer to the factory
* @param iConfig
* The pointer to the software configuration driving the versionning of code modifications
* @param iTopology
* The topological object defining a bounding box :
* CATBody, CATDomain, CATCell
* @return
* The pointer to the CATIPGMAdvancedBoundingBoxWireOper, to be deleted by the caller after use
*/
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedBoundingBoxWireOper *CATPGMCreateAdvancedBoundingBoxWireOper(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATBody *iBody);

#endif /* CATIPGMAdvancedBoundingBoxWireOper_h_ */
