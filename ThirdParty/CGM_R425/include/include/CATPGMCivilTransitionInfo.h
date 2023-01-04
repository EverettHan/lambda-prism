#ifndef CATPGMCivilTransitionInfo_h_
#define CATPGMCivilTransitionInfo_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"
#include "CATCivilCurveDef.h"
#include "CATCGMVirtual.h"
#include "CATErrorDef.h"

// ============================================================================================================================= //
//                                                    CATPGMCivilTransitionInfo                                                     //
// ============================================================================================================================= //
class ExportedByCATGMModelInterfaces CATPGMCivilTransitionInfo: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMCivilTransitionInfo();

  /**
   * Destructor
   */
  virtual ~CATPGMCivilTransitionInfo();

  //-----------------------------------------------------------------------------
  // Get
  //-----------------------------------------------------------------------------
  virtual CATCivilTransitionType GetTransitionType() const = 0;

  // in case of CATCivilTransition_LineCircleLine,
  // input is iTransitionTypeInfo (CATCivilTransitionInfo_R / _L1 / _L2)
  // output is the associated value
  virtual HRESULT GetLineCircleLineInfo(
    const CATCivilTransitionInfoType iTransitionTypeInfo,
    double &oVal) const = 0;

  // in case of CATCivilTransition_LineLine
  // output are oTransitionTypeInfo (CATCivilTransitionInfo_L / _VerticalL / _K) and the associated value
  virtual HRESULT GetLineLineInfo(
    CATCivilTransitionInfoType &oTransitionTypeInfo,
    double &oVal) const = 0;

};

// ============================================================================================================================= //
/**
* Create 
*/
ExportedByCATGMModelInterfaces CATPGMCivilTransitionInfo *CATPGMCreateCATCivilTransitionInfo(
  const CATCivilTransitionType iTransitionType,
  const double iL1,
  const double iL2,
  const double iR);

ExportedByCATGMModelInterfaces CATPGMCivilTransitionInfo *CATPGMCreateCATCivilTransitionInfo(
  const CATCivilTransitionType iTransitionType,
  const CATCivilTransitionInfoType iTransitionTypeInfo,
  const double iVal);

#endif /* CATPGMCivilTransitionInfo_h_ */
