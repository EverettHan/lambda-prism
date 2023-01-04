#ifndef CATIPGMTopTangentCurveOperator_h_
#define CATIPGMTopTangentCurveOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopMultiResult.h"
#include "CATTopDefine.h"

class CATTopTangentCurveData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopTangentCurveOperator;

/**
 * Class of the topological operators that create the bodies tangent to other bodies. 
 * This class is the base class for some supplied operators, but you must not derive it yourself.
 *<br>
 * This operator follows the general scheme of the topological operators producing several resulting bodies:
 * <ul>
 *<li> Create the operator with the appropriate global function 
 *<li> Set the parameters
 *<li> Run
 *<li> Get the resulting bodies (use the iterator on the resulting bodies, because
 * several line bodies can result from the computation)
 *<li> Release the operator with the <tt>Release</tt> method.
 *</ul>
 * @see CATIPGMTopMultiResult
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopTangentCurveOperator: public CATIPGMTopMultiResult
{
public:
  /**
   * Constructor
   */
  CATIPGMTopTangentCurveOperator();

  /**
   * Defines the tangent orientation of the resulting line bodies to output.
   * <br>To call before the <tt>Run</tt> method.
   * @param iTangentOrientation
   * The tangent orientation with regards to the <tt>iRankWire</tt>-th input body.
   * <br><b>Legal values</b>: 
   * <dl><dt><tt>0</tt></dt><dd>All the resulting line bodies are output
   *     <dt><tt>1</tt></dt><dd>Are kept the resulting line bodies whose orientation is the same as  
   *                            the orientation of the <tt>iRankWire</tt>-th input body
   *     <dt><tt>-1</tt></dt><dd>Are kept the resulting line bodies whose orientation is opposite to 
   *                            the orientation of the <tt>iRankWire</tt>-th input body
   * </dl>
   * @param iRankWire
   * The rank of the input body to consider. 
   * <br>Legal values</b>: <tt>iRankWire=1</tt> in case of <tt>CATIPGMTopLineTangentPtCrvOperator</tt>,
   * <tt>1 <= iRankWire <= 2</tt> in case of <tt>CATIPGMTopLineTangentCrvCrvOperator</tt>.
   */
  virtual void SetTangentOrientation(int iTangentOrientation, int iRankWire = 1) = 0;

  /**
   * Defines the curvature orientation of the resulting line bodies to output.
   * <br>To call before the <tt>Run</tt> method.
   * @param iTangentOrientation
   * The curvature orientation with regards to the <tt>iRankWire</tt>-th input body.
   * <br><b>Legal values</b>: 
   * <dl><dt><tt>0</tt></dt><dd>All the resulting line bodies are output
   *     <dt><tt>1</tt></dt><dd>Are kept the resulting line bodies that are on the side of the
   *                            vector product of the normal to the shell and the tangent to the resulting line body
   *     <dt><tt>-1</tt></dt><dd>Are kept the resulting line bodies that are on the opposite side of the
   *                            vector product of the normal to the shell and the tangent to the resulting line body
   * </dl>
   * @param iRankWire
   * The rank of the input body to consider. 
   * <br>Legal values</b>: <tt>iRankWire=1</tt> in case of <tt>CATIPGMTopLineTangentPtCrvOperator</tt>,
   * <tt>1 <= iRankWire <= 2</tt> in case of <tt>CATIPGMTopLineTangentCrvCrvOperator</tt>.
   */
  virtual void SetCurvatureOrientation(int iCurvatureOrientation, int iIWire = 1) = 0;

  /**
   * Defines the orientation of the current resulting line body.
   * <br>To call after the <tt>Run</tt> method, 
   * during the iterative step of the result recovery, see @href CATIPGMTopMultiResult .
   * @param ioTangentOrient
   * The tangent orientation with regards to the <tt>iRankWire</tt>-th input body.
   * <br><b>Legal values</b>: 
   * <dl><dt><tt>0</tt></dt><dd>All the resulting line bodies are output
   *     <dt><tt>1</tt></dt><dd>Are kept the resulting line bodies whose orientation is the same as  
   *                            the orientation of the <tt>iRankWire</tt>-th input body
   *     <dt><tt>-1</tt></dt><dd>Are kept the resulting line bodies whose orientation is opposite to 
   *                            the orientation of the <tt>iRankWire</tt>-th input body
   * </dl>
   * @param ioCurvatureOrient
   * The curvature orientation with regards to the <tt>iRankWire</tt>-th input body.
   * <br><b>Legal values</b>: 
   * <dl><dt><tt>0</tt></dt><dd>All the resulting line bodies are output
   *     <dt><tt>1</tt></dt><dd>Are kept the resulting line bodies that are on the side of the
   *                            vector product of the normal to the shell and the tangent to the resulting line body
   *     <dt><tt>-1</tt></dt><dd>Are kept the resulting line bodies that are on the opposite side of the
   *                            vector product of the normal to the shell and the tangent to the resulting line body
   * </dl>
   * @param ioIdem
   * The test of whether the current resulting line body can be distinguished from another one.
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt></dt><dd>If the current resulting line body can be distinguished in terms of orientations from
   * the other resulting line bodies
   *     <dt><tt>2</tt></dt><dd>If the current resulting line body has the same orientations than another resulting line body
   *                            and its length is equal (at the factory resolution) 
   *                            to the length of at least one of them.
   * </dl>
   * @param iRankWire
   * The rank of the input body to consider. 
   * <br>Legal values</b>: <tt>iRankWire=1</tt> in case of <tt>CATIPGMTopLineTangentPtCrvOperator</tt>,
   * <tt>1 <= iRankWire <= 2</tt> in case of <tt>CATIPGMTopLineTangentCrvCrvOperator</tt>.
   */
  virtual void GetOrientationOnWire(
    int &ioTangentOrient,
    int &ioCurvatureOrient,
    int &ioIdem,
    int iRankWire = 1) = 0;

  /**
   * Defines an index to distinguish the current resulting line body.
   * <br>To call after the <tt>Run</tt> method, 
   * during the iterative step of the result recovery, see @href CATIPGMTopMultiResult .
   * <br>Several resulting tangent line bodies produced by the operator can be same oriented
   * regarding to the input wire bodies. In such a case, they are sorted by length in order to
   * distinguish them.
   * @param ioIndex
   * The index value in the list of same oriented (in tangent and curvature) resulting line bodies.
   */
  virtual void GetDiscriminationIndex(int &ioIndex) = 0;

  /**
   * Returns the tangent orientation of the current resulting line body.
   * @return 
   * The tangent orientation with regards to the <tt>iRankWire</tt>-th input body.
   * <br><b>Legal values</b>: 
   * <dl>
   *     <dt><tt>1</tt></dt><dd>The resulting line body has the same orientation as  
   *                            the <tt>iRankWire</tt>-th input body
   *     <dt><tt>-1</tt></dt><dd>The resulting line body has the opposite orientation to 
   *                            the <tt>iRankWire</tt>-th input body
   * </dl>
   */
  virtual int GetTangentOrientation(int iRankWire = 1) const = 0;

  /**
   * Returns the curvature orientation of the resulting line bodie.
   * @return 
   * The curvature orientation with regards to the <tt>iRankWire</tt>-th input body.
   * <br><b>Legal values</b>: 
   * <dl>
   *     <dt><tt>1</tt></dt><dd>The resulting line body is on the side of the
   *                            vector product of the normal to the shell and the tangent to the itself
   *     <dt><tt>-1</tt></dt><dd>The resulting line body is on the opposite side of the
   *                            vector product of the normal to the shell and the tangent to the itself
   * </dl>
   */
  virtual int GetCurvatureOrientation(int iRankWire = 1) const = 0;

  /**
  * Creates the nearest line from conditions.
  * @param iCrvOr
  * The array of two curvature orientations for first and second input body.
  * Acceptables values: 0,-1,1. Use 0 if you don't want to use this condition.
  * @param iTngOr
  * The array of two tangent orientations between the line result and the first and second input body.
  * Acceptables values: 0,-1,1. Use 0 if you don't want to use this condition.
  * @iIndex 
  * iIndex = -1,0,1,2,... : The discrimination Index of the wanted solution, Use -1 if you don't want to use this condition.
  * @param oUseOrientationCondition
  * Return TRUE if the line solution use the orientation condition.
  * @param oUseIndexCondition
  * Return TRUE if the line solution use the index condition.
  * @param CurJourn
  * The pointer to the journal corresponding to the creation of the current line.
  * If <tt>NULL</tt>, the journal is not written.
  * @return
  * The pointer to the created body, or NULL if we cannot find it. If you do not want to keep it,
  * use the @CATICGMContainer#Remove method to remove it from the geometric factory, after the deletion
  * of <tt>this</tt> operator.
  * Put the iterator of the resulting lines on the solution.
  */
  virtual CATBody *GetResultWithConditions(
    CATOrientation *iCrvOr,
    CATOrientation *iTngOr,
    int iIndex,
    CATBoolean &oUseOrientationCondition,
    CATBoolean &oUseIndexCondition,
    CATCGMJournalList *CurJourn = NULL) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopTangentCurveOperator(); // -> delete can't be called
};

#endif /* CATIPGMTopTangentCurveOperator_h_ */
