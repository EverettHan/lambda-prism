#ifndef CATIPGMGlobalThicknessAnalyserOpe_h_
#define CATIPGMGlobalThicknessAnalyserOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : L. Marini 
//
// DESCRIPTION  : MAX THICKNESS
// ----------------------------
//                Evaluate a rough THICKNESS estimation value of a thin wall Body.
//
//                The algorithm is designed for simple thin wall Body WITHOUT Fillet and Chamfer.
//                The returned MAX THICKNESS value is only an estimate.
//                If you need an exact value, use CATIPGMTopWallThickness3D or CATIPGMTopWallThickness.
//
//                HOW TO CHECK THE ESTIMATION
//                ---------------------------
//                double maxThickness       = CATPGMGlobalThicknessAnalyse(..,MAX_THICKNESS_TYPE);
//                double signatureThickness = CATPGMGlobalThicknessAnalyse(..,SIGNATURE_THICKNESS_TYPE);
//                if (maxThickness > 2*signatureThickness)  you'b better use the CATIPGMTopWallThickness               
//
// DESCRIPTION  : SIGNATURE THICKNESS
// ----------------------------------
//                Compute the SIGNATURE THICKNESS value of a VOLUMIC body.
//                It's an average thickness value depending on volume and area of the body.
//
// DESCRIPTION  : MAX THICKNESS LIMIT
// ----------------------------------
//                Compute the limit of max thickness.
//                It's the upper bound of max Thickness for a thin wall body.
//                
//                HOW TO USE IT for regular cases (it is not suitable for all cases)
//                ------------------------------------------------------------------
//                double maxThickness      = CATPGMGlobalThicknessAnalyse(..,MAX_THICKNESS_TYPE);
//                double maxThicknessLimit = CATPGMGlobalThicknessAnalyse(..,MAX_THICKNESS_LIMIT_TYPE);
//                double rayMargin         = 1.1; or 1.5; or 2.0; 
//                double rayThreshold      = CATMin(maxThickness*rayMargin , maxThicknessLimit);
//
//=============================================================================
// Creation LAP February 2014
//
//=============================================================================

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMAdvancedOperator.h"

class CATGlobalThicknessAnalyserImpl;
class CATSoftwareConfiguration;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMGlobalThicknessAnalyserOpe;

class ExportedByCATGMOperatorsInterfaces CATIPGMGlobalThicknessAnalyserOpe: public CATIPGMAdvancedOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMGlobalThicknessAnalyserOpe();

  // Thickness type
  enum ThicknessType {
    MAX_THICKNESS_TYPE       = 0,
    SIGNATURE_THICKNESS_TYPE = 1,
    MAX_THICKNESS_LIMIT_TYPE = 2,
  };

  //==============================================================================
  // Set Methods
  //==============================================================================
  // The default mode is : max thickness
  virtual void SetThicknessType(
    CATIPGMGlobalThicknessAnalyserOpe ::ThicknessType iThicknessType) = 0;

  //==============================================================================
  // Get Methods
  //==============================================================================
  // Return the expected  thickness value.
  virtual double GetResultThicknessValue() const = 0;

  // Only for CATIPGMGlobalThicknessAnalyserOpe::MAX_THICKNESS_TYPE
  virtual double GetResultThicknessLimitValue() const = 0;

  // Return if the inputBody is a good candidate for the internal equation.
  // In practice there is a check if the part is a thin wall body.
  // For example, a sphere is not compliant.
  virtual CATBoolean IsACompliantBody() const = 0;

  // Return if the inputBody is a thin wall body.
  // In practice the width has to be at least twice bigger than the average thickness.
  virtual CATBoolean IsAThinWallBody() const = 0;

  // DO NOT USED : Deprecated since R418 : Use GetResultThicknessValue()
  virtual double GetMaxThicknessValue() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMGlobalThicknessAnalyserOpe(); // -> delete can't be called
};

//==============================================================================
// Data
//==============================================================================
//==============================================================================
// CATGlobalThicknessAnalyse : MAX THICKNESS or SIGNATURE THICKNESS or MAX THICKNESS LIMIT
//==============================================================================
/**
* static methode to get the directly the ResultFaceList<br>
* <b>Legal Values</b>:<br>
*  <ul>
*    <li> <tt>iBody</tt> : The body to analyse. It have to be a thin wall body.<br> 
*    <li> <tt>oResultThickness</tt> : This value depends on ThicknessType.<br>
*    <li> <tt>iThicknessType</tt> : The default value is MAX_THICKNESS_TYPE.<br>
*    <li> <tt>HRESULT<tt> : S_OK , S_FALSE means the body is not compliant but a value is returned, E_FAIL means there are an error during computation.<br>
*  </ul>
**/
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMGlobalThicknessAnalyse(
  CATBody *iBody,
  CATSoftwareConfiguration *iConfig,
  double &oResultThickness,
  CATIPGMGlobalThicknessAnalyserOpe ::ThicknessType iThicknessType = CATIPGMGlobalThicknessAnalyserOpe::MAX_THICKNESS_TYPE);

/**
* double call for perfo of MAX_THICKNESS_TYPE and MAX_THICKNESS_LIMIT_TYPE
*/
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMGlobalThicknessAnalyse(
  CATBody *iBody,
  CATSoftwareConfiguration *iConfig,
  double &oResultMaxThickness,
  double &oResultMaxThicknessLimit);

//==============================================================================
// CATGlobalThicknessAnalyse
//  Usage of oLateralFaceList
//   - Filter the pairing in AutoMidSurface
//   - Detection of PartEdge on SheetMetal Part for CloudDFM.
//==============================================================================
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMGlobalThicknessAnalyse(
  CATBody *iBody,
  CATSoftwareConfiguration *iConfig,
  double &oResultThickness,
  CATLISTP(CATFace) &oLateralFaceList,
  CATBoolean iComputePairingThickness = FALSE);

//==============================================================================
// CATPGMCreateGlobalThicknessAnalyserOpe
//==============================================================================
/**
* Create operator, it call the constructor.<br>
* <b>Legal Values</b>:<br>
*  <ul>
*    <li> <tt>iTopData</tt> : It represents the information about the configuration and
*                the journal. If iTopData is NULL , the operator create it.<br>
*    <li> <tt>iBody</tt> : The body to analyse. It have to be a thin wall body.<br>
*  </ul>
**/
ExportedByCATGMOperatorsInterfaces CATIPGMGlobalThicknessAnalyserOpe *CATPGMCreateGlobalThicknessAnalyserOpe(
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATIPGMGlobalThicknessAnalyserOpe_h_ */
