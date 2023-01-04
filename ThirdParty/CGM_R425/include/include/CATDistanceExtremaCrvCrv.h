//===================================================================
// COPYRIGHT Dassault Systemes 2015/03/11
//===================================================================
// CATDistanceExtremaCrvCrv.cpp
// Header definition of class CATDistanceExtremaCrvCrv
//===================================================================
//
// Usage notes: Header for the distance extrema crv crv operator.
//
//===================================================================
// Historic :
// 10-03-15 F1Z Creation.
// DD/MM/YY
//===================================================================

#ifndef CATDistanceExtremaCrvCrv_H
#define CATDistanceExtremaCrvCrv_H

//===================================================================
// GeometricOperator
#include "Y30C3XGG.h"
#include "CATGeoOperator.h"
#include "CATUtilDistanceCrv.h"

// Mathematics
#include "CATMathTransformation2D.h"

// GeometricObjects
class CATCrvParam;
//===================================================================
//-----------------------------------------------------------------------

class ExportedByY30C3XGG CATDistanceExtremaCrvCrv: public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATDistanceExtremaCrvCrv);

public:

   /**
   * @nodoc
   * Do not use this constructor. Use the creation method
   * <tt>CreateCATDistanceExtremaCrvCrv</tt>.
   */
   CATDistanceExtremaCrvCrv(CATGeoFactory *iFactory);

   /**
   * Destructor
   */
   virtual ~CATDistanceExtremaCrvCrv ();

   //-----------------------------------------------------------------------------
   // Options (Set)
   //-----------------------------------------------------------------------------
   /**
   * Set the maxmal distance variation error that could be done for an extremum.
   * @param iTol
   * The tolerance.
   */
   virtual void SetTolerance  (double iTol) = 0;

   /**
   * Set the maximal distance of the extrema computed.
   * @param iMaxDistance
   * The maximal distance
   * @param iStopComputation
   * Set at TRUE, the computation will stop if an extremum distance is above iMaxDistance.
   */
   virtual void SetMaxDistance(double     iMaxDistance,
                               CATBoolean iStopComputation=TRUE) = 0;

   /**
   * Set the curve limits where the computation will be performed.
   * @param iLim1
   * The limits on the first curve
   * @param iLim2
   * The limits on the second curve
   */
   virtual void SetLimits(CATCrvLimits & iLim1,
                          CATCrvLimits & iLim2) = 0;

   /**
   * The linear option force the computation to only catch 
   * the linear admissible extremum area.
   * Other extremum area type are not computed and only a point is returned at its location.
   * @param iLinear
   * if setted at TRUE, the linear option is activated.
   */
   virtual void SetLinear(CATBoolean iLinear = TRUE) = 0;

   /**
    * Force the computation to return the same result independently of the inputs order.
    * @param iSymmetrical
    * If setted at TRUE, the option is activated.
    */
   virtual void SetSymmetrical(CATBoolean iSymmetrical = TRUE) = 0;

   //-----------------------------------------------------------------------------
   // Interfaces (Get)
   //-----------------------------------------------------------------------------

   /**
   * @return TRUE if the max distance given was reached
   */
   virtual CATBoolean IsMaxDistanceReached() = 0;

   /**
   * @return TRUE if the computation has stopped because the
   * max distance given was reached by one of the extremum.
   */
   virtual CATBoolean ComputationStopedAboveMax() = 0;

   /**
   * Retrieve the information about the extremum which has the highest distance 
   * before the computation finish.
   * @param oParamCrv1
   * The parameter on the curve1
   * @param oParamCrv2
   * The parameter on the curve2
   * @param oDistance
   * The distance of this extremum.
   * @return 1 if there was an error, 0 otherwise.
   */
   virtual HRESULT    GetMaxDistanceInformation(CATCrvParam & oParamCrv1,
                                                CATCrvParam & oParamCrv2,
                                                double      & oDistance ) = 0;

   /**
   * Retrieve the number of extremum solution
   * @return The number of extremum solution
   */
   virtual CATLONG32 GetNumberOfExtremum() = 0;

   /**
   * Initializes the extremum result iterator.
   */
   virtual void BeginExtremum() = 0;

   /**
   * Increments the results iterator to the next extremum.
   * @return
   * TRUE if there is a next extremum, FALSE if the end of the result extremum is reached.
   */
   virtual CATBoolean NextExtremum() = 0;

   /**
   * Gets the next extremum result.
   * @param oCrvParam1
   * The parameter on the first curve.
   * @param oCrvParam2
   * The parameter on the second curve.
   * @param oDistance
   * The distance between the two points.
   * @param oMainProperties
   * The main properties of an extremum.
   * @param oSecondProperties
   * The second properties of an extremum
   */
   virtual CATBoolean GetExtremum(CATCrvParam  & oCrvParam1       ,
                                  CATCrvParam  & oCrvParam2       ,
                                  double       & oDistance        ,
                                  ExtremumType * oMainProperties  ,
                                  ExtremumType * oSecondProperties) const = 0;


   /**
   * Retrieve the number of extremum area solution
   * @return The number of extremum area solution
   */
   virtual CATLONG32 GetNumberOfExtremumArea() = 0;

   /**
   * Initializes the extremum area result iterator.
   */
   virtual void BeginExtremumArea() = 0;

   /**
   * Increments the results iterator to the next extremum area.
   * @return
   * TRUE if there is a next extremum area, FALSE if the end of the result extremum is reached.
   */
   virtual CATBoolean NextExtremumArea() = 0;

  /**
  * Gets the next extremum area result.
  * @param oCrvParamStart1
  * The start parameter of the area on the first curve.
  * @param oCrvParamStart2
  * The start parameter of the area on the second curve.
  * @param oCrvParamEnd1
  * The end parameter of the area on the first curve.
  * @param oCrvParamEnd2
  * The end parameter of the area on the second curve.
  * @param oDistance
  * The distance between the two points.
  */
  virtual CATBoolean GetExtremumArea(CATCrvParam &oCrvParamStart1,
                                     CATCrvParam &oCrvParamStart2,
                                     CATCrvParam &oCrvParamEnd1  ,
                                     CATCrvParam &oCrvParamEnd2  ,
                                     double      &oDistance      ) const = 0;

   /**
   * @nodoc
   * Create the geometric objects factory to represent the solution.
   **/
   virtual void VisualizeSolutions() = 0;
};

