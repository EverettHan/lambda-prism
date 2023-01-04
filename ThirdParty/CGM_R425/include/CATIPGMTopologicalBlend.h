#ifndef CATIPGMTopologicalBlend_h_
#define CATIPGMTopologicalBlend_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATBlendValue.h"

class CATFrFCCvLimits;
class CATFrFCCvParam;
class CATFrFNurbsMultiForm;
class CATFrFSweepChecker;
class CATLaw;
class CATTopData;
class CATVertex;
class CATFrFCCvParam;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopologicalBlend;

//#define CATIPGMTopologicalBlend_BlendCouplingPoint
/**
 * @deprecated V5R10 CATIPGMTopBlend
 * Class defining the topological operator that connects two wires with a skin.
 * <br> Continuity criteria can be precised: G0, G1 or G2 if the supporting surfaces of the wires
 * are given, G0 otherwise.
 * <br>The CATIPGMTopologicalBlend operator creates the resulting blend
 * separately from the inputs: the topology of the input bodies is not used to define the topology
 * of the resulting body.  
 *<ul>
 * <li>A CATIPGMTopologicalBlend operator is created with the <tt>CATPGMCreateTopologicalBlend</tt> global function;
 * it must be directly released with the <tt>Release</tt> method after use. It is is not streamable. 
 *<li>Options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.Although several sucessive 
 * <tt>Run</tt>s with different inputs
 * are possible, it is strongly recommended to <tt>Run</tt> it only once.
 * <li>The journal corresponding to the blend operation is not yet implemented.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalBlend: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopologicalBlend();

  /**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 * <br>Use it only once after setting the options. If you want to do another run, create another operator.
 */
  //virtual void Run()=0;
  //virtual int Run;
  /**
 * Returns the result of <tt>this</tt> operator.
 * @return
 * The pointer to the created body. You must delete it with the @href CATICGMContainer#Remove 
 * method if you do not want to keep it.
 */
  virtual CATBody *GetResult() = 0;

 /**
  * @nodoc
  */
  virtual void                      GetResult                (     CATLISTP(CATGeometry)    & Surfaces                 ,
                                                                   CATListOfInt             & NbOfEdgeCurvesBySurf     ,
                                                                   CATLISTP(CATGeometry)    & EdgeCurves               ,
                                                                   CATListOfInt             & EdgeCurvesOrientations   ) const = 0 ;

  /** 
 * @nodoc 
 */
  virtual void                      GetResult                (     CATFrFNurbsMultiForm    *& oMultiForms              ) const = 0 ;

  /**
 * Retrieves the default orientations taken by <tt>this</tt> operator (<tt>ADVANCED mode</tt>).
 * <br>The operator does an analysis of the inputs, in order to avoid twisted surfaces for examples.
 * This method returns the relative orientations found after this analysis.
 * Let <tt>T=oWireOrientationSide * (Tangent Vector to Wire)</tt> be the tangent to the wire, 
 * corrected by the default orientation. Let now <tt>N</tt> be the normal to the skin body.
 * The transition orientation defines how the blend goes from the initial wires: it takes the 
 * direction of <tt>oTransitionOrientationSide*(T^N)</tt>, where <tt>^</tt> is the vectorial product.
 * @param oWireOrientationSide1
 * The default orientation of the first wire.
 * <br><b>Legal values</b>: <tt>1</tt> if the first wire is taken with its natural orientation, </tt>-1</tt>
 * for an opposite orientation.
 * @param oWireOrientationSide2
 * The default orientation of the second wire. Not use in case of extrapolation.
 * <br><b>Legal values</b>: <tt>1</tt> if the second wire is taken with is natural orientation, </tt>-1</tt>
 * for an opposite orientation.
 * @param oTransitionOrientationSide1
 * The transition from the first wire.
 * @param oTransitionOrientationSide2
 * The transition from the second wire.
 */
  virtual void                      SetDefaultConfiguration  (      CATLONG32                & oWireOrientationSide1      ,
                                                                    CATLONG32                & oWireOrientationSide2      ,
                                                                    CATLONG32                & oTransitionOrientationSide1,
                                                                    CATLONG32                & oTransitionOrientationSide2) = 0;

  /**
 * Defines the relative orientation of the wire (<tt>ADVANCED mode</tt>).
 * @param iWhichWire
 * The first (1) or the second (2) input wire.
 * @param iWireOrientation
 * The relative orientation with respect to the default given by the <tt>SetDefaultConfiguration</tt> 
 * method.
 * <br><b>Legal values</b>: <tt>1</tt> if the orientation of the <tt>iWhichWire</tt> wire is the default
 * computed by <tt>this</tt> operator, <tt>-1</tt> for the opposite orientation.
 */
  virtual void                      SetWireOrientation       (const CATLONG32                  iWhichWire                 ,
                                                              const CATLONG32                  iWireOrientation           ) = 0; 

  /**
 * @nodoc
 */
  virtual void                      ReverseWireOrientation   (const CATLONG32                  iSide                      ) = 0;

  /**
 * Defines the continuity criteria to take into account for a given wire (<tt>ADVANCED mode</tt>).
 * @param iWhichWire
 * The first (1) or the second (2) input wire.
 * @param iTransitionContinuity
 * The continuity criteria
 * <br><b>Legal values</b>: <tt>0</tt> for G0 continuity, <tt>1</tt> for G1 continuity, 
 * <tt>2</tt> for G2 continuity.
 */
  virtual void                      SetTransitionContinuity  (const CATLONG32                  iWhichWire                 ,
                                                              const CATLONG32                  iTransitionContinuity      ) = 0;

  /**
 * @nodoc
 */
  virtual void                      SetDefaultTopologicalOrientation(CATLONG32                 iTopoOrGeo                 ) = 0; 

  /**
 * Defines the way of construction of the second rank of control points of the blend surface
 * (<tt>ADVANCED mode</tt>).
 * <br>In case of analytical mode and G1 or G2 continuity.
 * @param iBlendTgContMode
 * The way of construction. By default, it is set to <tt>CATBlendCrossTgCont</tt>.
 */
  virtual void                      SetBasicTangencyContinuityMode(const CATBlendTgContMode    iBlendTgContMode)=0;

  /**
 * Defines the relative orientation of the wire (<tt>ADVANCED mode</tt>).
 * @param iWhichWire
 * The first (1) or the second (2) input wire.
 * @param iTransitionContinuity
 * The relative transition with respect to the default given by the <tt>SetDefaultConfiguration</tt> 
 * method.
 * <br><b>Legal values</b>: <tt>1</tt> if the transition of the <tt>iWhichWire</tt> wire is the default
 * computed by <tt>this</tt> operator, <tt>-1</tt> for the opposite transition.
 */
  virtual void                      SetTransitionOrientation      (const CATLONG32             iSide                      ,
                                                                   const CATLONG32             iTransitionOrientation     ) = 0;

  /** 
 * @nodoc 
 */
  virtual void                      SetSkinSupport                (const CATLONG32             iSide                      ,
                                                                   const CATBody             * iSkin                      ) = 0;

  /** 
 * @nodoc 
 * Internal use.
 */
  virtual void                      SetDynamicMode                (const int                   iMode                      ) = 0;

  //
  //======================================================================
  //======================================================================
  //
  // Set the value of the mode "TangentToSides". The available values are :
  //   0 if the blext is - in the tangent plane to the shell (if any)
  //                     - perpendicular to the wires at their extremities,
    //                               /
    //                              /
    //                        _____/
    //            example :        \   blext
    //                              \
    //                        shell  \    /
    //                                \  /
    //                        _________\/
  //
  //   1 if the blext is colinear to the shell's sides limiting the wire. This
  //     has a meaning only in the case of a wire made of edges from the external
  //     loop of the shell, and with a non colinear link with the other edges of
  //     the loop
  //
  //                        ________
  //            example :        \   
  //                              \
  //                        shell  \   blext
  //                                \
  //                        _________\____
  //
  /**
 * @nodoc
 */
  virtual void                      SetTangentToSides             (const CATLONG32             iSide                      ,
                                                                   const CATLONG32             iValue                     ,
                                                                   const CATLONG32             iStartEnd                  = 0) = 0;

  /**
 * @nodoc
 */
  virtual void                      SetTangencyDirection          (const int                   iMode                      ) = 0;

  /**
 * @nodoc
 */
  virtual void                      SetToleranceForSurfaceCreation(      double                iTol                       ) = 0;

  //-----------------------------------------------------------------------------
  // Set and Get the Blend limits 
  //-----------------------------------------------------------------------------
  /** 
 * @nodoc 
 */
  virtual CATFrFCCvLimits        * GetLimits                      ()                                                        const = 0;

  /** 
 * @nodoc 
 */
  virtual void                     SetLimits                      (const CATFrFCCvLimits     * iCCvLimits                 )= 0;

  /** 
 * @nodoc 
 */
  virtual void                     SetOneLimit                    (const CATLONG32             iIndex                     ,
                                                                   const CATLONG32             iExtremity                 ,
                                                                   const CATFrFCCvParam      & iCCvParam                  ) = 0;

  /**
 * @nodoc
 * Defines the relimiting body.
 * @param iBody
 * The pointer to the relimiting body in case of extrapolation only.
 */
  virtual void                     SetUntilBody                   (const CATBody             * iBody                      ) = 0; 

  /**
 * Defines the mode of creation of the blend surface (<tt>ADVANCED mode</tt>).
 * @param iMode
 * The mode of the blend surface.
 * <br><b>Legal values</b>:
 * <dl><dt>0</dt><dd> Analytical mode: in case of simple geometrical wire 
 * (such as iso-parametric line on a surface  in G1 or G2 continuity or
 * Nurbs in case of G0 continuity), the control points of the wire are taken to build the blend surface.
 * In some cases depending on the input geometry, the surface cannot be created.
 * <dt>1</dt><dd> Geometrical mode: the blend surface is computed by tracing (or marching) the solution 
 * along the wire.
 * <dt>2</dt><dd> Automatic mode: automatically choose the more appropriate mode 
 * (default mode in <tt>BASIC</tt> use)
 * </dl>
 */
  virtual void                     SetMode                        (      CATLONG32             iMode                      ) = 0;

  /**
 * Returns the mode of creation of the blend surface.
 * @param iMode
 * The mode of the blend surface.
 * <br><b>Legal values</b>:
 * <dl><dt>0</dt><dd> Analytical mode: the control points of the wire are taken to build the blend surface.
 * In some cases depending on the input geometry, the surface canot be created.
 * <dt>1</dt><dd> Geometrical mode: the blend surface is computed by tracing (or marching) the solution 
 * along the wire.
 * </dl>
 */
  virtual CATLONG32                GetMode                        ()                                                        const = 0;

  /**
 * @nodoc
 */
  virtual CATLONG32                GetGeneralMode                 ()                                                        const = 0;

  /**
 * @nodoc
 */
  virtual CATLONG32                GetAutoMode                    ()                                                        const = 0;

  //-----------------------------------------------------------------------------
  // Set the Laws
  //-----------------------------------------------------------------------------
  /** 
 * @nodoc 
 * Sets the AngularLawPhi.
 * <br>To use in <tt>ADVANCED</tt> mode.
 */
  virtual void                     SetAngularLawPhi               (      CATLONG32             iIndex                     ,
                                                                   const CATLaw              * iAngularLawPhi             ) = 0 ;

  /** 
 * @nodoc
 * Sets the AngularLawTheta.
 * <br>To use in <tt>ADVANCED</tt> mode.
 */
  virtual void                     SetAngularLawTheta            (      CATLONG32               iIndex                    ,
                                                                  const CATLaw                * iAngularLawTheta          ) = 0 ;

  /** 
 * @nodoc
 * Set the RadiusLaw for.
 * <br>To use in <tt>ADVANCED</tt> mode. 
 */
  virtual void                     SetRadiusLaw                  (const CATLaw                * iRadiusLaw                ) = 0 ;

  /** 
 * @nodoc 
 * Sets the TensionLawDsDu.
 * <br>To use in <tt>ADVANCED</tt> mode.
 */
  virtual void                     SetTensionLawDsDu             (      CATLONG32               iIndex                    ,
                                                                  const CATLaw                * iTensionLawDsDu           ) = 0 ;

  /** 
 * @nodoc 
 * Sets the TensionLawD2sDu2.
 * <br>To use in <tt>ADVANCED</tt> mode.
 */
  virtual void                     SetTensionLawD2sDu2           (      CATLONG32               iIndex                    ,
                                                                  const CATLaw                * iTensionLawD2sDu2         ) = 0 ;

  //============================================================================
  //============================================================================
  //===========     ONLY FOR THE ADVANCED MODE       ===========================
  //============================================================================
  //============================================================================
  /**
 * @nodoc
 * Defines whether the computed topology must be linked to the inputs (<tt>ADVANCED mode</tt>).
 * @param iLevel
 * The option value.
 * <br><b>Legal values</b>: 
 * <dl><dt><tt>0</tt></dt><dd> if the computed topology is not linked to the input bodies. This
 * is the default value. 
 * <dt><tt>1</tt></dt><dd> if the computed topology is linked to the input bodies, and the smart
 * mechanism applies. 
 * </dl>
 */
  virtual void                     SetLinkedTopology             (const CATLONG32               iLevel                    ) = 0;

  /** 
 * @nodoc 
 * Returns whether the computed topology must be linked to the inputs.
 * @return 
 * The option value.
 * <br><b>Legal values</b>: 
 * <dl><dt><tt>0</tt></dt><dd> if the computed topology is not linked to the input bodies. This
 * is the default value. 
 * <dt><tt>1</tt></dt><dd> if the computed topology is linked to the input bodies, and the smart
 * mechanism applies. 
 * </dl>
 */
  virtual CATLONG32                GetLinkedTopology             ()                                                         const = 0;

  /**
 * @nodoc
 * Gets one coupling point.
 */
  virtual CATFrFCCvParam         * GetOneCouplingPoint           (const CATLONG32               iIndex                    ) const = 0;

  /**
 * @nodoc
 */
  virtual void                     GetOneCouplingPoint           (const CATLONG32               iIndex                    ,
                                                                        CATVertex             * oVertex                   ) const = 0;

  /** 
 * @nodoc 
 * Gets all the coupling points except the CCvLimits.
 */
  virtual CATFrFCCvParam        ** GetCouplingPoints             ()                                                         const = 0;

  /**
 * @nodoc
 */
  virtual void                     GetCouplingPoints             (      CATVertex            ** oVertices                 ) const = 0;

  /** 
 * @nodoc 
 * Removes all the coupling points  except the CCvLimits.
 */
  virtual void                     RemoveCouplingPoints          ()                                                               = 0 ;

  /** 
 * @nodoc 
 * Removes one coupling point.
 */
  virtual void                      RemoveOneCouplingPoint       (const CATLONG32               iIndex                    ) = 0;

  /** 
 * @nodoc 
 * Replaces a coupling point in the set of existing coupling points.
 */
  virtual void                      ReplaceCouplingPoint         (const CATLONG32               iIndex                   ,
                                                                  const CATFrFCCvParam        * iCCvParam                ) = 0;

  /**
 * @nodoc
 */
  virtual void                      ReplaceCouplingPoint         (const CATLONG32               iIndex                   ,
                                                                  const CATVertex             * iVertex                  ) = 0;

  /** 
 * @nodoc 
 * Gets the number of coupling points (without the ccv limits, considered as 
 * coupling points).
 */
  virtual CATLONG32                 GetNumberOfCouplingPoints    () const = 0;

  /**
 * Defines the level of twist detection (<tt>ADVANCED mode</tt>).
 * @param iLevel
 * The level.
 * <br><b>Legal values:</b>
 * <dl><dt>0</dt><dd>No twist detection.
 * <dt>1</dt><dd>A twist detection (this is a rough computation that may be too strict).
 * This is the default value.
 * </dl>
 */
  virtual void                      SetTwistTreatment            (      CATLONG32               iLevel                   ) = 0;

  /** 
 * @nodoc 
 */
  virtual void                      SetPreview                   (      CATLONG32               iPreview                 ) = 0;

  /**
 * Returns the level of the twist detection (<tt>ADVANCED mode</tt>).
 * @return
 * The level.
 * <br><b>Legal values:</b>
 * <dl><dt>0</dt><dd>No twist detection.
 * <dt>1</dt><dd>A twist detection (this is a rough computation that may be too strict).
 * This is the default value.
 *</dl>
 */
  virtual CATLONG32                 GetTwistTreatment            ()                                                        const = 0;

  /**
 * Returns the result of the twist detection.
 * @return
 * The diagnosis of the twist detection.
 * <br><b>Legal values</b>:
 * <dl><dt>1</dt><dd>The surface is not twisted and was computed.
 * <dt>0</dt><dd>The surface is twisted and the blend was not computed.
 * <dt>-1</dt><dd>No diagnosis (in case of </tt>twist detection level = 0</tt>).
 * </dl>
 */
  virtual CATLONG32                 GetValidity                  ()                                                        const =0;

  /** 
 * @nodoc 
 */
  virtual CATLONG32                 GetPreview                   ()                                                        const = 0;

  /**
 * @nodoc
 */
  virtual CATFrFSweepChecker      * GetChecker                   ()                                                        const = 0;

  /**
 * @nodoc
 * Possibility to create or not merged curves between the guides and Blend surface
 * Default is TRUE.
 */
  virtual void                      SetCreateMergedCurves        (const CATBoolean              iCreateMergedCurve       = TRUE) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopologicalBlend(); // -> delete can't be called
};

