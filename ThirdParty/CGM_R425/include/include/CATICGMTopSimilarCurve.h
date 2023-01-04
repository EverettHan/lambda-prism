#ifndef CATICGMTopSimilarCurve_h_
#define CATICGMTopSimilarCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATDataType.h"

class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSimilarCurve;

/**
 * Class defining the topological operator that connects two wires with 
 * the "Base Curve" option.
 *<ul>
 * <li>A CATICGMTopSimilarCurve operator is created with the <tt>CATCGMCreateTopSimilarCurve</tt> global function;
 * it must be directly released with the <tt>Release</tt> method after use. 
 * It is is not streamable. 
 *<li>Options such as the start and end points must be 
 * precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.Although several sucessive 
 * <tt>Run</tt>s with different inputs
 * are possible, it is strongly recommended to <tt>Run</tt> it only once.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopSimilarCurve: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopSimilarCurve();

  /**
  * Defines the start point.
  * @param iStartPoint
  * The start point. It must be laid down on <tt>iCurve1</tt>
  * @param iCurve
  * The first curve. If iCurve1 is NULL the point is free.
  */
  virtual int                     SetStartPoint            (      CATBody                *  iStartPoint              ,
                                                                  CATBody                *  iCurve1                  )=0;

  /**
  * Defines the end point.
  * @param iEndPoint
  * The endpoint. It must be laid down on <tt>iCurve2</tt>
  * @param iCurve2
  * The second curve. If iCurve2 is NULL the point is free.
  */
  virtual int                     SetEndPoint              (       CATBody               *  iEndPoint                ,
                                                                   CATBody               *  iCurve2                  )=0;


  /**
  * Defines whether the input bodies must be trimmed.
  * @param iWire
  * The first (1) or the second (2) wire body.
  * If not precised and if iTrimmingMode is set to ON,
  * the two wire bodies are trimmed.
  * @param iTrimmingMode
  * trim ON (1), trim OFF (0)                
  */
  virtual void                    SetTrimmingMode           (const CATLONG32                iWire                    ,
                                                             const CATLONG32                iTrimmingMode            ) = 0;

  /**
  * Runs <tt>this</tt> operator.
  */
  virtual int                     Run                       ()                                                         = 0;

  /**
  * Returns the result of <tt>this</tt> operator.
  * @return
  * The pointer to the created body. You must delete it with the @href CATICGMContainer#Remove 
  * method if you do not want to keep it.
  */
  virtual CATBody               * GetResult                 ()                                                         = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopSimilarCurve(); // -> delete can't be called
};

/**
 * Creates a topological operator that connects to curves according to the
 * specification of a base curve.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBaseCurve
 * The base curve.
 * @param iInputCurve1
 * One of the wire to be connected. The start/end point must be laid down on iInputCurve1. 
 * If NULL is specified, the start/end point is free.
 * @param iInputCurve2
 * The other wire to be connected. The end/start point must be laid down on iInputCurve2.
 * If NULL is specified, the end/start point is free.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopSimilarCurve *CATCGMCreateTopSimilarCurve(
                                              CATGeoFactory * iFactory     ,
                                              CATTopData    * iData        ,
                                              CATBody       * iBaseCurve   ,
                                              CATBody       * iInputCurve1 = NULL,
                                              CATBody       * iInputCurve2 = NULL);

#endif /* CATICGMTopSimilarCurve_h_ */
