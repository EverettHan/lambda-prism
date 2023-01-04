#ifndef CATICGM2DBoxComputation_h_
#define CATICGM2DBoxComputation_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATEdge;
class CATFace;
class CATGeoFactory;
class CATSurLimits;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGM2DBoxComputation;

/**
 * Class defining a topological operator that computes a uv bounding box for a <tt>CATFace</tt> or a <tt>CATEdge</tt> on a support face.
 * <ul>
 *     <li> A <tt>CATICGM2DBoxComputation</tt> operator is created with the <tt>CATCreate2DBoxComputationOper</tt> global functions
 *     <li> It is the user's responsibility to release the operator after it has been used.
 *     <li> In both cases, the result is returned by the <tt>Get2DBox</tt> method.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGM2DBoxComputation: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGM2DBoxComputation();

  /**
  * Returns the computed uv bounding box.
  * @return
  * oBoundingBox : The uv bounding box.
  */
  virtual void Get2DBox(CATSurLimits &oBoundingBox) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGM2DBoxComputation(); // -> delete can't be called
};

/**
 * Creates the operator that computes a uv bounding box for a <tt>CATFace</tt>.
 * @param ipFactory
 * The pointer to the factory of the geometry.
 * @param ipTopData
 * The pointer to the <tt>CATTopData</tt> object used to create the operator.
 * @param ipInputFace
 * The pointer to the input face.
 * @return
 * The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 */
ExportedByCATGMOperatorsInterfaces CATICGM2DBoxComputation *CATCGMCreate2DBoxComputation(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATFace *ipInputFace);

/**
 * Creates the operator that computes a uv bounding box for a CATEdge on a support face.
 * @param ipFactory
 * The pointer to the factory of the geometry.
 * @param ipTopData
 * The pointer to the <tt>CATTopData</tt> object used to create the operator.
 * @param ipInputEdge
 * The pointer to the input edge.
 * @param ipSupportFace
 * The pointer to the support face of the input edge.
 * @return
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGM2DBoxComputation *CATCGMCreate2DBoxComputation(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATEdge *ipInputEdge,
  CATFace *ipSupportFace);

#endif /* CATICGM2DBoxComputation_h_ */
