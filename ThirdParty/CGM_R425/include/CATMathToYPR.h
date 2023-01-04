#include "CATMathTransformation.h"
#include "CATMathematics.h"

//=============================================================================
// COPYRIGHT Dassault Systemes 2006 
//=============================================================================
//
// xx/10/06 OBH Creation
//=============================================================================

//it computes Yaw pitch roll angles from a CATMathTransofrmation 
//@oXX , @oYY and @oZZ are corrdinates of translation vector. 
//@oRoll, @oPitch, @oYaw are values of yaw pitch and roll.
//iEpsAngle is an angular tolerance.
//@pitch is included in]-0.5*CATPi,+0.5*CATPi[
//@roll is included in ]-CATPi    ,    +CATPi[
//@yaw is included in  ]-CATPi    ,    +CATPi[
int ExportedByCATMathematics 
  FromCATMathToYPR(const CATMathTransformation & iTransfo, 
                         double                * oXX, 
                         double                * oYY, 
                         double                * oZZ, 
                         double                * oRoll, 
                         double                * oPitch,
                         double                * oYaw, 
                         double                  iEpsAngle=CATGetDefaultTolerance().EpsgForRelativeTest());

//it computes a CATMathTransofrmation given Yaw pitch roll angles 
//@xx , @yy and @zz are corrdinates of translation vector. 
//@roll, @pitch, @yaw are values of yaw pitch and roll.
////// |c_phi * c_teta  ,      (c_phi * s_teta * s_psi) - (s_phi * c_psi),    (c_phi * s_teta * c_psi) + (s_phi * s_psi)|////// 
////// |s_phi * c_teta  ,      (s_phi * s_teta * s_psi) + (c_phi * c_psi),    (s_phi * s_teta * c_psi) - (c_phi * s_psi)|////// 
////// |- s_teta        ,                                  c_teta * s_psi,                                c_teta * c_psi|////// 
int ExportedByCATMathematics 
  FromYPRToCATMath(CATMathTransformation * oTransfo, 
                   double                & iXX, 
                   double                & iYY, 
                   double                & iZZ, 
                   double                & iRoll, 
                   double                & iPitch, 
                   double                & iYaw);
