#ifndef CATSysTSCreateExternalObject_h
#define CATSysTSCreateExternalObject_h

// COPYRIGHT DASSAULT SYSTEMES 2004

#include "CATSysTSObjectModeler.h"
#include "CATSysTSFillDictionary.h"

#ifdef  _AIX_SOURCE
#define Exported  
#else
#define Exported DSYExport
#endif
#include "DSYExport.h"

/**
 * Defines the class creation function.
 * @param Class 
 * Class to create and used as input of the @href CATSysTSCreateExternalObject function. 
 */
#define CATSysTSCreateClass(Class)						\
									\
extern "C" Exported CATSysTSBaseUnknown * fctCATSysTSCreate##Class(void * _pt_Arg)	{		\
   return (new Class());					\
}									\
									\
CATSysTSFillDictionary static_CATSysTSCreate##Class(#Class, "CreateInterface", (CATSysTSCreationFunc)fctCATSysTSCreate##Class)

/**
 * Defines the class creation function with an argument.
 * @param Class 
 * Class to create and used as input of the @href CATSysTSCreateExternalObject function. 
 * @param TypArg 
 * Argument type expected by the function
 */
#define CATSysTSCreateClassArg(Class, TypArg)					\
									\
extern "C" Exported CATSysTSBaseUnknown *fctCATSysTSCreate##Class(TypArg *_pt_Arg)	{	 \
   return (new Class(_pt_Arg));					\
}									\
									\
CATSysTSFillDictionary static_CreateArg##Class(#Class, "CreateInterface", (CATSysTSCreationFunc)fctCATSysTSCreate##Class)


/**
 * Creates a class from its name.
 * @param iClassName
 *   Name of the class to instantiate
 * @param iLibraryName
 *   Optional name of the library used to retrieve its executable code file.
 *   CATSysTSCreateExternalObject possibly adds a prefix and a suffix to this name to
 *   match the operating system naming convention. For example, the command
 *   CD0PRINT is named libCD0PRINT.a with AIX, libCD0PRINT.sl with HP, libCD0PRINT.so
 *   with IRIX and SOLARIS, and CD0PRINT.dll with Windows/NT.
 *   If iLibraryName is not specified, the dictionary file must contains the entry :
 *   ClassName CreateInterface libLibraryName
 * @param iArg
 *   Optional argument value passed to the class constructor. 
 * @return
 *   A pointer to the created object or NULL if an error occured.
 */
ExportedByCATSysTSObjectModeler extern CATSysTSBaseUnknown * CATSysTSCreateExternalObject(
			const char * iClassName,
			const char * iLibraryName = 0,
			void * iArg = 0);


#endif // CATSysTSCreateExternalObject_h
