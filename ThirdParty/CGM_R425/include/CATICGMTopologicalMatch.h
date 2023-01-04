#ifndef CATICGMTopologicalMatch_h_
#define CATICGMTopologicalMatch_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATDataType.h"
#include "CATFreeFormDef.h"
#include "CATSkillValue.h"

class CATBody;
class CATMathDirection;
class CATVertex;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopologicalMatch;

/**
 * Class defining the topological operator that matches parts of skin boundaries.
 * <br>The skins must be composed of one face, which boundaries are on the surface boundaries.
 * The matching operation is done with respect to continuity criteria along the
 * boundaries. If the G0 continuity is imposed on a boundary, the control points of this boundary
 * are taken into account. If the G1 continuity is imposed, the first rank (on the boundary) and
 * second rank of control points are taken into account. If the G2 continuity is imposed, 
 * three ranks of control points are taken into account. It is possible to optimize 
 * the modifications of these ranks (<tt>SetOptimization</tt>), as well as diffuse the modifications
 * on the whole surface (<tt>SetDiffusion</tt>).
 * The CATICGMTopologicalMatch operator can be used in two different match configurations:
 * <ul>
 *   <li>The matching operator deforms the selected boundary edges of the first skin, to be 
 * coincident with boundary edges of other skins, with respect to a given continuity criteria
 * ("multiple sides matching"). 
 *   <li>The matching operator deforms both skins that must match along a given edge 
 * ("both" matching).
 * </ul>
 * The operator follows the use frame of all operator. It satisfies to the smart mechanism: the
 * input bodies are not modified. New one are created, possibly sharing data with the input ones.
 *<ul>
 * A CATICGMTopologicalMatch operator is created with the <tt>CATCGMCreateTopologicalMatch</tt> global function 
 * for the multiple sides matching
 * and the <tt>CATCGMCreateTopologicalMatchBoth</tt> global function for the both matching; it must be
 * directly released with the <tt>Release</tt> method after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with additional continuity constraints.
 *<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 *</ul>
 *
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopologicalMatch: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopologicalMatch();

  /**
 * Returns the result of <tt>this</tt> operator.
 * <br>The bodies are created by the operator. 
 * You must delete them with the @href CATICGMContainer#Remove 
 * method if you do not want to keep them.
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @return
 * The pointer to the created body corresponding to the deformation of the <tt>iSkinIndex</tt> surface.  
 */
  virtual CATBody *GetResult(CATLONG32 iSkinIndex) const = 0;

  /**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 */
  virtual int Run() = 0;

  /**
 * Defines a new matching operation (<tt>ADVANCED</tt> mode).
 * <br>The result of the preceeding <tt>Run</tt> is set for the next run. This allows you to refine the continuity 
 * criteria of the matching. Use the <tt>Setxxx</tt> methods to tune the criteria, and <tt>Run</tt> again
 * the operator. New resulting bodies are created.
 */
  virtual void UseTheLastRunResult() = 0;

  /**
 * Defines the continuity criteria for <tt>this</tt> matching operation (<tt>ADVANCED</tt> mode).
 * @param iWireIndex
 * The index (beginning at 0) of the wire on which the continuity criteria is defined.
 * @param iContinuity
 * The type of continuity for <tt>iWireIndex</tt>. Set to <tt>CATFrFPointCont</tt> (G0 continuity), in default mode.
 */
  virtual void SetConnectionContinuity(
    CATLONG32 iWireIndex,
    CATFrFContinuity iContinuity) = 0;

  /**
 * Returns the continuity criteria for <tt>this</tt> matching operation (<tt>ADVANCED</tt> mode).
 * @param iWireIndex
 * The index (beginning at 0) of the wire on which the continuity criteria is defined.
 * @return
 * The type of continuity for <tt>iWireIndex</tt>.
 */
  virtual CATFrFContinuity GetConnectionContinuity(CATLONG32 iWireIndex) const = 0;

  /**
 * Defines a continuity criteria on the boundaries that are not part of the boundaries to match (<tt>ADVANCED</tt> mode).
 * <br>In case of conflict with the connection continuity, the priority is given to the connection
 * continuity.
 * @param iWireIndex
 * The index (beginning at 0) of the wire to match. The continuity  will be defined on the opposite wire.
 * Remember that the only works on faces with four edges defined on the surface coundaries.
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @param iContinuity
 * The type of continuity for <tt>iWireIndex</tt>. Set to <tt>CATFrFPointCont</tt> (G0 continuity), in default mode.
 */
  virtual void SetOppositeSideContinuity(
    CATLONG32 iWireIndex,
    CATLONG32 iSkinIndex,
    CATFrFContinuity iContinuity) = 0;

  /**
 * Returns the continuity criteria on the boundaries that are not part of the boundaries to match (<tt>ADVANCED</tt> mode).
 * <br>In case of conflict with the connection continuity, the priority is given to the connection
 * continuity.
 * @param iWireIndex
 * The index (beginning at 0) of the wire to match. The continuity  will be defined on the opposite wire.
 * Remember that the only works on faces with four edges defined on the surface coundaries.
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @return
 * The type of continuity for <tt>iWireIndex</tt>. Set to <tt>CATFrFPointCont</tt> (G0 continuity), in default mode.
 */
  virtual CATFrFContinuity GetOppositeSideContinuity(
    CATLONG32 iWireIndex,
    CATLONG32 iSkinIndex) const = 0;

  //======================
  //  Orientation Methods
  //======================
  /**
 * Asks for the default choice of the relative orientation of the wires to match (<tt>ADVANCED</tt> mode).
 */
  virtual void SetDefaultRelativeWireOrientation() = 0;

  /**
 * Asks for reversing the default relative orientation of the wires to match (<tt>ADVANCED</tt> mode).
 * <br> This can used to manualy manage the twist.
 */
  virtual void ReverseRelativeWireOrientation() = 0;

  /**
 * Asks for the default choice of the transition between the surface to match (<tt>ADVANCED</tt> mode). 
 */
  virtual void SetDefaultTransitionOrientation() = 0;

  /**
 * Asks for reversing the default transition between the surface to match (<tt>ADVANCED</tt> mode).
 */
  virtual void ReverseTransitionOrientation(CATLONG32 iSkinIndex) = 0;

  //==================
  // Diffusion  
  //==================
  /**
 * Defines the diffusion of the deformation on the whole surface (<tt>ADVANCED</tt> mode).
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @param iDiffusion
 * The diffusion.
 * <br><b>Legal values</b></tt>: 0 for only deform the control points impacted by the continuity criteria
 * (default value), 1 to diffuse the modifiations on the whole surface.
 */
  virtual void SetDiffusion(CATLONG32 iSkinIndex, CATLONG32 iDiffusion) = 0;

  /** 
 * Returns the level of diffusion of the deformation on the whole surface (<tt>ADVANCED</tt> mode).
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @return
 * The diffusion.
 * <br><b>Legal values</b></tt>: 0 for only deform the control points impacted by the continuity criteria, 1 to diffuse
 * the modifiations on the whole surface.
 */
  virtual CATLONG32 GetDiffusion(CATLONG32 iSkinIndex) const = 0;

  /**
 * Asks fot the optimization of the local deformation (<tt>ADVANCED</tt> mode).
 * @param iOptimization
 * The optimization is set with 1  (default mode) and unset with 0.
 */
  virtual void SetOptimization(CATLONG32 iOptimization) = 0;

  //=============================
  //  Both Configuration Methods
  //=============================
  /**
 * Sets the match factor in case of both matching and <tt>ADVANCED</tt> mode.
 * @param iContinuity
 * The continuity order on the boundary
 * @param iFactor
 * The relative influence of each surface.
 * <br><b>Legal values</b>: <tt>0 <= iFactor <= 1 </tt>, <tt>0<= iFactor <=0.5 </tt> to enhance the influence
 * the first surface, <tt>0<= iFactor <=0.5 </tt> to enhance the influence of the second surface. 
 * Set to <tt>0.5</tt> by default.
 */
  virtual void SetMatchFactor(CATFrFContinuity iContinuity, double iFactor) = 0;

  /**
 * Returns the match factor.
 * @return
 * The relative influence of each surface.
 * <br><b>Legal values</b>: <tt>0 <= iFactor <= 1 </tt>, <tt>0<= iFactor <=0.5 </tt> to enhance the influence
 * the first surface, <tt>0<= iFactor <=0.5 </tt> to enhance the influence of the second surface. 
 */
  virtual double GetMatchFactor(CATFrFContinuity iContinuity) const = 0;

  /**
 * Defines a stiffness on the matching zone in case of both matching and <tt>ADVANCED</tt> mode.
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @param iTangentRatio
 * The global tangent parameter ratio. Can be used for connection continuity greater or equal to G1.
 * <br><b>Legal values</b>: <tt>0. <= iTangentRatio <= 1.</tt>. Set by default to <tt>1.</tt>.
 */
  virtual void SetGlobalTangentParameter(
    CATLONG32 iSkinIndex,
    double iTangentRatio) = 0;

  /**
 * Retrieves the stiffness on the matching zone in case of both matching and <tt>ADVANCED</tt> mode.
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @param ioTangentRatio
 * The global tangent parameter. Can be used for connection continuity greater or equal to G1.
 * <br><b>Legal values</b>: <tt>0. <= iTangentRatio <= 1.</tt>.
 */
  virtual void GetGlobalTangentParameter(
    CATLONG32 iSkinIndex,
    double &ioTangentRatio) const = 0;

  /**
 * Defines a stiffness on the matching zone in case of both matching and <tt>ADVANCED</tt> mode.
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @param iCurvatureRatio
 * The global curvature parameter ratio. Can be used for connection continuity greater or equal to G2.
 * <br><b>Legal values</b>: <tt>0. <= iCurvatureRatio <= 1.</tt>. Set by default to <tt>1.</tt>.
 */
  virtual void SetGlobalCurvatureParameter(
    CATLONG32 iSkinIndex,
    double iCurvatureRatio) = 0;

  /**
 * Retrieves the stiffness on the matching zone in case of both matching and <tt>ADVANCED</tt> mode.
 * @param iSkinIndex
 * The index of the input surface.
 * <br><b>Legal values</b>:
 * <ul><li>In case of multiple sides matching, only the first skin is modified, such that <tt>iSkinIndex=0</tt>.
 * <li>In case of both matching,<tt>iSkinIndex=0</tt> is set for the first input skin,
 * <tt>iSkinIndex=1</tt> is set for the second one.
 * </ul>
 * @param ioCurvatureRatio
 * The global curvature parameter ratio. Can be used for connection continuity greater or equal to G2.
 * <br><b>Legal values</b>: <tt>0. <= iCurvatureRatio <= 1.</tt>. Set by default to <tt>1.</tt>.
 */
  virtual void GetGlobalCurvatureParameter(
    CATLONG32 iSkinIndex,
    double &ioCurvatureRatio) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopologicalMatch(); // -> delete can't be called
};

