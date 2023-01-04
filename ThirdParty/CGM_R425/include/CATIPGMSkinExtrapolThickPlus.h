#ifndef CATIPGMSkinExtrapolThickPlus_h_
#define CATIPGMSkinExtrapolThickPlus_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATMathDef.h"

class CATBody;
class CATCGMJournalInfo;
class CATCGMJournalList;
class CATCGMOutput;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATRegul;
class CATIPGMThick;
class CATTopData;
class CATLISTP(CATEdge);
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSkinExtrapolThickPlus;

class ExportedByCATGMOperatorsInterfaces CATIPGMSkinExtrapolThickPlus: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSkinExtrapolThickPlus();

  /**
  * Sets the ability to later modify the resulting body.
  * @param iFreezeMode
  * The freeze mode.
  */
  virtual void SetFreezeMode(CATBodyFreezeMode iFreezeMode) = 0;

  /**
  * Appends a list of edges to extrapolate.
  * It replaces the current value of an already selected edges by <tt>iExtrapolValue</tt>.
  * @param iBoundaryEdges
  * The list of edges to append.
  * @param iExtrapolValue
  * The common extrapolation value for all the edges of the <tt>iBoundaryEdges</tt> list.
  */
  virtual void Append(CATLISTP(CATEdge) &iBoundaryEdges, CATLength iExtrapolValue) = 0;

  /**
  * Appends an edge to extrapolate.
  * It replaces the current value of an already selected edges by <tt>iExtrapolValue</tt>.
  * @param iBoundaryEdge
  * The edge to append.
  * @param iExtrapolValue
  * The extrapolation value for the <tt>iBoundaryEdge</tt> edge.
  */
  virtual void Append(CATEdge *iBoundaryEdge, CATLength iExtrapolValue) = 0;

  /**
  * Selects all the edges of the shell boundary and sets to them a common extrapolation value.
  * @param iExtrapolValue
  * The new current extrapolation value of the already selected edges.
  */
  virtual void SetDefaultExtrapolationValue(CATLength iExtrapolValue) = 0;

  /**
  * Defines the propagation mode of the extrapolation value.
  * @param iPropagationMode
  *<dl>
  *<dt><tt>0</tt></dt><dd> No propagation of the extrapolation value.
  *<dt><tt>1</tt></dt><dd> Defines the automatic definition of the extrapolation value on an edge
  * to the one of its tangential adjacent edges.
  * This mode is used by default at the creation of the operator.
  *</dl>
  */
  virtual void SetPropagationMode(short iPropagationMode) = 0;

  /**
  * @nodoc
  * Defines the relimitation mode from all boundary extremities in SkinExtrapolation operator.
  * @param iExtremitiesMode
  *<dl>
  *<dt><tt>0</tt></dt><dd> Extrapolate adjacent edges to cut the offset boundary.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> Add junction edges in normal direction of boundary extremities
  *</dl>
  */
  virtual void SetExtremitiesMode(short iExtremitiesMode) = 0;

  /**
  * @nodoc
  * Keep geometry of edges to relimit
  * (not compatible with Normal mode or propagation OFF)
  */
  virtual void SetKeepBorderEdgeCurves() = 0;

  /**
  * @nodoc
  * To obtain a partial result when all edges cannot be extrapolated.
  * Edges that couldn't be extrapolated can be retrieved with GetTrickyEdges method.
  * @param iPartialExtrapolationAllowed
  *<dl>
  *<dt><tt>0</tt></dt><dd> No partial extrapolation.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> Partial Extrapolation allowed.
  *</dl>
  */
  virtual void SetPartialExtrapolationAllowed(short iPartialExtrapolationAllowed) = 0;

  /**
  * @nodoc
  * Defines the level of approximation allowed for the boundary of the result skin (robustness mode).
  * @param iApproximateExtrapolationLevel
  *<dl>
  *<dt><tt>0</tt></dt><dd> No Approximation.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> Approximation allowed (level 1).
  *</dl>
  */
  virtual void SetApproximateExtrapolationLevel(short iApproximateExtrapolationLevel) = 0;

  /**
  * @nodoc
  * Defines whether the result should contain the whole extrapolated surface or only the extrapolated area.
  * @param iKeepOnlyExtrapolatedArea
  *<dl>
  *<dt><tt>0</tt></dt><dd> The whole extrapolated surface is returned.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> The result contains the extrapolated area only.
  *</dl>
  */
  virtual void SetKeepOnlyExtrapolatedArea(short iKeepOnlyExtrapolatedArea) = 0;

  /**
  * @nodoc
  * Enables or disables twist detection.
  * @param iTwistDetection
  *<dl>
  *<dt><tt>0</tt></dt><dd> Twist detection is disabled : result skin may lie on twisted surfaces.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> Twist detection is enabled : extrapolation is not possible if a twist is detected.
  *</dl>
  */
  virtual void SetTwistDetection(short iTwistDetection) = 0;

  /**
  * @nodoc
  * Enables or disables deviation checking.
  * @param iWithDeviation
  * <dl>
  * <dt><tt>1</tt><dd> Check if surface deviations are below maximum value.
  * This value can be provided by the user through <tt>SetDeviationAllowed</tt> method.
  * Default value is the factory resolution
  * <dt><tt>0</tt><dd> No deviation checking is performed
  * This mode is used by default at the creation of the operator.
  * </dl>
  **/
  virtual void SetDeviationMode(short iDeviationMode) = 0;

  /**
  * @nodoc
  * Defines the maximum deviation value allowed by the user.
  * @param iDeviation
  * The value of the deviation. This value must be positive.
  */
  virtual void SetDeviationAllowed(CATLength iMaxDeviation) = 0;

  /**
  * @nodoc
  * Set Implicit Geometric Factory for CGMReplay
  */
  virtual void SetCGMMode(short iCGMMode) = 0;

  /**
  * @nodoc
  * Get list of faces for which Matter side has been reversed.
  * @param oReverseMatterOutputFaces
  *   The list of Reversed Faces.
  */
  virtual void GetReverseMatterOutputFaces(CATLISTP(CATFace) &oReverseMatterOutputFaces) = 0;

  /**
  * Returns the pointer to the resulting body.
  */
  virtual CATBody *GetResult() = 0;

  /**
  * Runs <tt>this</tt> operator.
  */
  virtual int Run() = 0;

  /**
  * @nodoc
  * Get list of faces that couldn't be extrapolated.
  * @param oTrickyFaces
  *   The list of Tricky Faces.
  */
  virtual void GetTrickyFaces(CATLISTP(CATFace) &oTrickyFaces) = 0;

  /**
  * @nodoc
  * Get list of edges that couldn't be extrapolated.
  * @param oTrickyEdges
  *   The list of Tricky Edges.
  */
  virtual void GetTrickyEdges(CATLISTP(CATEdge) &oTrickyEdges) = 0;

  /**
  * @nodoc
  * Get list of edges that couldn't be extrapolated.
  * @param iThick
  *   The CATIPGMThick operator.
  * @param oTrickyEdges
  *   The list of Tricky Edges.
  */
  virtual void GetLocalTrickyEdges(
    CATIPGMThick *iThick,
    CATLISTP(CATEdge) &oTrickyEdges,
    short iUpdateLists = 0) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSkinExtrapolThickPlus(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSkinExtrapolThickPlus *CATPGMCreateSkinExtrapolThickPlus(
  CATBody *iSkin,
  CATTopData *iTopData);

#endif /* CATIPGMSkinExtrapolThickPlus_h_ */
