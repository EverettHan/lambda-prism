//===================================================================================
// COPYRIGHT Dassault Systemes 2020
//===================================================================================
// CATProfileRecognizer.h
// Header definition of class CATProfileRecognizer
//===================================================================================
//
// Usage notes: Detect the connexe profile from a list of ordered points 
// option: curve can be identified from a given list of curves and limits within 
// a user tolerance - if no curve identified fill with line.
// The operator returns a list of curves with their limits and orientation
//===================================================================================
// Historic:
// 07/07/20 : AOV Creation
// DD/MM/YY
//===================================================================================
#ifndef CATProfileRecognizer_H
#define CATProfileRecognizer_H

// ExportedBy
#include "GeoRecognition.h"

// Base class
#include "CATGeoOperator.h"

#include "CATListOfCATPCurves.h"
#include "CATListOfCATCrvParams.h"


// ============================================================================================================================= //
//                                                           OPERATOR                                                            //
// ============================================================================================================================= //
class ExportedByGeoRecognition CATProfileRecognizer : public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATProfileRecognizer);
public:
   //-----------------------------------------------------------------------------
   // Object Management
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Do not use this constructor. Use the creation method
   * <tt>CATCreateProfileRecognizer</tt>.
   */
  CATProfileRecognizer(CATGeoFactory * iFactory);

   /**
   * Destructor
   */
   virtual ~CATProfileRecognizer();


  /**
  * tolerance used to associate points with input curve
  */
  virtual void SetUserTolerance(double iTol)=0;

  /**
  * set the curves set to be identified within the user tolerance among the list of points
  * curves informations are the curve and thier limits
  */
  virtual void SetInputCurvesData(const CATLISTP(CATCurve) & iListOfCurves, const CATLISTP(CATCrvLimits) & iListCrvLimits)=0;


  /**
  *Get result: the set of curves dientified, their limits and orientation regarding the set of point order
  */
  virtual void GetCurveResults(CATLISTP(CATCurve) & ioListOfCurves, CATLISTP(CATCrvLimits) & ioCrvLimits, CATListOfInt & ioOrientations)=0;

  /**
  * Get results: returns the list of input curves index associated to a point
  */
  virtual void GetCurvesFromPoint(int idPoint, CATListOfInt & oListOfIdCurves)=0;

};

// ============================================================================================================================= //
//                                                        CREATE OPERATOR                                                        //
// ============================================================================================================================= //
/**
* Create an operator which identifies the set of curves from a set of points 3D. 
*/
ExportedByGeoRecognition CATProfileRecognizer * CreateProfileRecognizer(CATGeoFactory                       * iFactory,
                                                                           CATSoftwareConfiguration            * iConfig,
                                                                           const CATMathSetOfPointsND          * iPoints);

/**
* @nodoc
* @nocgmitf
*/
ExportedByGeoRecognition void Remove (CATProfileRecognizer * & ioProfileRecognizer);

#endif

