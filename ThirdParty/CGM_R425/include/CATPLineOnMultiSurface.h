#ifndef CATPLineOnMultiSurface_H
#define CATPLineOnMultiSurface_H
// COPYRIGHT DASSAULT SYSTEMES 2013

/**
* @nodoc
*
* Create a "Pline" on a MultiSurface
* it fills an ordered list of CATPline 
* corresponding to the parametric LINE between
* iStart and iEnd in UV space of MultiSurface
* 
* options :
* =========
*  if ForceBorder option is set and if iStart and iEnd are defining an isparametric Line 
*  we create the isoparametric line that is nearest to iStart and iEnd in UV space
*  if iStart3D and iEnd3D are provided through Set3DBoundaries they will be used to relimit the Line 
*  (only if ForceBorder Option is Set) 
* 
*/

#include "Y30UIUTI.h"
#include "CATGeoOperator.h"
#include "CATListOfCATPCurves.h"

class CATMultiSurface;

class ExportedByY30UIUTI CATPLineOnMultiSurface : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATPLineOnMultiSurface);
public:

  CATPLineOnMultiSurface(CATGeoFactory * iFactory);

  virtual ~CATPLineOnMultiSurface();

  /**
  * @nodoc
  * Creates the  solution curve of <tt>this</tt> CATPLineOnMultiSurface operator.
  */
  virtual void GetResults(CATLISTP(CATPCurve)* ioListOfPlines)=0;

  /**
  * @nodoc
  * Force Border Options
  * By default it is not set 
  */
  virtual void SetForceBorderOption(CATBoolean iOption)=0; 

   /**
  * @nodoc
  * 3D Boudaries Options
  */
  virtual void Set3DBoundaries(CATMathPoint & iStart3D, CATMathPoint & iEnd3D)=0;

};

/**
 * @nodoc
 * Create CATPLineOnMultiSurface Operator
 */
ExportedByY30UIUTI
CATPLineOnMultiSurface * CATCreatePLineOnMultiSurface(CATGeoFactory *iWhere,
                                                      CATSoftwareConfiguration *iConfig,
                                                      CATMultiSurface *iSurface,
                                                      CATMathPoint2D & iStart, 
                                                      CATMathPoint2D & iEnd);


#endif

