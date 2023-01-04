#ifndef CATIPGMFluidRegionLidOperator_h_
#define CATIPGMFluidRegionLidOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATFace;
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFluidRegionLidOperator;

/**
 * Interface representing an operator that uses a solid bodies and geometries on
 * those bodies to create one or more surfacic lids that will be used for the fluid region
 * extract operator. 
 * The solid container bodies and resulting lids should enclose one or more volumes
 * 
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateFluidRegionLidOperator</tt> global function.
 * <li>Run it
 * <li>Get the resulting body with the <tt>GetResult</tt> method. If you do not want
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the
 * geometric factory, after the operator deletion.
 *<li>delete it after use  with the usual C++ <tt>delete</tt> operator.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMFluidRegionLidOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFluidRegionLidOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFluidRegionLidOperator(); // -> delete can't be called
};

/**
 * Creates a CATFluidRegionLid operator that will create a single lid only.
 * @param iFactory
 * The pointer to the factory of the geometry for the creation of the resulting body.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iSolidContainerBodyList
 * List of solid container bodies.
 * @param iEdgeList
 * List of edges lying on the container bodies.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFluidRegionLidOperator *CATPGMCreateFluidRegionLidOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) &iSolidContainerBodyList,
  CATLISTP(CATEdge) &iEdgeList);

/**
 * Creates a CATFluidRegionLid operator that will create one lid for each intenal loop of the face that does not
 * surround material in the solid conainer body.
 * @param iFactory
 * The pointer to the factory of the geometry for the creation of the resulting body.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt>
 * is <tt>NULL</tt>, it is not filled.
 * @param iSolidContainerBodyList
 * List of solid container bodies.
 * @param iFace
 * A face lying on one of the container bodies.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFluidRegionLidOperator *CATPGMCreateFluidRegionLidOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) &iSolidContainerBodyList,
  CATFace *iFace);

/**
 * Creates a CATFluidRegionLid operator that will automatically create all the lids required for a
 * list of solid container bodies.
 * @param iFactory
 * The pointer to the factory of the geometry for the creation of the resulting body.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt>
 * is <tt>NULL</tt>, it is not filled.
 * @param iSolidContainerBodyList
 * List of solid container bodies.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFluidRegionLidOperator *CATPGMCreateFluidRegionLidOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) &iSolidContainerBodyList);

#endif /* CATIPGMFluidRegionLidOperator_h_ */
