#ifndef CATIPGMDynTrimSew_h_
#define CATIPGMDynTrimSew_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"
#include "CATDynTrimSewDef.h"
#include "CATTopDefine.h"
#include "CATCollec.h"

/**
* @level Protected
* @usage U1
*/

class CATBody;
class CATGeoFactory;
class CATPlane;
class CATShell;
class CATSurface;
class CATLISTP(CATVertex);
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynTrimSew;

/**
* @nodoc
* Class defining the operator to trim and sew a skin for replacing faces of a 3D body.
* The CATIPGMTopFaceReplaceSurface operator offers similar capabilities with more options. It is recommended
* to use CATIPGMTopFaceReplaceSurface instead of CATIPGMDynTrimSew.
* <ul>
* <li>A CATIPGMDynTrimSew operator is created with the <tt>CATPGMCreateDynTrimSew</tt> global function:
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>Options can be precised (such as the domain to draft) with the <tt>SetXxx</tt> and <tt>Add</tt> 
* methods, before
* asking for the computation with the <tt>Run</tt> method. The <tt>Add</tt> method can only be called once
* for a draft operation.
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMDynTrimSew: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynTrimSew();

  /**
   * @nodoc
   * Asks for the computation of the trimmed shell only. To be used for debug purpose.
   * @param iMode
   * CATDynTrimmedSkinShellPreview is the only mode.
   */
  virtual void SetPreviewMode(CATDynTrimSewPreviewMode iMode) = 0;

  /**
   * @nodoc
   * Defines the parameters of the sewing operation.
   * @param iListOfFacesCovered
   * The list of faces belonging to the solid body on which the
   * skin is stiched.
   * @param iTrimBody
   * The solid body on which the skin is stiched.
   * @param iTrimShell
   * The shell underlying the solid body.
   * @param iSkinBody
   * The skin to be stiched onto the solid body.
   * @param iSkinShell
   * The shell underlying the skin body and corresponding to the part to be stiched.
   * @param iSkinOrient
   * The orientation of the skin with respect to the solid shell.
   */
  virtual void Add(
    CATLISTP(CATFace) &iListOfFacesCovered,
    CATBody *iTrimBody,
    CATShell *iTrimShell,
    CATBody *iSkinBody,
    CATShell *iSkinShell,
    CATOrientation iSkinOrient) = 0;

  /**
   * @nodoc
   * Defines the initialization mode. Specifying this mode is a way 
   * to optimize the algorithm behavior. There is a default mode (CATDynTrimSewLaydownAndInterInitMode), this
   * is the one which is activated if you do not call this API. With no indication, the algorithm 
   * performs a "laydown" and then an intersection which may not be necessary. Unless you have no
   * indication on the way the two input bodies intersects.
   * @param iMode
   * <ul>
   * <li>CATDynTrimSewLaydownInitMode: to be used if some edges of the skin are "laid down" on the solid.
   * If a PCurve of the skin to be sewn relies on the solid, you must use 
   * the OnlyUseExistingGeometryForLayDown API in addition to the SetInitMode(CATDynTrimSewLaydownInitMode) 
   * method.
   * <li>CATDynTrimSewIntersectionInitMode: to be used when the covering faces intersect the faces to be covered 
   * and when you are sure that you will never have to "lay down" an edge onto the solid body. 
   * </ul>
   */
  virtual void SetInitMode(CATDynTrimInitMode iMode) = 0;

  /**
   * @nodoc
   * Defines the Align mode.
   * @param iAlign
   * Asks for an extrapolation when there is no intersection between the 
   * skin to be sewn and the solid.
   */
  virtual void SetAlignMode(CATBoolean iAlign) = 0;

  /**
   * @nodoc
   * Set one (or more) list of edges already laid on the skin.
   * This list will initialize the relimitation.
   */
  virtual void SetListOfAlreadyLaidOnEdges(
    int iNumberOfList,
    CATLISTP(CATEdge) *iListOfEdges,
    CATListOfInt *iSideSkinOnListOfEdge) = 0;

  /**
   * @nodoc
   * Mode without simplification if iNoSimplif = TRUE
   */
  virtual void SetNoSimplif(CATBoolean iNoSimplif) = 0;

  /**
   * @nodoc
   * Mode without keep feature mode  if iNoKeepFeature = TRUE
   */
  virtual void SetNoKeepFeature(CATBoolean iNoKeepFeature) = 0;

  /**
   * @nodoc
   * If the CATDynTrimSewLaydownInitMode option is specified in the SetInitMode method,
   * calling OnlyUseExistingGeometryForLayDown is a means to specify the use
   * of a pre-existing geometry on the solid to be sewn (the skin edge which is on the solid must have a PCurve
   * relying on the solid surface).
   * @param iUseExistingGeometryForLayDown
   * Specifies the use of a pre-existing geometry if  iUseExistingGeometryForLayDown=TRUE.
   */
  virtual void OnlyUseExistingGeometryForLayDown(
    CATBoolean iUseExistingGeometryForLayDown) = 0;

  /**
   * @nodoc
   * DO NOT USE. ONLY FOR CATIA LIVE SHAPE<br>
   * Set the correspondance between the replacing faces and the faces to replace.
   * The lists are synchroneous (there must be a bijection between the faces).
   * @param iToReplaceFaces
   * List of faces to be replaced.
   * @param iReplacingFaces
   * List of replacing faces.
   */
  virtual void SetReplacingFacesBijection(
    CATLISTP(CATFace) &iToReplaceFaces,
    CATLISTP(CATFace) &iReplacingFaces) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynTrimSew(); // -> delete can't be called
};

/**
* @nodoc
* Creates a CATIPGMDynTrimSew operator.
* @param iFactory
* The factory of the geometry. 
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iPart
* The pointer to the solid body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDynTrimSew *CATPGMCreateDynTrimSew(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart);

#endif /* CATIPGMDynTrimSew_h_ */
