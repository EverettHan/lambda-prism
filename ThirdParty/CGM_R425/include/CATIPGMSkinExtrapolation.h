#ifndef CATIPGMSkinExtrapolation_h_
#define CATIPGMSkinExtrapolation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATLISTP(CATVertex);
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSkinExtrapolation;

/**  
* Class defining the topological operator that extrapolates a 
* surface in tangency. 
* The parameters to be specified are:
* <ul>
* <li>an extrapolation length. 
* <li>the type of extrapolation: the faces that are created to extend the surface body
*   are added smoothly. See diagram below:
* </ul>
* <pre>
*
*                             |--------|              /--\
*                             |        |             /    \
*                             |        |            /      \
*       /--------\            /--------\           /--------\
*      /          \          /          \         /          \
*     /            \        /            \       /            \
*        . . . .               . . . .               . . . .
*
*        body to               normal mode         tangent mode
*       extrapolate
*
*</pre> 
* <ul>
* <li>A CATIPGMSkinExtrapolation operator is created with the
* <tt>CATPGMCreateSkinExtrapolation</tt> global method.
* It must be directly released with the <tt>Release</tt> method after use. It is is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. 
* <li>The resulting body is retrieved with the <tt>GetResult</tt> method.
*</ul> 
*/


class ExportedByCATGMOperatorsInterfaces CATIPGMSkinExtrapolation: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSkinExtrapolation();

  /**
* @nodoc
* Defines the continuity criteria: 1 for G1, 2 for G2.
* Not to be used.
*/
  virtual void SetContinuity(int mode = 1) = 0;

  /**
* Specifies the type of extrapolation.
* @param mode
*<dl>  
*<dt><tt>1</tt></dt><dd>  The extrapolation is Tangent to extremities.   
*<dt><tt>2</tt></dt><dd>  The extrapolation is Normal to extremities.
*   This mode is the default mode.
*</dl>  
*/
  virtual void SetBorderMode(int mode = 1) = 0;

  /**
* @nodoc
* Specifies the extrapolation length.
* Use SetLength method.
*/
  virtual void SetOffset(double ) = 0;

  /**
* Specifies the extrapolation length.
*/
  virtual void SetLength(double ) = 0;

  /**
* @nodoc
* Specifies a body to extrapolate up to.
* @param Body
*    The body to extrapolate up to.   
* @param iSplitMode
*<dl>  
*<dt><tt>0</tt></dt><dd>  No split.   
*<dt><tt>1</tt></dt><dd>  Result will be splitted by iUntilBody.
*   This mode is the default mode.
*</dl>  
*/
  virtual void SetUntilBody(CATBody * iBody      ,
                            int       iSplitMode = 1
                            ) = 0;

  /**
* @nodoc
* 0 = NO, otherwise = YES.
* In active mode, checks that the wire is on the boundary of the skin.
* Not to be used : check is automatically done.
*/
  virtual void SetCheckIfWireIsOnShellBoundary(int mode) = 0;

  /**
* @nodoc
*/
  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration *iConfig) = 0;

  /**
* @nodoc
*/
  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  /**
* @nodoc
* Specifies one or several internal edges in order to determine a direction for the extrapolation.
* The edges will be extrapolated in tangency. It is possible to associate a vertex to each edge
* to give an orientation to extrapolation.
* @param iEdgesForDirection
*   The Edges to determine direction for extrapolation.
* @param iVertexOfEdges
*   The Vertex associated to each Edge for orientation. 
*/
  virtual void SetDirectionnalEdge(
    const CATLISTP(CATEdge) &iEdgesForDirection,
    const CATLISTP(CATVertex) &iVertexOfEdges) = 0;

  /**
* @nodoc
*/
  virtual void SetJournalMode(CATLONG32 iJournalMode) = 0;

  /**
 * @nodoc
 * Enables or disables twist detection. 
 * @param  iTwistDetection  
 *<dl>  
 *<dt><tt>0</tt></dt><dd>  No  twist detection : twist is authorized.  
 *<dt><tt>1</tt></dt><dd>  twist detection : twist is not authorized.  
 *   This is default mode : extrapolation is not possible if a twist is detected.
 *</dl>  
 */
  virtual void SetTwistDetection(int iTwistDetection) = 0;

  /**
* Retrieves the resulting body.
*/
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSkinExtrapolation(); // -> delete can't be called
};

/**
 * Creates a CATIPGMSkinExtrapolation operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data of the operation.
 * @param iSkin
 * The pointer to surface to be extrapolated.
 * @param iWireOnSkin
 * The pointer to the wire from which the skin is to be extrapolated.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSkinExtrapolation *CATPGMCreateSkinExtrapolation(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iSkin,
  CATBody *iWireOnSkin);

#endif /* CATIPGMSkinExtrapolation_h_ */
