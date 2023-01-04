#ifndef CATIPGMThicknessExtraction_h_
#define CATIPGMThicknessExtraction_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATTopDefine.h"
#include "CATLISTP_CATMathPoint.h"
#include "CATLISTP_CATMathVector.h"
#include "CATListOfInt.h"

class CATBody;
class CATGeoFactory;
class CATString;
class CATTopData;
class CATWallAnalyzer;
class CATIPGMPositionPtVolOperator;
class CATIPGMDistancePointBody;
class CATMathTransformation;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMThicknessExtraction;


/*Class defining the operator for extracting the Thickness of a volumic body given a set of points
* To use the operator:
*<ul>
* <li>Create it with the <code>CATPGMCreateThicknessExtraction< / code> global function
* <li>Run the operator,
* <li>Retrieve the results with the GetResult... methods
* < / ul>
*/
//-----------------------------------------------------------------------------
// CATIPGMThicknessExtraction
//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMThicknessExtraction: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   * Do no use
   * Create the operator with the CATCreate method
   */
  CATIPGMThicknessExtraction();

  //---------------------------------------------------------
  // SetListOfPoints
  //---------------------------------------------------------
  virtual void SetListOfPoints(CATLISTP(CATMathPoint) &iListOfPoints) = 0;

  //---------------------------------------------------------
  // SetListOfNormals
  //---------------------------------------------------------
  virtual void SetListOfNormals(CATLISTP(CATMathVector) &iListOfNormals) = 0;

  //---------------------------------------------------------
  // SetIndexesToIgnore
  //---------------------------------------------------------
  virtual void SetIndexesToIgnore(CATListOfInt& iListOfIndexesToIgnore) = 0;

  //---------------------------------------------------------
  // SetMaxThickness
  //---------------------------------------------------------
  virtual void SetMaxThickness(double iMaxThickness) = 0;

  //---------------------------------------------------------
  // SetMidSurfaceBody
  //---------------------------------------------------------
  virtual void SetMidSurfaceBody(CATBody *iBody) = 0;

  //---------------------------------------------------------
  // GetResult
  //---------------------------------------------------------
  virtual int GetResult(
    double *&ioThicknesses,
    double *&ioOffsets,
    CATListOfInt &ioListOfKOIndexes) = 0;

  //---------------------------------------------------------
  // GetResult
  //---------------------------------------------------------
  virtual int GetResult(
    CATListOfDouble oThicknesses,
    CATListOfDouble oOffsets,
    CATListOfInt oListOfKOIndexes) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMThicknessExtraction(); // -> delete can't be called 
};

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMThicknessExtraction *CATPGMCreateThicknessExtraction(CATGeoFactory* iFactory,
                                                                                           CATTopData* iData,
                                                                                           CATBody* iVolumicBody,
                                                                                           CATLISTP(CATMathPoint) iPoints,
                                                                                           CATLISTP(CATMathVector)iNormals,
                                                                                           double                 iMaxThickness,
                                                                                           CATMathTransformation  iTransfo,
                                                                                           CATListOfInt iListOfIndexesToIgnore);

#endif /* CATIPGMThicknessExtraction_h_ */
