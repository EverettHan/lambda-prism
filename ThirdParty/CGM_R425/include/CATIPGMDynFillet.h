#ifndef CATIPGMDynFillet_h_
#define CATIPGMDynFillet_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"
#include "CATCollec.h"
#include "CATTopDefine.h"

/**
* @level Protected
* @usage U1
*/ 

class CATBody;
class CATCGMJournalList;
class CATDomain;
class CATDynBlendVertexDiag;
class CATDynEdgeFilletRibbon;
class CATDynFaceFaceFilletRibbon;
class CATDynFilletContextForFastRun;
class CATDynRemoveFaceFilletRibbon;
class CATExtCGMReplay;
class CATExtTopOperator;
class CATMathPoint;
class CATTopData;
class CATLISTP(CATDynFilletBlendVertex);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynFillet;

/**
* Class defining the operator to fillet edges or faces of a 3D body or a skin body.
* <br>Several filleting operations (called ribbons) can be defined in the same operator. A ribbon
* is either defined between two faces (<tt>CATDynFaceFaceFilletRibbon</tt>), or along an edge
* (<tt>CATDynEdgeFilletRibbon</tt>), or between three faces (<tt>CATDynRemoveFaceFilletRibbon</tt>)
* without specifying the radius (tri-tangent fillet).
* By default, a ribbon is automatically propagated by following the tangential
* continuity of its support, but this propagation can be switched off.
* <br>
* A fillet is roughly generated by rolling a ball tangently to the two faces adjacent to the edge to be filleted.
* By doing this, the fillet creation is disrupted if the ball reaches the limits of the adjacent faces prior to 
* reaching the edge extremity. This happens especially when the shape around the edge to be filleted shows 
* accute angles. The fillet surface is then extrapolated in order to complete the fillet operation 
* up to the edge extremity. This extrapolation defines the maximum limits of the surface underlying the
* fillet. Updating a fillet can possibly modify these maximum limits. But undoing an operation in CATIA does not modify
* the previous computed maximum limits. 
* <br>
	* The <tt>CATIPGMDynFillet</tt> operator follows the global frame of the topological operators and satisfies the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
	* <li>A <tt>CATIPGMDynFillet</tt> operator is created with the <tt>CATPGMCreateDynFillet</tt> global function:
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
* <li>Options must be precised (such as the faces or edges to fillet) with the appropriate methods, before
* asking for the computation with the <tt>Run</tt> method. 
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
* </ul>
* @see CATDynFilletRibbon, CATDynFilletRadius
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMDynFillet: public CATIPGMDynOperator
{
public:
  /**
  * Constructor
  */
  CATIPGMDynFillet();

  /**
  * Appends a ribbon between two faces.
  * <br>The face-face ribbon can be only used in a single ribbon filleting operation.
  * @param iRibbonToAppend
  * The pointer to the ribbon to add to <tt>this</tt> operator.
  */
  virtual void Append(CATDynFaceFaceFilletRibbon *iRibbonToAppend) = 0;

  /**
  * Appends a ribbon along an edge.
  * @param iRibbonToAppend
  * The pointer to the ribbon to add to <tt>this</tt> operator.
  */
  virtual void Append(CATDynEdgeFilletRibbon *iRibbonToAppend) = 0;

  /**
  * Appends a tri-tangent ribbon.
  * <br>The tri-tangent ribbon can be only used in a single ribbon filleting operation.
  * @param iRibbonToRemove
  * The pointer to the ribbon to add to <tt>this</tt> operator.
  */
  virtual void Append(CATDynRemoveFaceFilletRibbon *iRibbonToRemove) = 0;

  /**
  * Asks for the computation of the construction paths of the fillet, even though the filleting operation
  * cannot be completely run.
  * <br>To use in debug purpose, in order to understand the configuration.
  */
  virtual void SetPrevisualizationOnly() = 0;

  /**
  * @nodoc
  * Defines the shape of a round corner. When edges blend together,
  * the resulting shape of the corner may not suit the user needs.
  * The corner can be reshaped by specifying a transition distance
  * from the edge to the vertex to be rounded. This is the setback distance.
  * <br>
  * The main steps to create a blend corner are:
  * <ol>
  * <li>Create a CATDynFilletBlendVertexSpec for each edge bounding the corner. 
  * A CATDynFilletBlendVertexSpec defines the setback distance along with the orientation
  * of the edge with respect to the vertex
  * <li>Create for each edge a CATDynEdgeFilletRibbon and specify the CATDynC1SingleFaceFilling option
  * in the SetReconfigFillFunction method
  * <li>Create for each edge a CATDynFilletBlendVertex. You must use the CATDynFilletBlendVertex::PocOnly 
  * <li>Add the list of CATDynFilletBlendVertex to the CATIPGMDynFillet.
  * </ol>
  * @param iVertexBlendList
  * The list of CATDynFilletBlendVertex to be added to the created fillet.
  */
  virtual void SetVertexBlendList(
    CATLISTP(CATDynFilletBlendVertex) &iVertexBlendList) = 0;

  /**
  * @nodoc
  */
  virtual CATDynBlendVertexDiag *CreateVertexBlendDiag(int iVertexBlendIndex) = 0;

  /**
  * Defines a face or plane to stop the fillet. 
  * @param iBody
  * The body which contains the shell used as a limiting element.
  * @param iSkin
  * The shell to be used as a limiting element.
  * @param iOrientation
  * The orientation of the edge with respect to the limiting element.
  * @param iSmartCrossParting
  * The parting option:
  * <ul>
  * <li> 0: no parting
  * <li> 1: parting is activated
  * </ul>
  */
