/* -*-C++-*- */
/* COPYRIGHT DASSAULT SYSTEMES 1997                                      */
/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/
/*=======================================================================*/

#ifndef __CATFillDictionary
#define __CATFillDictionary

// this class is used to put information into the dictionary at runtime */

#include <stdio.h>
#include "CATBaseUnknown.h"
#include "CATCreateClassInstance.h"

/* The type of factory functions */
typedef CATBaseUnknown* (*OMFactoryFunctionType) ();

class CATMetaClass;

/**
 * Do not use this class. For internal use only.
 * Class used to fill in the interface dictionary at runtime.
 */
class ExportedByJS0CORBA CATFillDictionary
{
   public :
      // to put class name, interface name and functions in the dictionary
/**
 * Constructs a CATFillDictionary instance by means of a class name that
 * implements an interface.
 * @param iClass      Class implementing the interface
 * @param iInterface  Interface
 * @param iCreation   Creation function
 * @param iCondition  Conditional function
 */
      CATFillDictionary(const char *iClass, const char *inter, void *iCreation,
		        void *iCondition = NULL);
      // to put class id, interface id and functions in the dictionary
/**
 * Constructs a CATFillDictionary instance by means of a class GUID and the
 * interface GUID it implements.
 * @param iClass      GUID of the class implementing the interface
 * @param iInterface  GUID of the interface
 * @param iCreation   Creation function
 * @param iCondition  Conditional function
 */
      CATFillDictionary(const GUID & iClass, const GUID & iInterface,
                        void * iCreation, void * iCondition = NULL);
      // to fill the dictionary using the meta-objects
/**
 * Constructs a CATFillDictionary instance by means of the meta objects of
 * both the interface class and the class that implements it.
 * @param iClassMetaObject      Meta object of the class implementing the interface.
 * @param iInterfaceMetaObject  Meta object of the interface class.
 * @param iCreation   Creation function.   
 * @param iCondition  Conditional function.
 * @param iInheritanceForInterfaces  Inheritance For Interfaces.
 */
      CATFillDictionary(const CATMetaClass * iClassMetaObject,
								const CATMetaClass * iInterfaceMetaObject,
								void * iCreation,
								void * iCondition = NULL,
								int iInheritanceForInterfaces = 1);
      // to put commands in the dictionary
/**
 * Constructs a CATFillDictionary instance by means of a class that implements an
 * interface and a creation function.
 * @param iName Class implementing an interface.      
 * @param iCreation Creation function.
 */
      CATFillDictionary(const char * iname, void * iCreation);
/**
 * Constructs a CATFillDictionary instance by means of a class that implements an
 * interface inside a shared library.
 * @param iName Class that supports the interface.      
 * @param iInterface Interface name.
 * @param iLibrary Library containing the interface implementation code.
 */
      CATFillDictionary(const char * iname, const char * iinterface,
			const char * ilibrary);
/**
 * Constructs a CATFillDictionary instance by means of an extension class
 * that implements an interface for an implementation.
 * @param iExtensionMetaObject Meta object of the extension.
 * @param iInterfaceMetaObject Meta object of the interface.
 * @param iImplementation Implementation name.
 * @param iCreation Creation function.
 */
      CATFillDictionary(CATMetaClass * iExtensionMetaObject,
                        CATMetaClass * iInterfaceMetaObject,
			const char * iImplementation,
			void * iCreation);
			
/**
 * @nodoc 
 * Fills the functions dictionary with a function pointer and its keyname and function type. 
 * @param iKeyName          : the keyname of the registered function 
 * @param iPtrFunct         : the pointer on the function
 * @param iFunctionTypeName : the type of the registered function
 * @return 0 if the call has succeeded else 1
 */		
	static char RegisterFunction(const char * iKeyName, const void * iPtrFunct, const char * iFunctionTypeName);

/**
 * @nodoc 
 * Fills the functions dictionary with a function creation pointer and its keyname. 
 * For more information about creation functions, see CATCreateClassInstance.h
 * @param iKeyName          : the keyname of the registered function 
 * @param iPtrFunct         : the pointer on the creation function 
 * @return 0 if the call has succeeded else 1
 */		
	static char RegisterFunctionCreation(const char * iKeyName, OMFactoryFunctionType iPtrFunct);
};
#endif
