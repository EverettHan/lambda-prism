
#ifndef CATSysTSFillDictionary_h
#define CATSysTSFillDictionary_h

#include "CATSysTSObjectModeler.h"
#include "CATSysTSMetaClass.h"

/**
 * Do not use this class. For internal use only.
 * Class used to fill in the interface dictionary at runtime.
 */
class ExportedByCATSysTSObjectModeler CATSysTSFillDictionary {
	
   public :
   
	/**
	 * Constructs a CATSysTSFillDictionary instance by means of a class name and the
	 * interface name it implements.
	 * @param iClassName      name of the class implementing the interface
	 * @param iInterfaceName  name of the interface
	 * @param iCreation   creation function
	 */
	CATSysTSFillDictionary(
				const char * iClassName,
				const char * iInterfaceName,
	      CATSysTSCreationFunc iCreation);

	/**
	 * Constructs a CATSysTSFillDictionary instance by means of the meta objects of
	 * both the interface class and the class that implements it.
	 * @param iClassMetaObject      Meta object of the class implementing the interface.
	 * @param iInterfaceMetaObject  Meta object of the interface class.
	 * @param iCreation   Creation function.   
	 */
	CATSysTSFillDictionary(
				const CATSysTSMetaClass * iClassMetaObject,
				const CATSysTSMetaClass * iInterfaceMetaObject,
				CATSysTSCreationFunc iCreation);

    /**
	 * @nodoc 
	 * internal for macros 
	 */
    static int InitMetaClasses(CATSysTSMetaClass * iMetaObject1, CATSysTSMetaClass * iMetaObject2 = 0);
  
};

#endif // CATSysTSFillDictionary_h