#ifdef CATIACGMV5R23
  virtual void AddLimitingElement(
    CATBody *iBody,
    CATDomain *iSkin,
    const CATOrientation iOrientation) = 0;

  /** @nodoc */
  virtual void AddLimitingElement(
    CATBody *iBody,
    CATDomain *iSkin,
    const CATOrientation iOrientation,
    const int iSmartCrossParting) = 0;
#else

  virtual void AddLimitingElement(
    CATBody *iBody,
    CATDomain *iSkin,
    const CATOrientation iOrientation,
    const int iSmartCrossParting = 0) = 0;
#endif

  /**
  * Defines the type of computation in case of multi ribbons configurations.
  * By default, the <tt>Run</tt> method compute all the ribbons and then intersect them
  * together. Moreover, if this computation failed, another computation is launched, taken one ribbon 
  * after the other.
  * If called, this method only allows the <tt>Run</tt> method to execute the first step.
  */
  virtual void SetTrueMultiRibbonOnly() = 0;

  /**
  * @nodoc
  * DO NOT USE.
  */
  virtual void GetSplittingElements(
    int iSupport,
    CATLISTP(CATGeometry) &oElementsList,
    CATListOfInt &oSides) = 0;

  /**
  * When several ribbons are possible in a FaceFace Fillet, 
  * allows you to choose a help point to specify the edge where the ribbon must be computed.
  * @param iHelpPoint
  * The point to specify the edge where the ribbon must be computed.
  */
  virtual void SetHelpPoint(CATMathPoint &iHelpPoint) = 0;

  /**
   * @nodoc
   * @return [out, CATBaseUnknown#Release]
  */
  virtual CATContextForFastRun *GetContextForFastRun(CATBoolean iGetOnly = FALSE) = 0;

  /**
   * @nodoc
   * @return [out, CATBaseUnknown#Release]
  */
  virtual CATDynFilletContextForFastRun *GetDynFilletContextForFastRun(
    CATBoolean iGetOnly = FALSE) = 0;

protected:
  /**
  * Destructor
  */
  virtual ~CATIPGMDynFillet(); // -> delete can't be called
};

/**
* Creates a CATIPGMDynFillet operator.
* @param iContainer
* The factory of the geometry.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.  
* @param iPart
* The pointer to the body to fillet. 
* When set to <tt>NULL</tt>, the different ribbons can be defined on several bodies.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDynFillet *CATPGMCreateDynFillet(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart = NULL);

#endif /* CATIPGMDynFillet_h_ */
