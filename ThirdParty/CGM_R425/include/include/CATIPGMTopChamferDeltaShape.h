#ifndef CATIPGMTopChamferDeltaShape_h_
#define CATIPGMTopChamferDeltaShape_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDynChamferRibbon.h"

class CATFace;
class CATLISTP_CATEdge_;
class CATLISTP_CATFace_;
class CATLISTP(CATEdge);
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopChamferDeltaShape;

/** 
 * Class representing the operator that creates a body which is an added material by Chamfer creation
 * on given edge(s) of single or two joining bodies
 * <br>To use the CATIPGMTopChamferDeltaShape :
 * <ul><li>Create the <tt>CATCreateChamferDeltaShape</tt> global function. 
 * <li> <tt>Run</tt> the operator
 * <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
 * <li>Delete with the usual C++ <tt>delete</tt> operator after use.</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopChamferDeltaShape: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopChamferDeltaShape();

  /**
  * @nodoc
  * Defines a face or connected faces to stop the chamfer. 
  * @param iBody
  * The body which contains the shell used as a limiting element.
  * @param iSkin
  * The shell to be used as a limiting element.
  * @param iOrientation
  * The orientation of the edge with respect to the limiting element.
  */
  virtual void AddLimitingElement(
    CATBody *iBody,
    CATDomain *iSkin,
    const CATOrientation iOrientation) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopChamferDeltaShape(); // -> delete can't be called
};

/** 
 * Creates an operator to build a delta (added material) body
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside the
 * configuration is <tt>NULL</tt>, it is not filled. 
 * @param iBody1
 * The pointer to the body containing edge to chamfer 
 * @param iListOfEdgesToChamfer
 * The list of edges to be chamfered
 * @param iListOfReferenceFaces
 * The list of reference faces. Reference Face defines the side at which Length1 is to be taken for an edge.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopChamferDeltaShape *CATPGMCreateTopChamferDeltaShape(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iFirstBody,
  CATLISTP(CATEdge) *iListOfEdgesToChamfer,
  CATLISTP(CATFace) *iListOfReferenceFaces,
  CATDynTypeChamfer iChamferType,
  double iLengthOfLeg1,
  double iLengthOfLeg2);

#endif /* CATIPGMTopChamferDeltaShape_h_ */
