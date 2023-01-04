#ifndef CATPGMCreateFrFMovingFrame_h_
#define CATPGMCreateFrFMovingFrame_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATBoolean.h"

class CATCurve;
class CATFrFCompositeCurve;
class CATFrFCoupling;
class CATIPGMFrFMovingFrame;
class CATMathDirection;
class CATMovingFrameStruct;
class CATIPGMFrFObject;
class CATIPGMFrFCoupling;

//#ifdef KeepDeprecatedCreateMovingFrame
// deprecated
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreateMovingFrame(
  CATIPGMFrFMovingFrame *iToCopy,
  CATBoolean iCopyMapping = TRUE);

//#endif
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreateParallelToPlaneMovingFrame(
  CATIPGMFrFObject &iFrFObject,
  const CATFrFCompositeCurve *iSpine,
  const CATMathDirection *iPlaneNormal,
  CATBoolean iComputeMapping = TRUE);

//
/**
 * @return [out, IUnknown#Release]
 */

ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreateOrthoMovingFrame(
  CATIPGMFrFObject &iFrFObject,
  const CATFrFCompositeCurve *iSpine,
  CATBoolean iComputeMapping = TRUE);

//
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreatePseudoOrthoMovingFrame(
  CATIPGMFrFObject &iFrFObject,
  const CATFrFCompositeCurve *iSpine,
  CATBoolean iComputeMapping = TRUE);

//
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreateOrthoCrvCrvMovingFrame(
  CATIPGMFrFObject &iFrFObject,
  const CATFrFCompositeCurve *iSpine,
  const CATIPGMFrFCoupling *iCoupling,
  CATBoolean iComputeMapping = TRUE);

//
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreatePseudoOrthoCrvCrvMovingFrame(
  CATIPGMFrFObject &iFrFObject,
  const CATFrFCompositeCurve *iSpine,
  const CATIPGMFrFCoupling *iCoupling,
  CATBoolean iComputeMapping = TRUE);

//
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreateMeanTangMovingFrame(
  CATIPGMFrFObject &iFrFObject,
  CATIPGMFrFCoupling *iCoupling);

// Method to construct Ortho or PseudoOrtho MF
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreateMovingFrame(
  CATIPGMFrFObject &iFrFObject,
  const CATFrFCompositeCurve *iSpine,
  const CATMovingFrameStruct &iMFDef);

// restricted use
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame *CATPGMCreateExtrapolShapeMovingFrame(
  CATIPGMFrFObject &iFrFObject,
  const CATFrFCompositeCurve *iSpine);

#endif /* CATPGMCreateFrFMovingFrame_h_ */
