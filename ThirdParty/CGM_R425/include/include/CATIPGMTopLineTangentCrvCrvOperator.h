#ifndef CATIPGMTopLineTangentCrvCrvOperator_h_
#define CATIPGMTopLineTangentCrvCrvOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopTangentCurveOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopLineTangentCrvCrvOperator;

/**
 * @level Protected
 * @usage U1
 */
/**
 * Class defining a topological operator that creates the line bodies tangent to wire bodies.
 *<br>The input line bodies must be coplanar. The underlying plane is represented by a skin body
 * containing of a single face which underlying surface is a plane.
 * This operator follows the general scheme of the topological operators producing several resulting bodies:
 * <ul>
 *<li> Create the operator with the global function <tt>CATPGMCreateTopLineTangentCrvCrvOperator</tt>
 *<li> Set the parameters
 *<li> Run
 *<li> Get the resulting bodies (use the iterator on the resulting bodies, because
 * several line bodies can result from the computation)
 *<li> Release the operator with the <tt>Release</tt> method.
 *</ul>
 * @see CATIPGMTopMultiResult
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopLineTangentCrvCrvOperator: public CATIPGMTopTangentCurveOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopLineTangentCrvCrvOperator();

  /**
 * Defines the type of the created geometry.
 * @param iSupport
 * The type of the geometry to create.
 * <br><b>Legal values</b>: <tt>1</tt> if the geometry of the wire is a CATPLine (line on the supporting plane),
 * <tt>0</tt> if it is a CATLine. By default, a CATPline is created.
 */
  virtual void SetSupportMode(CATLONG32 iSupport = 1) = 0;

  /**
 * Returns the type of the created geometry.
 * @param ioSupportMode
 * The type of the geometry to create.
 * <br><b>Legal values</b>: <tt>1</tt> if the geometry of the wire is a CATPLine (line on the supporting plane),
 * <tt>0</tt> if it is a CATLine.
 */
  virtual void GetSupportMode(CATLONG32 &ioSupportMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopLineTangentCrvCrvOperator(); // -> delete can't be called
};

/**
 * Creates a topological operator to compute the line bodies tangent to two coplanar wire bodies.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. Warning: the 
 * journal of <tt>iTopData</tt> is never filled, because the journal is written for each solution by
 * the parent class of the operator @href CATIPGMTopMultiResult .
 * @param iWire1
 * The pointer to the first wire body.
 * @param iWire2
 * The pointer to the second wire body.
 * @param iPlane
 * The pointer to the plane body which contains the input and output line bodies. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopLineTangentCrvCrvOperator *CATPGMCreateTopLineTangentCrvCrvOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWire1,
  CATBody *iWire2,
  CATBody *iPlane);

#endif /* CATIPGMTopLineTangentCrvCrvOperator_h_ */
