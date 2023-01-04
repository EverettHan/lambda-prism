//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
//
// CATIntCurveReducer:
//    Header file for the CATIntCurveReducer operator.
//
//    The purpose of the operator is to create int curves by ignoring the arcs
//    of an input int curve that lie outside specified intervals.
//
//    The input int curve must consist of two p-spline curves, and must not
//    have a map of type "adjusted" (in which only one curve and its limits on
//    the edge curve are stored).
//
//=============================================================================
// Usage notes:
//=============================================================================
// 22/08/17 R1Y Creation.
//=============================================================================

#ifndef CATIntCurveReducer_H
#define CATIntCurveReducer_H

// System
#include "CATListOfCATIntCurves.h"

// Mathematics
#include "CATSkillValue.h"

// GeometricOperators
#include "Y30C3XGG.h"
#include "CATGeoOperator.h"

class CATMathInterval;

/**
* Class defining the CATIntCurveReducer operator, which is used to create int
* curves by ignoring the arcs of an input int curve that lie outside specified
* intervals.
* The input int curve must consist of two p-spline curves, and must not have a
* map of type "adjusted".
* <br> The operator returns 1 for success and 0 for failure.
*<ul>
*<li>The CATIntCurveReducer operator is created with the
* <tt>CreateCATIntCurveReducer</tt> method and directly <tt>delete</tt>d with
* the usual C++ delete operator.
*<li>In the case of <tt>BASIC</tt> mode, the operation is automatically
* performed at the operator creation. 
* In the case of <tt>ADVANCED</tt> mode, options can be selected with the
* <tt>Set</tt> methods, before asking for the computation with the <tt>Run</tt>
* method.
*<li>In both cases, the result is accessed using <tt>GetResult()</tt>.
*</ul>
*/
class ExportedByY30C3XGG CATIntCurveReducer : public CATGeoOperator
{
protected:

  /** 
  * @nodoc
  * Do not use these constructors; instead, use the creation method
  * <tt>CreateCATIntCurveReducer</tt>.
  */
  CATIntCurveReducer();
  CATIntCurveReducer(CATGeoFactory * const iFactory);

public:

  /** 
  * @nodoc
  * Destructor.
  */
  virtual ~CATIntCurveReducer();

  //-----------------------------------------------------------------------
  // Methods for setting data.
  //-----------------------------------------------------------------------

  /**
  * Sets the int curve from which int curves are to be created using the
  * specified intervals.
  * @param iIntCurve
  * The int curve from which int curves are to be created using the
  * specified intervals.
  */
  virtual void SetIntCurve(const CATIntCurve * const iIntCurve) = 0;

  /**
  * Sets the intervals from which int curves are to be created.
  * @param iNumIntervals
  * The number of intervals from which int curves are to be created.
  * @param iIntervals
  * The intervals from which int curves are to be created.
  */
  virtual void SetIntervals(const CATLONG32               iNumIntervals,
                                  CATMathInterval * const iIntervals) = 0;

  //-----------------------------------------------------------------------
  // Methods for getting data.
  //-----------------------------------------------------------------------

  /** 
  * @nodoc
  * Returns the software configuration to be taken into acccount by
  * <tt>this</tt> operator.
  * @return
  * The software configuration.
  */
  virtual CATSoftwareConfiguration * GetSoftwareConfiguration() const = 0;

  /**
  * Returns the number of int curves that are created from <tt>this</tt>
  * operator.
  * @return
  * The number of int curves that are created.
  */
  virtual CATLONG32 GetNumIntCurves() const = 0;

  /**
  * Returns the int curves that are created from <tt>this</tt> operator.
  * @param iIntCurves
  * The int curves that are created.
  */
  virtual void GetResult(CATLISTP(CATIntCurve) & oIntCurves) const = 0;

  /**
  * Returns the newly created int curve (from <tt>this</tt> operator)
  * that covers the input interval with a specified index.
  * @param iIntervalIndex
  * The index of the required input interval (with the index of the first
  * interval being zero).
  * @return
  * The newly created int curve that covers the input interval with the
  * specified index.
  */
  virtual const CATIntCurve * GetCurveOnInterval(CATLONG32 iIntervalIndex) const = 0;
};

/**
 * Creates an operator for creating int curves from specified intervals.
 * @param iFactory
 * The factory.
 * @param iConfig
 * The software configuration.
 * @param iIntCurve
 * The int curve from which int curves are to be created using specified
 * intervals.
 * @param iNumIntervals
 * The number of intervals from which int curves are to be created.
 * @param iIntervals
 * The intervals from which int curves are to be created.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator
 *                            creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute
 *                               the operation.</dl>
 * @return
 * The pointer to the created operator. To delete, use the usual C++ delete
 * operator after use.
*/
ExportedByY30C3XGG CATIntCurveReducer * CATCreateIntCurveReducer(      CATGeoFactory            * const iFactory,
                                                                       CATSoftwareConfiguration * const iConfig,
                                                                 const CATIntCurve              * const iIntCurve,
                                                                 const CATLONG32                        iNumIntervals,
                                                                       CATMathInterval          * const iIntervals,
                                                                 const CATSkillValue                    iMode = BASIC);

#endif
