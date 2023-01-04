#ifndef CATIPGMTopPConicOperator_h_
#define CATIPGMTopPConicOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopCurveOperator.h"

class CATBody;
class CATMathVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopPConicOperator;

/**
 * Class defining a topological operator that builds a PConic on a plane.
 * This operator follows the general scheme of the topological operators:
 * <ul>
 *<li> Create the operator with the global function <tt>CATPGMCreateTopPConicOperator</tt>, which defines
 * the start and end vertices, as well as the supporting planar shell body.
 *<li> Set the parameters. As a conic has many ways to be defined, there is one <tt>Setxxx</tt>
 * method by method.
 * <dl>
 * <dt><tt>SetTgtTgtPt</tt></dt><dd>Start and end tangents, and a passing point.
 * <dt><tt>SetTgtTgtPrm</tt></dt><dd>Start and end tangents, and a parameter <tt>iParameter</tt>. 
 * Define the line passing thru
 * the intersection between the two tangents, and of origin the middle of the segment defined
 * by the start and end points. 
 * The conic passes thru the point of parameter <tt>iParameter</tt> on this line.
 * <dt><tt>SetPtPrm</tt></dt><dd>A point (intersection of the tangents at the limit points) 
 * <tt>iTgtInterVertexBody</tt> and a parameter <tt>iParameter</tt> (as upper). 
 * <dt><tt>SetPtPt</tt></dt><dd>A point (intersection of the tangents at the limit points)
 * <tt>iTgtInterVertexBody</tt> and  a passing point <tt>iPassingVertexBody</tt>.
 * <dt><tt>SetPtPtPt</tt></dt><dd>Three additional passing points.
 * <dt><tt>SetPtPtTgtInd</tt></dt><dd>Two additional passing points and a tangent defined on
 * one of the four passing points.
 * </dl>
 *<li> Run,
 *<li> Get the resulting body,
 *<li> Delete the operator.
 *</ul>
 * You can also directly call the global function
 * <tt>CATPGMCreateTopPConic</tt>, that directly returns the resulting body.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopPConicOperator: public CATIPGMTopCurveOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopPConicOperator();

  // ADVANCED mode settings
  //-----------------------
  //
  /**
* Defines the working tolerance used in PConic creation.
* @param iTolerance
* The tolerance value. 
* If not called, the default value is the factory resolution.
*/
  virtual CATLONG32 SetTolerance(double iTolerance) = 0;

  /**
* Defines the relimitation mode used in PConic creation.
* @param iRelimitation
* The relimitation indicator value. 
* iRelimitation = TRUE to create a PConic from Start to End Point.
* iRelimitation = FALSE to create a non-limited PConic, i.e. a complete closed ellipse,
*  an infinite hyperbola or parabola.
* By default, the PConic is limited from Start to End point. 
*/
  virtual CATLONG32 SetRelimitation(CATBoolean iRelimitation) = 0;

  // The following setting methods follow the creation of a CATIPGMTopPConicOperator,
  // (see CATPGMCreateTopPConicOperator global function)
  //
  //-----------------------------------------
  // settings : start and end tangents + a passing point
  virtual CATLONG32 SetTgtTgtPt(
    const CATMathVector &iStartTangent,
    const CATMathVector &iEndTangent,
    CATBody *iPassingVertexBody) = 0;

  //-----------------------------------------
  // settings : start and end tangents, parameter 
  virtual CATLONG32 SetTgtTgtPrm(
    const CATMathVector &iStartTangent,
    const CATMathVector &iEndTangent,
    double iParameter) = 0;

  //-----------------------------------------
  // settings : intersection point of start and end tangents + parameter
  virtual CATLONG32 SetPtPrm(CATBody *iTgtInterVertexBody, double iParameter) = 0;

  //-----------------------------------------
  // settings : intersection point of start and end tangent + a passing point
  virtual CATLONG32 SetPtPt(
    CATBody *iTgtInterVertexBody,
    CATBody *iPassingVertexBody) = 0;

  //-----------------------------------------
  // settings : 5 passing points
  virtual CATLONG32 SetPtPtPt(
    CATBody *iPassingVertexBody1,
    CATBody *iPassingVertexBody2,
    CATBody *iPassingVertexBody3) = 0;

  //-----------------------------------------
  // settings : 4 passing points + a tangent given at a passing point :
  // iIndexTgtVertexBody = 1 : tangent is defined at point iStartVertexBody 
  // iIndexTgtVertexBody = 2 : tangent is defined at point iPassingVertexBody1 
  // iIndexTgtVertexBody = 3 : tangent is defined at point iPassingVertexBody2
  // iIndexTgtVertexBody = 4 : tangent is defined at point iEndVertexBody 
  virtual CATLONG32 SetPtPtTgtInd(
    CATBody *iPassingVertexBody1,
    CATBody *iPassingVertexBody2,
    const CATMathVector &iTgt,
    CATLONG32 iIndexTgtVertexBody) = 0;

  /**
  * Service needed to retrieve V4 behavior ( do not try to generate parabola first )
  */
  virtual void SetParabolaFirst(CATBoolean iParabolaFirst = TRUE) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopPConicOperator(); // -> delete can't be called
};

//
// creation of operator (ADVANCED mode)
//-------------------------------------
/**
* Creates a topological PConic operator :
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iShellBody
* The plane which contains the start and end vertex bodies.
* @param iStartVertexBody
* The pointer to the vertex body, origin of the PConic.
* @param iEndVertexBody
* The pointer to the vertex body, end of the PConic.
* @return [out, IUnknown#Release]
* A pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopPConicOperator *CATPGMCreateTopPConicOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATBody *iStartVertexBody,
  CATBody *iEndVertexBody);

//
// Creation of a topological PConic
// --------------------------------
//--------------- 1/
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateTopPConic(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATBody *iStartVertexBody,
  CATBody *iEndVertexBody,
  const CATMathVector &iStartTangent,
  const CATMathVector &iEndTangent,
  CATBody *iPassingVertexBody);

//--------------- 2/
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateTopPConic(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATBody *iStartVertexBody,
  CATBody *iEndVertexBody,
  const CATMathVector &iStartTangent,
  const CATMathVector &iEndTangent,
  double iParameter);

//--------------- 3/
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateTopPConic(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATBody *iStartVertexBody,
  CATBody *iEndVertexBody,
  CATBody *iTgtInterVertexBody,
  double iParameter);


//--------------- 4/
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateTopPConic(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATBody *iStartVertexBody,
  CATBody *iEndVertexBody,
  CATBody *iTgtInterVertexBody,
  CATBody *iPassingVertexBody);

//--------------- 5/
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateTopPConic(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATBody *iStartVertexBody,
  CATBody *iEndVertexBody,
  CATBody *iPassingVertexBody1,
  CATBody *iPassingVertexBody2,
  CATBody *iPassingVertexBody3);

//--------------- 6/
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateTopPConic(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATBody *iStartVertexBody,
  CATBody *iEndVertexBody,
  CATBody *iPassingVertexBody1,
  CATBody *iPassingVertexBody2,
  const CATMathVector &iTgt,
  CATLONG32 iIndexTgtVertexBody);

#endif /* CATIPGMTopPConicOperator_h_ */
