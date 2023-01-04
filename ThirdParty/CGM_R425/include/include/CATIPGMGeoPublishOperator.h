#ifndef CATIPGMGeoPublishOperator_h_
#define CATIPGMGeoPublishOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMGeoOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMGeoPublishOperator;

/**
* Class representing the operator that publish a CATICGMObject in another factory.
*
* This operator does not duplicate the objet in another factor but try to find the simpliest form of a object 
* in another factory. That mean that the type of the published objet can be totally different from the original objet.
*
* This operator does follow the general scheme of operator :
*
* - It is created with the "CATPGMCreateGeoPublishOperator" method.
* - It must be run with the "Run" method.
* - Get the published image with the "GetResult" method.
* 
* - Caution : the publication must be done in another factory than the input factory.
*
* What does the first version of the operator :
*
* - the image of a macro point give a cartesian point.
* - any other geometry gives NULL ( in this case the "CloneManager" has to be used instead ).
*
* This operator is dedicated to the need of MechanicalModeler / Publication
*
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMGeoPublishOperator: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMGeoPublishOperator();

  // GetResult ( to be used after the Run )
  virtual CATICGMObject *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMGeoPublishOperator(); // -> delete can't be called
};

/**
 * Creates a CATPGMCreateGeoPublishOperator operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iCGMObject
 * The pointer to the CATICGMObject to publish.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMGeoPublishOperator *CATPGMCreateGeoPublishOperator(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATICGMObject *iCGMObjectToPublish);

#endif /* CATIPGMGeoPublishOperator_h_ */
