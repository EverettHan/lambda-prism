/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2005
*/
#ifndef CATCGMStreamOperator_H 
#define CATCGMStreamOperator_H 
//=============================================================================
// DESCRIPTION : Partial Stream 
//=============================================================================
// Feb. 09	Creation For Archi GeometricObjects/GeometricObjectsCGM     TXO/TCX
//=============================================================================
#include "CATGeoFactory.h"
#include "CATCGMStream.h"
#include "CATCGMSafeHashTable.h"
#include "CATListOfCATICGMObjects.h"

/**
*  Class defining an operator for partial Stream.
*/
class ExportedByYP0LOGRP CATCGMStreamOperator
{
public :

  /**
  * Write NewObjects .
  * @param iStream
  *   The stream into which data is written.
  * @param iHashTable
  *   Already managed entities.
  * @param iObjects
  *   Write objects.
  * @param iStoreIntoTable
  *   Set if the sent objects are stored.
  */

  virtual HRESULT WriteNewObjects(CATCGMStream     & iStream, 
    CATCGMSafeHashTable  * iSafeHashTable, 
    const CATLISTP(CATICGMObject)& iObjects,
    CATBoolean iStoreIntoTable = TRUE)= 0;

  /**
  * Read Objects .
  * @param iStream
  *   The stream into which data is written.
  * @param iHashTable
  *   Already managed entities.
  * @param oObjects
  *   Read objects.
  * @param iStoreIntoTable
  *   Set if the received objects are stored.
  */

  virtual HRESULT ReadObjects(CATCGMStream & iStream, 
    CATCGMSafeHashTable* iSafeHashTable,
    CATLISTP(CATICGMObject)& oObjects,
    CATBoolean iStoreIntoTable = TRUE)= 0;

  /**
  * Destructor .
  */
  virtual ~CATCGMStreamOperator();


  /**
  * SetFactory .
  */
  void SetFactory(CATGeoFactory * iFactory);


  /**
  * GetFactory .
  */
  INLINE CATGeoFactory * GetFactory() const;

protected  :

  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATCGMStreamOperator(CATGeoFactory * iFactory);


  CATGeoFactory * _Factory;

private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMStreamOperator(const CATCGMStreamOperator &iCopy);
  CATCGMStreamOperator& operator=(const CATCGMStreamOperator &iCopy);
};


/**
*  GetFactory
* @return
*  The Factory.
*/

INLINE CATGeoFactory *  CATCGMStreamOperator::GetFactory()  const
{
  return _Factory;
}


/**
* Creates an operator for streaming
* @param iFactory
* The factory of the geometry. 
* @return
* The operator.
*/
ExportedByYP0LOGRP CATCGMStreamOperator*  CATCreateCGMStreamOperator(CATGeoFactory * iFactory);

/**
* @nodoc
*/
extern "C" { typedef CATCGMStreamOperator* catcgmstreamcreator(CATGeoFactory * iFactory); }  

#endif
