#ifndef CATNUpletOfCATICGMObject_H
#define	CATNUpletOfCATICGMObject_H
// COPYRIGHT DASSAULT SYSTEMES  2014
/**
* @CAA2Level L1 ????
* @CAA2Usage U1 ???? 
*/ 

class CATCell;
class CATCellHashTable;

#include "ExportedByGeometricObjects.h"
#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"
#include "CATListOfCATICGMObjects.h"
#include "CATBoolean.h"
//#include "CATCollec.h"

class CATICGMObject;
//class CATLISTP(CATICGMObject);


/**
* Class to manage a N Uplet of CATICGMObject
*
*
*/

class ExportedByGeometricObjects CATNUpletOfCATICGMObject
{
public:
  CATCGMNewClassArrayDeclare;

  /**
  * Default ctor
  */
  CATNUpletOfCATICGMObject();

  /**
  * param ctor
  * * @param iListOfCells 
  *   Cells List to transpose in a CATNUpletOfCATICGMObject
  */
  CATNUpletOfCATICGMObject (CATLISTP(CATICGMObject) &iListOfCGMObject);
    
  
  /**
  * destructor
  */
  virtual ~CATNUpletOfCATICGMObject();
  
  /**
  * Get the size of the SetOfCells
  * @return
  *   return size
  */
  int           Size();

  /**
  * Get the ieme CGMObject of the NUpletOfCATICGMObject
  *	  @param
  *    i index of the CGMObject
  * @return
  *   Ptr of CGMObject
  */
  CATICGMObject*	  	Get(int i);	 //(i=1 .. n)
    
  /**
  * Test the equality between two SetOfCells
  *	  @param
  *    iSetOfCells SetOfCells to compare with this
  * @return
  *	  <dl>
  *	  <dt><tt>0</tt>		<dd>if the sets contains the same cells
  *	  <dt><tt>1</tt>        <dd>if the sets are not equal
  *	  </dl>
  */
  int           IsEqual(CATNUpletOfCATICGMObject& iNUpletOfCATICGMObject);

  /**
  * Computes the HashKey og the set by suming tags of cells  
  * @return
  *    a hash key of this
  */
  CATULONG32    HashKey();

  /**
  * Test the equality between two SetOfCells
  *	 @param
  *    oListOfCells transpose the SetOfCells in a ListPOfCATCell
  */
  //void          GetList(CATLISTP(CATICGMObject)& ioListOfCATICGMObject);
    
  
  /** LifeCycle protection  */
  //INLINE unsigned short IncreaseCounter();

  //INLINE unsigned short DecreaseCounter();

private: 

	/**
  * copy ctor
  * @param iSetOfCells
  *   iSetOfCells to copy
  */
  CATNUpletOfCATICGMObject (const CATNUpletOfCATICGMObject& iSetOfCells);

  /**
  * operator =
  * @param iSetOfCells
  *   iSetOfCells to to copy
  */
  CATNUpletOfCATICGMObject& operator = (const CATNUpletOfCATICGMObject& iSetOfCells);


  //DATA
  CATLISTP(CATICGMObject) _ListOfCATICGMObject;
  
  /** LifeCycle */
  //unsigned int                 _Counter;

};

//INLINE  unsigned short CATNUpletOfCATICGMObject::IncreaseCounter()
//{ return ++_Counter; }

//INLINE  unsigned short CATNUpletOfCATICGMObject::DecreaseCounter()
//{ unsigned short rc = --_Counter; if ( 0 == rc ) delete this; return rc; }

#endif 
