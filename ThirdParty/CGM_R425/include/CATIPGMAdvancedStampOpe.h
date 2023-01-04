#ifndef CATIPGMAdvancedStampOpe_h_
#define CATIPGMAdvancedStampOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2019
//=============================================================================
//
// RESPONSIBLE  : VB7
//
// DESCRIPTION  : This operator creates a AdvancedStamp shape.
//                An AdvancedStamp is defined by its Shape, a fillet radius,
//                a draft angle and a Draft direction.
//                It provides a result body which contains the AdvancedStamp shape.
//                It can be volumic, surfacic or lineic.
//
// INPUT DATA   : 
//                - Input shape : must be monodomain and surfacic
//                - Top Bottom orientation
//                   ____________________________________________________________________________
//                   |           Bottom                                                         |
//                   |                 __________________ <----- Input Shape                    |
//                   |           Top           || <------------ Shell orientation (Matter Side) |
//                   |                         \/                                               |
//                   |                                                                          |
//                   |                                                     _____________________|
//                   |  if(Top)        __________________                  |           /\       |
//                   |                /                  \                 | Pull Dir  ||       |
//                   |               /                    \                | Draft angle > 0    |
//                   |                                                     |____________________|
//                   |                                                                          |
//                   |  if(Bottom)   \                    /                                     |
//                   |                \__________________/                                      |
//                   |                                                                          |
//                   |__________________________________________________________________________|
//
//                - Input Curve      optional
//                                   must be mono domain and lineic
//                                   provide open curve definition
//                - Right Left Orientation
//                   ____________________________________________________________________________
//                   |                                                                          |
//                   |                /    /               /         /                          |
//                   |               /    /               /<------------- Input Curve           |
//                   |              /    /_<-____________/         /                            |
//                   |             /       ^                      /<----- Input Shape           |
//                   |            /________|_____________________/                              |
//                   |                     |    || <----- Shell orientation (Matter Side) : M   |
//                   |                     |    \/                                              |
//                   |                     |                                                    |
//                   |                     Wire Orientation : W                                 |
//                   |                                                                          |
//                   |    M ^ W give the Right Side - The Opposite side is the Left Side        |
//                   |                                                                          |
//                   |                /    /               /         /                          |
//                   |               /    /   Right       /<------------- Input Curve           |
//                   |              /    /_______________/         /                            |
//                   |             /         Left                 /<----- Input Shape           |
//                   |            /______________________________/                              |
//                   |__________________________________________________________________________|
//
//                - iFilletRadius : radius of the fillet to create between input shape
//                                  and drafted faces
//                                  >= 0
//                - iPullDir : draft direction
//                - iDraftAngle : draft angle
//                                > 0, < 0 or == 0
//                - iAdvancedStampHeight : minimum height of result shape through the iPullDir direction
//                                   > iFilletRadius so > 0                     
//
// OPTIONS      : 
//                - Output dimension : Lineic, Surfacic or Volumic : By default : Surfacic
//                - TrimSupport                                    : By default : TRUE
//                - Fillet Representation                          : By default : TRUE
//                - Smmoth Internal Curve : smooth the reflectLine : By default : FALSE
//                - Smooth Input Curve                             : By default : FALSE
//                - Up to Option                                   : By default : FALSE
//
//=============================================================================

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPersistentOperator.h"
#include "ListPOfCATEdge.h"

class CATGMAdvancedStampImpl;
class CATGeoFactory;
class CATTopData;
class CATlsoAdvancedStampInputSpecificData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMAdvancedStampOpe;

class ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedStampOpe: public CATIPGMPersistentOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMAdvancedStampOpe();

  //------------------
  // Set methods
  //------------------
  //Output dimension
  virtual void SetVolumicMode() = 0;

  virtual void SetSurfacicMode() = 0;

  virtual void SetLineicMode() = 0;

  //Trim support or not
  virtual void SetTrimSupportMode(CATBoolean iTrimSupportMode) = 0;

  //Fillet representation in the output or not
  virtual void SetFilletRepresentationMode(CATBoolean iFilletRepresentationMode) = 0;

  //For Surfacic/NoTrim/NoFillet Rep only
  virtual void SetAdvancedStampL2Value(double iL2Value) = 0;

  //Input Curve representation in the output or not
  virtual void SetCurveRepresentationMode(CATBoolean iCurveRepresentationMode) = 0;

  //Smooth Internal Curve
  virtual void SetSmoothInternalCurve(
    CATBoolean iSmoothInternalCurve = TRUE,
    double iTangencyThreshold = 0.5,      // @NumValidated (VB7 - W10 2019)
    double iMaximumDeviation = 0.001) = 0;// @NumValidated (VB7 - W10 2019)

  //Smooth Input Curve
  virtual void SetSmoothInputCurve(
    CATBoolean iSmoothInputCurve = TRUE,
    double iTangencyThreshold = 0.5,      // @NumValidated (VB7 - W10 2019)
    double iMaximumDeviation = 0.001) = 0;// @NumValidated (VB7 - W10 2019)

  //Up To
  virtual void SetUpToBody(CATBody *iUpToBody) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMAdvancedStampOpe(); // -> delete can't be called
};

// ----------------------
// CATPGMCreateGMAdvancedStampOpe
// ----------------------
// Deprecated W42 2018
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  double iFilletRadius,
  CATMathDirection &iPullDir,
  CATAngle &iDraftAngle,
  double iAdvancedStampHeight);

//For open curve
// Deprecated W42 2018
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  CATLISTP(CATEdge) &iInputEdgeList,
  double iFilletRadius,
  CATMathDirection &iPullDir,
  CATAngle &iDraftAngle,
  double iAdvancedStampHeight);

// Deprecated W42 2018
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  CATBody &iOpenCurveBody,
  double iFilletRadius,
  CATMathDirection &iPullDir,
  CATAngle &iDraftAngle,
  double iAdvancedStampHeight);

//New constructor - W42 2018
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  CATOrientation iKeepTopOrBottom,
  double iFilletRadius,
  CATMathDirection &iPullDir,
  CATAngle &iDraftAngle,
  double iAdvancedStampHeight);

//New constructor - W42 2018
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  CATOrientation iKeepTopOrBottom,
  CATBody &iOpenCurveBody,
  CATOrientation iKeepRightOrLeft,
  double iFilletRadius,
  CATMathDirection &iPullDir,
  CATAngle &iDraftAngle,
  double iAdvancedStampHeight);

#endif /* CATIPGMAdvancedStampOpe_h_ */
