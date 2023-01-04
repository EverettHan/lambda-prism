//===================================================================
// COPYRIGHT Dassault Systemes 2017/02/22
//===================================================================
// CATComputeCivilTransitionCurves.h
// Header definition of class CATComputeCivilTransitionCurves
//===================================================================
//
// Usage notes: Compute the civil transition curve(s) to create a composition
// with canonical curve information.
//
//===================================================================
// Historic:
// 22/02/17 F1Z : Creation
// 30/07/18 KJD : New Create and Compute APIs with a new argt of type CATPGMCivilTransitionInfo
//                This structure stores all the kind of  specifications of the transition in a same object.
//                For the transition Line-Civil-Circle-Civil-Line, the lengths of the first and second civil curves, 
//                 and the radius of the circle arc between the two civil curves.
//                For the transition Line-Civil-Line, the Length of the civil curves but soon the projected Length 
//                 or the ration K  used in the motorway industry.
//                The previous Create and Compute APIs are now deprecated.
// 17/04/20 F4E : Migration CAT2DCurveEvaluator -> CATCivilCurveEvaluator
// 23/12/21 Q48 : Remove interface in GMModelInterfaces
// 23/12/21 Q48 : Remove Set method (curve type should be fixed)
// 31/03/22 Q48 : Remove unused VisualizeSolution
// 31/03/22 Q48 : Add SetReverseMode for complex corner (RampDesign)
//===================================================================

#ifndef CATComputeCivilTransitionCurves_H
#define CATComputeCivilTransitionCurves_H

//===================================================================

// Mathematics
#include "CATCGMVirtualMacros.h"

// GMModelInterfaces
#include "CATCivilCurveDef.h"
#include "CATCivilCurveArchiTEMP.h"

// Geometric Operators
#include "GeoAdvCurves.h"
#include "CATGeoOperator.h"

class CATSoftwareConfiguration;
class CATMathPoint2D;
class CATMathVector2D;

class CATGeoFactory;
class CATCivilTransitionInfo;

class CATCivilCurveEvaluator;
class CATMathCurve;
class CATPGMCivilTransitionInfo;

// ============================================================================================================================= //
//                                                           OPERATOR                                                            //
// ============================================================================================================================= //
class ExportedByGeoAdvCurves CATComputeCivilTransitionCurves : public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATComputeCivilTransitionCurves);
public:
   //-----------------------------------------------------------------------------
   // Object Management
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Do not use this constructor. Use the creation method
   * <tt>CATCreateComputeCivilTransitionCurves</tt>.
   */
   CATComputeCivilTransitionCurves(CATGeoFactory * iFactory);

   /**
   * Destructor
   */
   virtual ~CATComputeCivilTransitionCurves ();

   //-----------------------------------------------------------------------------
   // Options Interface (Set)
   //-----------------------------------------------------------------------------
   //virtual HRESULT Set(const CATCivilCurveType iCurveType) = 0;

   virtual void SetReverseMode() = 0;

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
   virtual HRESULT    GetRunStatus                  ()                                                 const = 0;

   /**
   * Does the computed composition is self intersecting
   */
   virtual CATBoolean IsSelfIntersecting            ()                                                 const = 0;

  /**
  * Initializes the iterator for accessing the civil curve evaluator.
  */
   virtual void       BeginCivilCurve               ()                                                 const = 0;

  /**
  * Sets the iterator to point at the next civil curve evaluator.
  * @return
  * TRUE if there is data,
  * FALSE if the end of the data has been reached.
  */
   virtual CATBoolean NextCivilCurve                ()                                                 const = 0;

   /**
   * @param oCurveEvaluator
   * The curve evaluator of the current civil curve.
   * <br>The object life of the object retrieved has to be handle by the caller. Use delete.
   */
   virtual HRESULT    GetCivilCurve                 (      CATCivilCurveEvaluator * & oCurveEvaluator   ) const = 0;

   /**
   * @param oOrientation
   * The orientation of this current civil curve parametrisation compared to the previous adjacent transition geometry.
   * <br> TRUE means direct, FALSE indirect.
   */
   virtual HRESULT    GetCivilCurveOrientation      (      CATBoolean            & oOrientation      ) const = 0;

   /**
   * @param oStartPoint
   * The common point between PreviousTransitionGeometry and the current civil curve.
   * @param oEndPoint
   * The common point between NextTransitionGeometry and the current civil curve.
   */
   virtual HRESULT    GetCivilCurveExtremities      (CATMathPoint2D              & oStartPoint       ,
                                                     CATMathPoint2D              & oEndPoint         ) const = 0;

   /**
   * Does the end extremity of the current civil curve is confused with
   * the next civil curve start extremity.
   * @return
   * TRUE if confused, FALSE otherwise.
   */
   virtual CATBoolean IsEndExtremityConfusedWithNext()                                                 const = 0;

   /**
   * @param oTransitionGeometry
   * The transition geometry before this current civil curve.
   * @param oIdFromInput
   *  >=0 if the geometry was provided as input, equals -1 otherwise. Filled if the pointer is not null.
   * @Param iHandleMemory
   * Set to TRUE if the user wants the handle the deletion of the CATCivilCurveEvaluator object, FALSE if the operator does it.
   * @return
   * <br>E_FAIL  If there was an issue during the extraction.
   * <br>S_OK    If the extraction has not encountered any issue.
   */
   virtual HRESULT    GetPreviousTransitionGeometry (const CATCivilCurveEvaluator * & oTransitionGeometry     ,
                                                           CATLONG32           *   oIdFromInput      =NULL ,
                                                           CATBoolean              iHandleMemory     =FALSE) const = 0;

   /**
   * @param oTransitionGeometry
   * The transition geometry after this current civil curve.
   * @param oIdFromInput
   *  >=0 if the geometry was provided as input, equals -1 otherwise. Filled if the pointer is not null.
   * @Param iHandleMemory
   * Set to TRUE if the user wants the handle the deletion of the CATCivilCurveEvaluator object, FALSE if the operator does it.
   * @return
   * <br>E_FAIL  If there was an issue during the extraction.
   * <br>S_OK    If the extraction has not encountered any issue.
   */
   virtual HRESULT    GetNextTransitionGeometry     (const CATCivilCurveEvaluator * & oTransitionGeometry     ,
                                                           CATLONG32           *   oIdFromInput      =NULL ,
                                                           CATBoolean              iHandleMemory     =FALSE) const = 0;

   ///**
   //* @nodoc
   //* @nocgmitf
   //* Create the geometric objects factory to represent the solution.
   //**/
   //virtual void    VisualizeSolution     ()                                   = 0;
};

