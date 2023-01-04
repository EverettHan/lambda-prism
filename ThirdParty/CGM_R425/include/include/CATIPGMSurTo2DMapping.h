#ifndef CATIPGMSurTo2DMapping_h_
#define CATIPGMSurTo2DMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATBoolean.h"
#include "CATMappingValidity.h"

class CATSurParam;
class CATSurface;
class CATSurLimits;
class CATMathInterval2D;
class CATMathVector2D;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurTo2DMapping;

//==========================================================================
//
// CATIPGMSurTo2DMapping:
// Virtual class of mapping between CATsurface and 2 coordinates
//
//==========================================================================
//
// Usage notes:
//      This virtual Object describes the mapping between one CATSurface and a
//       virtual  2 dimension space 
//       The derivation of this Object is generally created with derivation of 
//        CATIPGMSurTo2DGlobalMapping 
//        
//       
//	Methods :
//             - Eval     ( CATSurface to 2D space , first derivatives optionnal)
//             - InvEval  (   2D space to CATSurface, first derivatives optionnal)
//             - Get Reference    
//
//==========================================================================
//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMSurTo2DMapping: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSurTo2DMapping();

  //-------------
  // Evaluators
  //-------------
  //  Returned Boolean value is 0 if evalution (or inverse) is possible.
  //                            1 if not (outside bound evaluation for example).
  //  Direct evaluation 
  //   You can use either CATSurParam or GlobalParameter on CATSurface ( consistent with GetGlobalEquation )
  virtual CATBoolean Eval(const CATSurParam &iParam, double &oX, double &oY) const = 0;

  virtual CATBoolean Eval(
    const CATSurParam &iParam,
    double &oX,
    double &oY,
    double &oDXDU,
    double &oDXDV,
    double &oDYDU,
    double &oDYDV) const = 0;

  virtual CATBoolean Eval(
    const double iU,
    const double iV,
    double &oX,
    double &oY) const = 0;

  virtual CATBoolean Eval(
    const double iU,
    const double iV,
    double &oX,
    double &oY,
    double &oDXDU,
    double &oDXDV,
    double &oDYDU,
    double &oDYDV) const = 0;

  //  Inverse evaluation 
  //   You can use either CATSurParam or GlobalParameter on CATSurface ( consistent with GetGlobalEquation )  
  virtual CATBoolean InvEval(
    const double iX,
    const double iY,
    CATSurParam &oParam) const = 0;

  virtual CATBoolean InvEval(
    const double iX,
    const double iY,
    CATSurParam &oParam,
    CATMathVector2D &oDX,
    CATMathVector2D &oDY) const = 0;

  virtual CATBoolean InvEval(
    const double iX,
    const double iY,
    double &oU,
    double &oV) const = 0;

  virtual CATBoolean InvEval(
    const double iX,
    const double iY,
    double &oU,
    double &oV,
    double &oDUDX,
    double &oDUDY,
    double &oDVDX,
    double &oDVDY) const = 0;

  //----------------------
  // Validity of the mapping . Describe information regarding local validity of Mapping
  //---------------------- 
  //return TRUE if the image can be computed. 
  //Else the Interval doesn't necesarly contain the true image.
  virtual CATBoolean ComputeImage(CATMathInterval2D &oImage) = 0;

  //return TRUE if inverse functions are well defined on iImage.
  //(Only in DevDev case with radiantness).
  virtual CATBoolean CheckInvImage(CATMathInterval2D &iImage) = 0;

  //----------------------
  // Set and Get Methods 
  //---------------------- 
  virtual void GetReference(const CATSurface *&oReference) const = 0;

  virtual void GetReferenceLimits(CATSurLimits &oLimits) const = 0;

  virtual CATMappingValidity GetValidity() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurTo2DMapping(); // -> delete can't be called
};

#endif /* CATIPGMSurTo2DMapping_h_ */