// New Create
// BLEND
//=========
/**
 * Creates a topological operator that computes a connecting surface between two wires.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.  <br>The journal is not yet implemented.
 * @param iWire1
 * The pointer to the first wire to connect.
 * @param iWire2
 * The pointer to the second wire to connect.
 * @param iSupport1
 * The pointer to the supporting surface of the first wire to connect, thus allowing you to define G1 and G2
 * continuity criteria.
 * @param iSupport2
 * The pointer to the supporting surface of the second wire to connect, thus allowing you to define G1 and G2
 * continuity criteria.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATIPGMTopologicalBlend
 */
/*
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalBlend *CATPGMCreateTopologicalBlend(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  const CATBody *iWire1,
  const CATBody *iWire2,
  const CATBody *iSupport1,
  const CATBody *iSupport2);
*/

//  EXTRAPOL
//==========
/**
 * Creates a topological operator that computes a extrapolation of the surface.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * <br>The journal is not yet implemented.
 * @param iWire
 * The pointer to the first wire to connect.
 * @param iSupport
 * The pointer to the supporting surface of the first wire to connect, thus allowing you to define G1 and G2
 * continuity criteria.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATIPGMTopologicalBlend
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalBlend *CATPGMCreateTopologicalBlend(
                                                      CATGeoFactory  * iFactory    ,
                                                      CATTopData     * iTopData    ,
                                                const CATBody        * iWire       ,
                                                const CATBody        * iSupport    );

#endif /* CATIPGMTopologicalBlend_h_ */