// ============================================================================================================================= //
//                                                          DIRECT FUNCTION                                                      //
// ============================================================================================================================= //

/**
* Line-Civil-Circle-Civil-Line
*/
ExportedByGeoAdvCurves HRESULT CATComputeCivilTransitionCurvesInformation(      CATGeoFactory             * iFactory          ,
                                                                                CATSoftwareConfiguration  * iConfig           ,
                                                                          const CATMathPoint2D            & iPtLine1          ,
                                                                          const CATMathVector2D           & iDirLine1         ,
                                                                          const CATMathVector2D           & iDirOrtho1        ,
                                                                          const CATMathPoint2D            & iPtLine2          ,
                                                                          const CATMathVector2D           & iDirLine2         ,
                                                                          const CATMathVector2D           & iDirOrtho2        ,
                                                                          const CATPGMCivilTransitionInfo * iTransitionInfo   ,
                                                                          const CATCivilCurveType           iCurveType        ,
                                                                                CATMathPoint2D            & oCivilOnLine1     ,
                                                                                CATMathPoint2D            & oCenterCircle     ,
                                                                                CATMathPoint2D            & oCivilOnLine2     ,
                                                                                CATBoolean                & oSelfIntersection ,
                                                                                CATBoolean                & oEndPointsConfused,
                                                                          const CATBoolean                  iReverse = FALSE);

/**
* Line-Civil-Line
*/
ExportedByGeoAdvCurves HRESULT CATComputeCivilTransitionCurvesInformation(      CATGeoFactory             *  iFactory          ,
                                                                                CATSoftwareConfiguration  *  iConfig           ,
                                                                          const CATMathPoint2D             & iPtLine1          ,
                                                                          const CATMathVector2D            & iDirLine1         ,
                                                                          const CATMathVector2D            & iDirOrtho1        ,
                                                                          const CATMathPoint2D             & iPtLine2          ,
                                                                          const CATMathVector2D            & iDirLine2         ,
                                                                          const CATMathVector2D            & iDirOrtho2        ,
                                                                          const CATPGMCivilTransitionInfo *  iTransitionInfo   ,
                                                                          const CATCivilCurveType            iCurveType        ,
                                                                                CATMathPoint2D             & oCivilOnLine1     ,
                                                                                CATCivilCurveEvaluator    *& oCivilCurve       ,
                                                                                CATMathPoint2D             & oCivilOnLine2     );

/**
* @nodoc
* @nocgmitf
*/
//ExportedByGeoAdvCurves void Remove (CATComputeCivilTransitionCurves * & ioComputeCivilTransitionCurves);
#endif
