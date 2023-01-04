#ifndef CATIPGMFrFConversionServicesToSplines_h_
#define CATIPGMFrFConversionServicesToSplines_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

#include "CATFreeFormDef.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATFrFNurbsMultiForm.h"
#include "CATEdge.h"
#include "CATBody.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFrFConversionServicesToSplines;

class ExportedByCATGMOperatorsInterfaces CATIPGMFrFConversionServicesToSplines: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFConversionServicesToSplines();

  // comment to do ...
  virtual void SetConversioParams(
    double ideviation,
    int iNbMaxArcs,
    int iMaxDegree) = 0;

  virtual void ConstraintsExtremities(
    CATFrFContinuity iSideContinuity = CATFrFPointCont) = 0;

  // comment to do ... //sharpness_tolerance = 60 ?
  virtual void SetSharpnessAngle(double isharpness_angle) = 0;

  // comment to do
  virtual void SetDistributionOfPoints(double imin_dist) = 0;

  virtual int RunOperator() = 0;

  virtual CATBody *GetBody() = 0;

  virtual void GetResult(CATEdge *&oEdge) = 0;

  virtual void GetResult(CATFrFNurbsMultiForm *&ioNurbsMultiForm) = 0;

  virtual void GetResult(CATLISTV(CATMathPoint) &oListOfPtsFoSpline) = 0;
   
protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFConversionServicesToSplines(); // -> delete can't be called
};

//
ExportedByCATGMOperatorsInterfaces CATIPGMFrFConversionServicesToSplines *CATPGMCreateConversionServicesToSplines(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATEdge *iEdge);

//
ExportedByCATGMOperatorsInterfaces CATIPGMFrFConversionServicesToSplines *CATPGMCreateConversionServicesToSplines(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATIPGMFrFConversionServicesToSplines_h_ */
