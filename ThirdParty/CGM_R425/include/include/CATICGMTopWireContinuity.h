#ifndef CATICGMTopWireContinuity_h_
#define CATICGMTopWireContinuity_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATIACGMLevel.h"

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATFreeFormDef.h"
#include "CATMathDef.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopWireContinuity;

   #define CATICGMTopWireContinuity_V1    // INTERNAL USE DS ONLY flag for version 1 of this operator, always active.              NLD111219

// #ifdef CATIACGMR423CAA
// #define CATICGMTopWireContinuity_V2    // INTERNAL USE DS ONLY flag for version 2 of this operator, will be activated later on. NLD111219
// #endif
/**
 *=============================================================================
 *
 * CATICGMTopWireContinuity
 * -----------------
 * Compute continuity information at the vertices of a wire body.
 * The wire body has a single wire domain that may be open or closed.
 * Operator returns :
 * - the G order of continuity at each connection ( G0, G1 or G2 )
 * - the distance gap between incident edges at each connection
 * - the angular gap between tangents to edges at each connection, in degrees.
 * - the G2 curvature ratio at each connection, in ]0..1]
 *<ul>
 * <li>A <tt>CATICGMTopWireContinuity</tt> operator is created with the <ttCATCreateTopWireContinuity</tt> global function:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable.
 * <li>Optional parameter MeasureMode can be specified before using the <tt>Run</tt> method.
 * <li>The continuity order of the connection is accessed by the <tt>GetGOrder</tt> method which takes the connection rank as an
 * argument.
 * <li>The position and tangency gaps are accessed by the <tt>GetDeltaPt</tt> and <tt>GetDeltaTg</tt> methods. The ratio
 * <li> of the smaller to the larger curvature is returned by the <tt>GetRatioCv</tt> method.
 * <li>Caution: the curvature measure implementation has the default historical value 1, the recommended mode being 2
 * MeasureMode = 1 or 2
 * <li>MeasureMode = 1  a C2 measure by comparison of
 * difference between curvature radii and CATEpsg
 * <li>MeasureMode = 2  a standard C2 measure corresponding to CatC2
 * <li>MeasureMode can be set by <tt>SetMeasureMode</tt> method, if available on this API level
 *</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopWireContinuity: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopWireContinuity();

  #ifdef CATICGMTopWireContinuity_V2
  /**
  * Choose curvature measure implementation
  * iMeasureMode = 1 or 2
  * In both implementations :
  *     - C0 measure based on standard C0 measure corresponding to CatC0
  *     - C1 measure based on standard C1 measure corresponding to CatC1
  * iMeasureMode = 1 to perform a C2 measure by comparison of
  *                difference between curvature radii and CATEpsg
  * iMeasureMode = 2 to perform a standard C2 measure corresponding to CatC2
  * default (historical) value is 1.
  * @param iMeasureMode
  * The mode of curvature measurement
  */
  virtual void                SetMeasureMode(CATLONG32 iMeasureMode) = 0;
  #endif

  /**
  * Run : compute continuity informations on body wire
  */
  virtual int                 Run() = 0;

  /**
  * Get the number of connection vertices in the wire.
  * equal to the NbEdges for a closed wire, to (NbEdges - 1) for an open wire,
  * NbEdges being the number of edges in the wire
  */
  virtual int                 NbVertex() = 0;

  /**
  * GetGOrder : returns G continuity order of connection with rank iConnectionRank
  * @param iConnectionRank
  * rank of connection.
  * @return
  * returns 0 if OK, nonzero on error
  */
  virtual CATLONG32           GetGOrder(int               iConnectionRank,
                                        CATFrFContinuity& oGOrder) = 0;

  /**
  * GetDeltaPt : returns oL = G0 gap between points at connection iConnectionRank
  * @param iConnectionRank
  * rank of connection.
  * @return
  * returns 0 if OK, nonzero on error
  */
  virtual CATLONG32           GetDeltaPt(int              iConnectionRank,
                                         CATLength      & oL     ) = 0;

  /**
  * GetDeltaTg : returns oA = G1 gap between tangents at connection iConnectionRank, in degrees
  * @param iConnectionRank
  * rank of connection.
  * @return
  * returns 0 if OK, nonzero on error
  */
  virtual CATLONG32           GetDeltaTg(int              iConnectionRank,
                                         CATAngle       & oA     ) = 0;

  #ifdef CATICGMTopWireContinuity_V2
  /**
  * GetRatioCv : returns oRatioCv = G2 curvature ratio of curvature vectors at connection iConnectionRank
  * If the two curvature vectors are VC1 and VC2, then the curvature ratio is defined as
  *
  *                   1
  * ------------------------------------------
  *    1 + ||VC1-VC2||/max(||VC1||,||VC2||)
  *
  * This method should be called only if SetMeasureMode(2) was called.
  * In other case, oRatio is non-sensical and a value != 0 will be returned.
  * After SetMeasureMode(2) :
  * @param iConnectionRank
  * rank of connection.
  * @param oRatioCv
  * G2 curvature ratio. Measure mode must be set to 2 for this to be meaningful
  * @return
  * returns 0 if OK, nonzero on error.
  */
  virtual CATLONG32           GetRatioCv(int              iConnectionRank ,
                                         double         & oRatioCv) = 0;
  #endif


  #ifdef CATICGMTopWireContinuity_V2
  /**
  * Get curvature measure implementation
  * MeasureMode = 1 or 2
  * MeasureMode = 1  a C2 measure by comparison of
  *                difference between curvature radii and CATEpsg
  * MeasureMode = 2  a standard C2 measure corresponding to CatC2
  * default (historical) value is 1.
  * @return
  * The mode of curvature measurement
  * <br><b>Legal values</b>:
  * <dl><dt>1<dd> No maximum distance.
  * <dt>2<dd> Maximum distance has been set.</dl>
  */
  virtual CATLONG32           GetMeasureMode() = 0;

  #endif

  virtual CATLength           GetTolPt() = 0;

  virtual CATAngle            GetTolTg() = 0;

  virtual double              GetTolCv() = 0;

protected:
  /**
   * Destructor
   */
  virtual                    ~CATICGMTopWireContinuity(); // -> delete can't be called
};

/**
 * Creates the operator to evaluate continuity order and values at vertices of a wire.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * @param iWireBody
 * The body to evaluate. It is a body made of a single wire domain.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces
CATICGMTopWireContinuity *CATCGMCreateTopWireContinuity(CATGeoFactory * iFactory,
                                                        CATTopData    * iTopData,
                                                        CATBody       * iWireBody);

#endif /* CATICGMTopWireContinuity_h_ */
