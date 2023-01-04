#ifndef CATICGMTopologicalBlendCurve_h_
#define CATICGMTopologicalBlendCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATDataType.h"

class CATSoftwareConfiguration;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopologicalBlendCurve;

/**
 * Class defining the topological operator that connects two wire bodies.
 * <br> Continuity criteria can be precised: G0, G1 or G2.
 * <br>The CATICGMTopologicalBlendCurve operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: 
 * the input bodies are not modified. A new resulting body is created, 
 * possibly sharing data with the input bodies. The resulting blend can be created
 * separately from the inputs, or linked to the inputs according to the <tt>SetTrimmingMode</tt> method.  
 *<ul>
 * <li>A CATICGMTopologicalBlendCurve operator is created with the <tt>CATCGMCreateTopologicalBlendCurve</tt> global function.
 * It must be directly released with the <tt>Release</tt> method after use. It is is not streamable. 
 *<li>Options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method 
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopologicalBlendCurve: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopologicalBlendCurve();

  /**
   * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
   * <br>It is possible to <tt>Run</tt> the operator with different inputs or parameters. Each time,
   * a new body is created, that you must remove from the geometric factory @href CATICGMContainer#Remove
   * if you do not want to keep it.
   */
  virtual int Run() = 0;

  /**
   *  Defines the topological blend curve limits (<tt>ADVANCED mode</tt>).
   * @param iWhichWire
   * The first (1) or second (2) wire body. 
   * @param iWire
   * The pointer to the new first wire.
   */
  virtual void SetCurve                 (const CATLONG32   iWhichWire           ,
                                               CATBody  *  iWire                )=0;

  /**
   * Defines the topological blend curve limits (<tt>ADVANCED mode</tt>).
   * @param iWhichWire
   * The first (1) or second (2) wire body. 
   * @param iWireParam
   * The pointer to the new vertex body, defining where the connection must be done.
   */
  virtual void SetCurveParam            (const CATLONG32   iWhichWire           ,
                                               CATBody  *  iWireParam           ) = 0;

  /**
   * Defines the continuity criteria to take into account for a given wire (<tt>ADVANCED mode</tt>).
   * @param iWhichWire
   * The first (1) or the second (2) input wire.
   * @param iTransitionContinuity
   * The continuity criteria
   * <br><b>Legal values</b>: <tt>0</tt> for G0 continuity, <tt>1</tt> for G1 continuity (default value), 
   * <tt>2</tt> for G2 continuity.
   */
  virtual void SetTransitionContinuity  (const CATLONG32   iWhichWire           ,
                                         const CATLONG32   iTransitionContinuity)=0;

  /**
   * Modifies the starting direction of the connecting wire (<tt>ADVANCED mode</tt>).
   * @param iWhichWire
   * The first (1) or the second (2) input wire.
   * @param oTransitionOrientation
   * The orientation of the starting direction, with regards to the default direction given by
   * <tt>SetDefaultConfiguration</tt>.
   * <br><b>Legal values</b>: <tt>1</tt> if the connecting wire starts in the default orientation given
   * by <tt>SetDefaultConfiguration</tt>, </tt>-1</tt>
   * for the opposite orientation.
   */
  virtual void SetTransitionOrientation (const CATLONG32   iWhichWire,
                                         const CATLONG32   iTransitionOrientation)=0;

  /**
   * Returns the starting direction keeping the wire of greatest length (<tt>ADVANCED mode</tt>).
   * @param iWhichWire
   * The first (1) or the second (2) input wire.
   * @param oTransitionOrientation
   * The default orientation of the <tt>iWhichWire</tt>.
   * <br><b>Legal values</b>: <tt>1</tt> if the connecting wire starts in the natural orientation of
   * <tt>iWhichWire</tt>, </tt>-1</tt>
   * for the opposite orientation.
   */
  virtual void SetDefaultConfiguration  (const CATLONG32   iWhichWire,
                                               CATLONG32 & oTransitionOrientation)=0;

  /**
    * Defines the influence of the tangency constraint (<tt>ADVANCED mode</tt>).
    * @param iWhichWire
    * The first (1) or the second (2) input wire.
    * @param iTangencyParameter
    * The value to multiply the tangent, in order to increase or decrease its influence. 
    */
  virtual void SetTangencyParameter     (const CATLONG32   iWhichWire,
                                         const double      iTangencyParameter)=0;

  /**
    * Defines the influence of the curvature constraint (<tt>ADVANCED mode</tt>).
    * @param iWhichWire
    * The first (1) or the second (2) input wire.
    * @param iCurvatureParameter
    * The value to multiply the curvature, in order to increase or decrease its influence. 
    */
  virtual void SetCurvatureParameter    (const CATLONG32   iWhichWire,
                                         const double      iCurvatureParameter)=0;

  /**
   * Defines whether the input bodies must be trimmed (<tt>ADVANCED mode</tt>).
   * @param iWhichWire
   * The first (1) or second (2) wire body.
   * @param iTrimmingMode
   * The trimming mode fot <tt>iWhichWire</tt>.
   * <br><b>Legal values</b>: <tt>0</tt> if <tt>iWhichWire</tt> is not trimmed, <tt>1</tt> if 
   * it is trimmed according to the smart mechanism.
   */
  virtual void SetSupportTrimmingMode   (const CATLONG32   iWhichWire,
                                         const CATLONG32   iTrimmingMode)=0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopologicalBlendCurve(); // -> delete can't be called
};

/**
 * Creates a topological operator that connects two wire bodies.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to object defining the journal and the software configuration. If the pointer to the
 * journal is <tt>NULL</tt>, the journal is not filled in.
 * @param iWire1
 * The pointer to the first wire body, containing only one wire. 
 * @param iWireParam1
 * The pointer to a vertex body on <tt>iWire1</tt>, defining where the connection must be done.
 * @param iWire2
 * The pointer to the second wire body, containing only one wire. 
 * @param iWireParam2
 * The pointer to a vertex body on <tt>iWire2</tt>, defining where the connection must be done.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMTopologicalBlendCurve
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopologicalBlendCurve *CATCGMCreateTopologicalBlendCurve(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iWire1,
  CATBody *iWireParam1,
  CATBody *iWire2,
  CATBody *iWireParam2);

#endif /* CATICGMTopologicalBlendCurve_h_ */