/**
* Create an operator which computes the distance extrema between two CATCurves in 3D.
* @param iFactory
* The pointer to the geometry factory
* @ param iCrv1
* The first curve used to compute the distance
* @param iCrv2
* The second curve used to compute the distance
*/
ExportedByY30C3XGG CATDistanceExtremaCrvCrv * CreateCATDistanceExtremaCrvCrv(CATGeoFactory            * iFactory,
                                                                             CATSoftwareConfiguration * iConfig ,
                                                                             CATCurve                 * iCrv1   ,
                                                                             CATCurve                 * iCrv2   );

/**
* Create an operator which computes the distance extrema between two CATPCurves in 2D.
* @param iFactory
* The pointer to the geometry factory
* @ param iPCrv1
* The first parametric curve used to compute the distance
* @param iPCrv2
* The second parametric curve used to compute the distance
* @param iTransfoUV
* The 2D transformation that transform the iPCrv2 surface support to the iPCrv1 surface support
* in case they are not the same. Not necessary otherwise.
* Set to NULL if identity
*/
ExportedByY30C3XGG CATDistanceExtremaCrvCrv * CreateCATDistanceExtremaPCrvPCrv(CATGeoFactory            * iFactory          ,
                                                                               CATSoftwareConfiguration * iConfig           ,
                                                                               CATPCurve                * iPCrv1            ,
                                                                               CATPCurve                * iPCrv2            ,
                                                                               CATMathTransformation2D  * iTransfoUV = NULL );
//-----------------------------------------------------------------------

#endif