/*
protected :
  virtual CATTopologicalMatch(CATTopologicalMatch &);
*/
/**
 * Creates a topological operator of multiple sides matching.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iWire1
 * The array <tt>[NbWires]</tt> of pointers to wire body on the first same surface. 
 * Each body only contains one wire with one edge. The geometry of the edge must
 * be a boundary of <tt>iSupport1</tt>.
 * @param iWire2
 * The array <tt>[NbWires]</tt> of pointers to the corresponding wire bodies to match.
 * Each body only contains one wire with one edge. The geometry of the edge must
 * be a boundary of the corresponding surface in <tt>iSupport2</tt>. 
 * @param iNbWires
 * The number of wires to match.
 * @param iSupport1
 * The pointer to the common surface of the wire bodies of <tt>iWire1</tt>.
 * @param iSupport2
 * The array <tt>[NbWires]</tt> pointers to the corresponding surfaces of the wire bodies of <tt>iWire2</tt>.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMTopologicalMatch
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopologicalMatch *CATCGMCreateTopologicalMatch(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody **iWire1,
  CATBody **iWire2,
  CATLONG32 iNbWires,
  CATBody *iSupport1,
  CATBody **iSupport2,
  CATSkillValue iMode = BASIC);

#endif /* CATICGMTopologicalMatch_h_ */
