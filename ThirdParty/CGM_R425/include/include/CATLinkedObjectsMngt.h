#ifndef CATLinkedObjectsMngt_H
#define	CATLinkedObjectsMngt_H
// COPYRIGHT DASSAULT SYSTEMES  2011
//===========================================================================  
//  Class  CATLinkedObjectsMngt                 
//---------------------------------------------------------------------------  
//
//  Class that mange a collection of objects and their linked objects
//    
//  Services  
//        1)  
//        2)  
//        3)  
//        4)  
//            
//=============================================================================  
// May. 2011   Creation                                                    KY1
//
//  
//============================================================================= 

#include "YP00IMPL.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include <CATListOfCATCGMObjects.h>
#include "CATErrorDef.h"

class CATGeoFactory;
class CATCGMObject;
class CATICGMObject;
class CATCGMHashTable;
class CATCGMHashTableWithAssoc;
//class CATLISTP(CATCGMObject);

/**
* @nodoc
*/
enum CATKindOfLinkedObject
{
   CATKindOfLinkedObject_ALL,
   CATKindOfLinkedObject_Unknown
};


/**
* @nodoc
* Class dedicated to manage a collection of CGM Objects and their linked objects
*/
class ExportedByYP00IMPL CATLinkedObjectsMngt
{
public:

  CATCGMNewClassArrayDeclare;

    /**
  * @nodoc
  * ctor with parameters
  * @param piGeoFactory 
  *    GeoFactory of handled CGM Object
  */ 
  CATLinkedObjectsMngt(CATGeoFactory *piGeoFactory);

  /**
  * @nodoc
  * ctor with parameters
  * @param iListOfCGMObject 
  *    List of CGM Object to analyze 
  */ 
  void SetListOfCGMObject(CATLISTP(CATCGMObject) &iListOfCGMObject);


  /**
  * @nodoc
  * Init transaction bit of all CGM Objects and their linked objects
  * @param iOption 
  *    Turn on or off the the initialization step
  */
	INLINE void SetInitWorkingBit(CATBoolean iOption);

  /**
  * @nodoc
  * Generic Run : 1- Extracts from the Input Objects the desired sub ojects
  *               2- Delegates the specific processing to the Specific Run
  *	@return
  *	  <dl>
  *	  <dt><tt>S_OK</tt>		<dd>if the Run succeded
  *	  <dt><tt>E_FAIL</tt>    <dd> otherwise
  *	  </dl> 
  *
  * N.B : DO NOT OVERLOAD THIS METHOD
  */

  HRESULT Run();

  /**
  * @nodoc
  * dtor
  */
  virtual ~CATLinkedObjectsMngt();

  /**
  * @nodoc
  * Compute and extract all linked objects of the master object <tt>piCGMObject</tt>.
  * The linked objects are stored in the hash table
  * @param piCGMObject
  *      the object from where hte linked objects are extracted
  * @param pioHashTableOfLinkedObjects
  *      the hash table where linked objects are stored
  */
  static void GetLinkedObjects(CATCGMObject *piCGMObject,CATCGMHashTableWithAssoc *&pioHashTableOfLinkedObjects,CATBoolean iInitWorkingBit);

  /**
  * @nodoc
  * read  level one federators of a given <tt>piCGMitf</tt>.
  * construct a hashtable where federator interfaces are stored
  * @param piCGMitf
  *      the object for which federators are asked
  * @return
  *      the hash table where federator interfaces are stored
  */
  CATCGMHashTable * GetFederators(CATICGMObject *piCGMitf);

protected:
  /**
  * @nodoc
  * Specific Run :1- Execute an action on each linked objects
  *	@return
  *	  <dl>
  *	  <dt><tt>S_OK</tt>		<dd>if RunObject succeeded
  *	  <dt><tt>E_FAIL</tt>    <dd> otherwise
  *	  </dl> 
  *
  * N.B : YOU HAVE TO OVERLOAD THIS METHOD if you want to execute a specific action on each linked object
  */
  virtual HRESULT RunObject();

  /**
  * @nodoc
  * Clean method: called by dtor or if a throw is happened
  */
  void Clean();

  /**
  * @nodoc
  * Access to Hash Table of a requested object
  */
  CATCGMHashTableWithAssoc *GetCGMHashTableOfObject(CATCGMObject *piCGMObject);


  //DATA
  CATGeoFactory*						  _pFactory;
  CATLISTP(CATCGMObject)		 	_ListOfMasterCGMObject;									// List of Master CGM Objects  
  CATCGMHashTable*				  	_HashTableOfAllLinkedObjects;						// Hash Table to store all linked objects 
  CATCGMHashTableWithAssoc**	_HT_LinkedObjectsOfMasterObjects;				// Hash Table of linked objects per object, Each federated object has a multiplicity value (count number of upper objects that federate the linked object)
  CATBoolean						    	_InitWorkingBit;												// To Init bit of transaction of each object stored in the hash table 

  //CATCGMHashTableWithAssoc *_HashTableOfCGMObjectsWithLinkedObjects;	// Hash Table to store all objects and their linked objects
  //CATCGMHashTable **_HashTableOfLinkedObjectsPerObject;								// Hash Table to store all linked objects 
 
  private:
  
  CATLinkedObjectsMngt();
  CATLinkedObjectsMngt(const CATLinkedObjectsMngt &iCopy);
  CATLinkedObjectsMngt& operator=(const CATLinkedObjectsMngt &iCopy);
};

//-----------------------------------------------------------------------------------------------
// SetInitWorkingBit(...) : 
//-----------------------------------------------------------------------------------------------
INLINE void CATLinkedObjectsMngt::SetInitWorkingBit(CATBoolean iOption)
{
   _InitWorkingBit = iOption;
}
#endif


