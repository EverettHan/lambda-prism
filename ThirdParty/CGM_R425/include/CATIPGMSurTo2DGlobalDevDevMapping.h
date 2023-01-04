#ifndef CATIPGMSurTo2DGlobalDevDevMapping_h_
#define CATIPGMSurTo2DGlobalDevDevMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMSurTo2DGlobalMapping.h"
#include "CATDataType.h"
#include "CATBoolean.h"

class CATFrFCompositeCurve;
class CATFrFCompositeCurveMapping;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSurTo2DGlobalDevDevMapping;

//----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMSurTo2DGlobalDevDevMapping: public CATIPGMSurTo2DGlobalMapping
{
public:
  /**
   * Constructor
   */
  CATIPGMSurTo2DGlobalDevDevMapping();

  //-------------
  //-------------
  // Methods
  //-------------
  //  Create LocalMapping 
  /**
   * @return [out, IUnknown#Release]
   */
  virtual CATIPGMSurTo2DMapping *CreateLocalMapping(
    CATSurface *iLocalReference,
    const double &iRefOrientation,
    const CATSurLimits &iRefLimits) const = 0;

  //----------------------
  // Set and Get Methods 
  //----------------------   
  //  Set Radiantness ( this is a neologism : tentative translation from french rayonnance which is itself a nelologism)
  //  Transformation of output X and Y as follows :
  //  X'= X    and Y' = (R+Y*Radiantness)*X / (R + Y)  ;R being the Radius at Invariant point .
  virtual void SetRadiantness(double iRadiantness) = 0;

  //  Set Inclination ( Radian)
  //  Transformation of output X and Y as follows :
  //  X'= X    and Y' = Y + X*tan(Inclination)
  //  Rq : Inclinaison is applied first then Radiantness.
  virtual void SetInclination(double iInclination) = 0;

  //  Set Inversion
  //  Inversion of the X according to the standard axis on support 
  //  standard axis on Support depends itself on mapping mode in Create  ( implicit (outside) or 
  //   Explicte according to Shell normal.
  virtual void SetInversion(double iInversion) = 0;

  //  Get Inversion
  //  Inversion of the X according to the standard axis on support 
  //  standard axis on Support depends itself on mapping mode in Create  ( implicit (outside) or 
  //   Explicte according to Shell normal.
  virtual double GetInversion() = 0;

  //  Able or disable fast run operator.
  //  To enhance performance, for preview mode for example
  //  Default is accuracy run mode (with worse accuracy, iAccuracy=0).
  virtual void SetPerformanceMode(CATLONG32 iAccuracy = 0) = 0;

  //  Able or disable InvertMode.
  //  This option allow you to invert the way operations are done.
  //  First develop will be done along axis direction, and then along
  //  circle direction.
  //  Default is FALSE.
  virtual void SetInvertDevDevOption(CATBoolean iSet = TRUE) = 0;

  virtual CATBoolean GetInvertDevDevOption() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurTo2DGlobalDevDevMapping(); // -> delete can't be called
};

#endif /* CATIPGMSurTo2DGlobalDevDevMapping_h_ */
