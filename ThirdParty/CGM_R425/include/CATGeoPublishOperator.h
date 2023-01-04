#ifndef CATGeoPublishOperator_h
#define CATGeoPublishOperator_h

// COPYRIGHT DASSAULT SYSTEMES 1999

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATICGMObject;

#include "CATGeoOperator.h"
#include "BOOPER.h"

/**
* Class representing the operator that publish a CATICGMObject in another factory.
*
* This operator does not duplicate the objet in another factor but try to find the simpliest form of a object 
* in another factory. That mean that the type of the published objet can be totally different from the original objet.
*
* This operator does follow the general scheme of operator :
*
* - It is created with the "CATCreateGeoPublishOperator" method.
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

class ExportedByBOOPER CATGeoPublishOperator : public CATGeoOperator
{

  CATCGMVirtualDeclareClass(CATGeoPublishOperator);
public :
// -----

  // Destructor
  virtual ~CATGeoPublishOperator();

  // GetResult ( to be used after the Run )
  virtual CATICGMObject * GetResult() = 0;

protected :
// --------
   
  // Constructor
  CATGeoPublishOperator ( CATGeoFactory  * iFactory );
  

};


/**
 * Creates a CATCreateGeoPublishOperator operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iCGMObject
 * The pointer to the CATICGMObject to publish.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */

ExportedByBOOPER CATGeoPublishOperator * CATCreateGeoPublishOperator ( CATGeoFactory            * iFactory            ,
                                                                       CATSoftwareConfiguration * iConfig             ,
                                                                       CATICGMObject            * iCGMObjectToPublish );

#endif
