#ifndef CATCGMRefCounted_h_
#define CATCGMRefCounted_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 

/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"


/**
* Class that implements ref-counting.  
* (Comment: This implementation is not thread-safe.  To do.)
*/
class ExportedByCATGMModelInterfaces CATCGMRefCounted
{

protected:

  inline CATCGMRefCounted ();
  virtual ~CATCGMRefCounted ();

public:

  /**  
   * Increments  the  reference  count  for  the  given  interface. 
   * @return 
   *   The reference count value.  
   */  
  CATULONG32 AddRef ();

  /**  
   * Decrements  the  reference  count  for  the  given  interface and
   * deletes the object when the reference count reaches 0.
   * @return 
   *   The reference count value.  
   */  
  CATULONG32 Release ();  

private:

  CATULONG32 _RefCount;

};


inline CATCGMRefCounted::CATCGMRefCounted () :
  _RefCount (1)
{
}


#endif /* CATCGMRefCounted_h_ */
