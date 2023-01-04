//===================================================================
// COPYRIGHT Dassault Systemes 2017/02/22
//===================================================================
// CATCivilCurveRecognizer.h
// Header definition of class CATCivilCurveRecognizer
//===================================================================
//
// Usage notes: Determine, from a PCurve, the civil curve type if 
// possible.
//
// /!\ : The PCurve should have been created by CATApproxCivilCurve or
//       CATApproxClothoide because assumption are made to increase
//       the operator robustness and efficiency.
// Note: The code can be openned from PCurve created by unknown source though.
//
//===================================================================
// Historic:
// 22/02/17 F1Z : Creation
//===================================================================

#ifndef CATCivilCurveRecognizer_H
#define CATCivilCurveRecognizer_H

//===================================================================


// Mathematics
#include "CATCGMVirtualMacros.h"

// GMModelInterfaces
#include "CATCivilCurveDef.h"

// Geometric Operators
#include "GeoAdvCurves.h"
#include "CATGeoOperator.h"

class CATSoftwareConfiguration;

class CATGeoFactory;
class CATPCurve;

class CAT2DCurveEvaluator;

// ============================================================================================================================= //
//                                                           OPERATOR                                                            //
// ============================================================================================================================= //
class ExportedByGeoAdvCurves CATCivilCurveRecognizer: public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATCivilCurveRecognizer);
public:
   //-----------------------------------------------------------------------------
   // Object Management
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Do not use this constructor. Use the creation method
   * <tt>CATCreateCivilCurveRecognizer</tt>.
   */
   CATCivilCurveRecognizer(CATGeoFactory * iFactory);

   /**
   * Destructor
   */
   virtual ~CATCivilCurveRecognizer ();

   //-----------------------------------------------------------------------------
   // Output Interface (Get)
   //-----------------------------------------------------------------------------
   /**
   * @return
   * <br>E_FAIL  If there was an operator issue during the computation.
   * <br>S_FALSE If the operator did not succeed because of the inputs & option given
   *             are not consistent.
   * <br>S_OK    If the operator has not encountered any issue.
   */
   virtual HRESULT GetRunStatus ()                                        const = 0;

   /**
   * @param oType
   * The civil curve type recognized.
   * @return
   * <br> S_OK if the oType retrieved is valid, E_FAIL otherwise.
   */
   virtual HRESULT GetCurveType (CATCivilCurveType     & oType          ) const = 0;

   /**
   * @param oCurveEvaluator
   * The 2D curve evaluator of the civil curve detected.
   * <br> Contains the civil curve properties. Use the CATExtractCivilCurve*** methods to extract the information.
   * <br> The object life of the object retrieved has to be handle by the caller.
   */
   virtual HRESULT GetEvaluator (CAT2DCurveEvaluator * & oCurveEvaluator) const = 0;

   /**
   * @nodoc
   * @nocgmitf
   * Create the geometric objects factory to represent the solution.
   **/
   virtual void VisualizeSolution() = 0;
};

// ============================================================================================================================= //
//                                                        CREATE OPERATOR                                                        //
// ============================================================================================================================= //
/**
* Create an operator which determines the civil curve type from a PCurve.
* <br> The PCurve is supposed to be created from CATApproxCivilCurve or CATApproxClothoide
* @param iPCurve
* The PCurve to determine the civil curve type.
*/
ExportedByGeoAdvCurves CATCivilCurveRecognizer * CATCreateCivilCurveRecognizer(CATGeoFactory            * iFactory,
                                                                           CATSoftwareConfiguration * iConfig ,
                                                                           CATPCurve                * iPCurve );

/**
* @nodoc
* @nocgmitf
*/
ExportedByGeoAdvCurves void Remove (CATCivilCurveRecognizer * & ioCivilCurveRecognizer);

#endif

