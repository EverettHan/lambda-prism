#ifndef CATMassProperties1D_H
#define CATMassProperties1D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 
#include "CATIACGMLevel.h"
#include "CATCGMOperator.h"

#include "Y3DYNOPE.h"

#include "CATCurve.h"
class CATCrvParam;
class CATSoftwareConfiguration;

/**
 * Class defining the geometric operator to perform a global analysis on a CATCurve.
 *<br>This class is transient and cannot be streamed. It performs conversion from curve parameter
 * to length and the converse.
 * The class is created with the <tt>CATDynCreateMassProperties1D</tt> global method and is deleted
 * with the usual C++ delete operator.
 */
#ifdef CATIACGMV5R21
class ExportedByY3DYNOPE CATDynMassProperties1D : public CATCGMOperator
#else
class ExportedByY3DYNOPE CATDynMassProperties1D : public CATCGMVirtual
#endif
{
  CATCGMVirtualDeclareClass(CATDynMassProperties1D);
  public :
      /** @nodoc */
#ifdef CATIACGMV5R21
  CATDynMassProperties1D(CATGeoFactory *iFactory);
#else
  CATDynMassProperties1D();
#endif
  virtual ~CATDynMassProperties1D() ;
  
  /**
  * @nodoc 
  * Sets the operator in a mode where, in the GetParamFromLength method,
  * it estimates the solution before starting the computation.
  * Better and quicker results, but the behaviour modification may
  * affect sensitive algorithms.
  * @param iEstimate
  * The type of search.
  * <br><b>Legal values</b>:
  *  <dl><dt><tt>FALSE</tt><dd> the operator uses the low value of the limits as
  * an initial point.
  *<dt><tt>TRUE</tt><dd> the operator uses an estimation of the solution as an
  * initial point.</dl> 
  */
  virtual void SetEstimateInit(const CATBoolean &iEstimate=TRUE) = 0;
  
  
  /**
   * Returns the CATCrvParam corresponding to the point at a given length
   * of another point.
   * @param iParam
   * The point on the curve.
   * @param iLength
   * The length on the curve measured from the point <tt>iParam</tt>.
   * @return
   * The corresponding point.
   */
  virtual CATCrvParam GetParamFromLength(const CATCrvParam &iParam,
					 const CATLength   &iLength) const = 0; 
  
  /**
   * Returns the length between two points of a CATCurve.
   * @param iParam1
   * The first point.
   * @param iParam2
   * The second point.
   * @return
   * The length between the two points.
   */
     virtual CATLength GetLengthFromParams(const CATCrvParam &iParam1,
					   const CATCrvParam &iParam2) const  = 0;
  
  /**
   * Returns the total length of a CATCurve.
   * @return
   * The total length of the curve
   */
  virtual CATPositiveLength GetLength() const = 0; 
};


/**
 * Creates a global analyzer on a CATCurve.
 * @param iCurveToAnalyze
 * The pointer to the curve to analyze.
 * @param iSoftwareConfig
 * The pointer to the CATSoftwareConfiguration.
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */  
ExportedByY3DYNOPE CATDynMassProperties1D* CATDynCreateMassProperties1D(CATCurve* iCurveToAnalyze,
                                                                        CATSoftwareConfiguration * iSoftwareConfig);

/**
 * @deprecated V5R14
 * Use the signature with CATSoftwareConfiguration as second argument.
 * Creates a global analyzer on a CATCurve.
 * @param iCurveToAnalyze
 * The pointer to the curve to analyze.
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */  
ExportedByY3DYNOPE CATDynMassProperties1D* CATDynCreateMassProperties1D(const CATCurve* iCurveToAnalyze);

#endif 






