//===================================================================
// COPYRIGHT Dassault Systemes 2017/02/21
//===================================================================
// CATApproxCivilCurve.h
// Header definition of class CATApproxCivilCurve
//===================================================================
//
// Usage notes: Approximation of a civil curve from its evaluator.
//
//===================================================================
// Historic:
// 21/02/17 F1Z : Creation
// 14/03/17 F1Z : Add extract methods.
// 13/04/17 F1Z : Add evaluator creation for parabola_2 and correct
// 28/11/17 F1Z : Add create evaluator from end information
// 30/07/18 KJD : Add create evaluator for catenary
// 17/01/20 F4E : Add catenary properties extraction method
// 21/02/20 F4E : add of catenary coef as output of CATExtractCivilCatenaryProperties for CGMReplay and Debug
// 13/03/20 F4E : Move all CATCreate for Evaluators to dedicated file to gather all occurencies
// 17/04/20 F4E : Migration CAT2DCurveEvaluator -> CATCivilCurveEvaluator
// DD/MM/YY
//===================================================================

#ifndef CATApproxCivilCurve_H
#define CATApproxCivilCurve_H

//===================================================================

// System
#include "CATBoolean.h"

// Mathematics
#include "CATCGMVirtualMacros.h"

// GMModelInterfaces
#include "CATCivilCurveDef.h"

// Geometric Operators
#include "GeoAdvCurves.h"
#include "CATGeoOperator.h"

class CATSoftwareConfiguration;
class CATMathPoint2D;
class CATMathVector2D;
class CATTolerance;
class CATGeoFactory;
class CATSurface;
class CATCurve;
class CATCivilCurveEvaluator;
class CATCivilCurveEvaluatorImp;
class CAT2DCurveEvaluator;
class CATBasis2DCurveEvaluator;

// ============================================================================================================================= //
//                                                           OPERATOR                                                            //
// ============================================================================================================================= //
class ExportedByGeoAdvCurves CATApproxCivilCurve: public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATApproxCivilCurve);
public:
   //-----------------------------------------------------------------------------
   // Object Management
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Do not use this constructor. Use the creation method
   * <tt>CATCreateApproxCivilCurve</tt>.
   */
   CATApproxCivilCurve(CATGeoFactory * iFactory);

   /**
   * Destructor
   */
   virtual ~CATApproxCivilCurve ();

   //-----------------------------------------------------------------------------
   // Output Interface (Get)
   //-----------------------------------------------------------------------------
   /**
   * @return
   * <br>E_FAIL  If there was an operator issue during the computation.
   * <br>S_FALSE If the operator did not succeed because of the inputs & option given
   *             are not consistent (ex: the evaluator is not a civil curve).
   * <br>S_OK    If the operator has not encountered any issue.
   */
   virtual HRESULT GetRunStatus()                                           = 0;

   /**
    * @return
    * TRUE If the solution is a point, FALSE if it is a curve.
    */
   virtual HRESULT IsAPoint              (CATBoolean       & iIsAPoint) const = 0;

   /**
   *  Retrieve the point in UV space where the civil curve start.
   */
   virtual HRESULT GetPoint              (CATMathPoint2D   & oPoint   ) const = 0;

   /**
   * @param oCurve
   * The curve representing (can be exact or an approximation) of the civil curve.
   * <br>The object life of the object retrieved has to be handle by the caller.
   */
   virtual HRESULT GetCurve              (CATCurve       * & oCurve   ) const = 0;
};

// ============================================================================================================================= //
//                                                        CREATE OPERATOR                                                        //
// ============================================================================================================================= //
/**
* Create an operator which computes approximation of a civil curve defined by a 2D curve evaluator inside its current limits.
* @param iCivilCurveEvalutor
* The civil curve evaluator. A civil curve evaluator can be created from CATCreateCivilCurveEvaluator.h
* @param iSurface
* The surface support of the civil curve.
*/
ExportedByGeoAdvCurves CATApproxCivilCurve * CATCreateApproxCivilCurve(      CATGeoFactory            * iFactory             ,
                                                                             CATSoftwareConfiguration * iConfig              ,
                                                                       const CATCivilCurveEvaluator   * iCivilCurveEvaluator ,
                                                                             CATSurface               * iSurface             );

// @nodoc @nocgmitf
//  Internal method (called by the public one)
CATApproxCivilCurve * CreateApproxCivilCurve(      CATGeoFactory             * iFactory             ,
                                                   CATSoftwareConfiguration  * iConfig              ,
                                             const CATCivilCurveEvaluatorImp * iCivilCurveEvaluator ,
                                                   CATSurface                * iSurface             );

/** deprecated : only for catenary
* Create an operator which computes approximation of a civil curve defined by a 2D curve evaluator inside its current limits.
* @param iCivilCurveEvalutor
* The civil curve evaluator. A civil curve evaluator can be created from CATCreateCivilCurveEvaluator.h
* @param iSurface
* The surface support of the civil curve.
*/
ExportedByGeoAdvCurves CATApproxCivilCurve * CATCreateApproxCivilCurve(      CATGeoFactory            * iFactory            ,
                                                                             CATSoftwareConfiguration * iConfig             ,
                                                                       const CATBasis2DCurveEvaluator * iCivilCurveEvaluator,
                                                                             CATSurface               * iSurface            );

// ============================================================================================================================= //
//                                                       CREATE CIVIL CURVE                                                      //
// ============================================================================================================================= //

// Use CATCreateCivilCurveEvaluator.h




/**
* @nodoc
* @nocgmitf
*/
ExportedByGeoAdvCurves void Remove (CATApproxCivilCurve * & ioApproxCivilCurve);

#endif

