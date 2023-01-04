#ifndef CATSysTSMetaClass_h
#define CATSysTSMetaClass_h

#include "CATSysTSObjectModeler.h"
#include "CATBoolean.h"
#include "IUnknown.h"

/**
 * GUID of the CATSysTSMetaClass class.
 */
extern ExportedByCATSysTSObjectModeler const GUID CLSID_CATSysTSMetaClass;

/**
 * Possible type of class.
 */
enum CATSysTSTypeOfClass {
	CATSysTSNothingType,
	CATSysTSImplementation,
	CATSysTSTIE,
	CATSysTSInterface,
	CATSysTSDataExtension,
	CATSysTSCacheExtension
};

class CATSysTSBaseUnknown;
class CATSysTSMetaClassBase;

/**
 * Creation Function prototype
 */
typedef IUnknown *(*CATSysTSCreationFunc)(CATSysTSBaseUnknown * pBaseImpl, CATBoolean iFullyThreadSafe);

/**
 * Class used to store and manage data for classes that implement interfaces. 
 * There is one instance of CATSysTSMetaClass per class, called the meta object for 
 * that class. 
 * It contains data specific to the class, such as the GUID of the class, the class name.
 */
class ExportedByCATSysTSObjectModeler CATSysTSMetaClass {

	public :

		/**
		 * Returns the class name for which the given object is an instance.
		 */
		virtual const char * IsA() const = 0;
		
		/**
		 * Determines whether the given object's class derives from a given class.
		 * @param iClassName
		 *   The class name from which the given object's class is supposed to derive.
		 * @return 1 if the given object's class derives from <tt>iClassName</tt>
		 * and 0 otherwise.
		 */
		virtual int IsAKindOf(const char * iClassName) const = 0;

		/**
		 * Returns the class identifier (GUID) for the given object.
		 */
		virtual const GUID& __stdcall GetClassId() const = 0;
      
		/**
		 * Determines whether the given object's class derives from a given class.
		 * @param iClsid
		 *   The class identifier (CLSID) from which the given object's class is supposed to derive.
		 * @return 1 if the given object's class derives from the class with
		 * <tt>iClsid</tt> as CLSID and 0 otherwise.
		 */
		virtual int __stdcall IsAKindOf(const CLSID &iClsid) const = 0;

		/**
		 * Determines whether the given object's class derives from a given class whose
		 * meta object is <tt>iMetaObject</tt>
		 * @param iMetaObject
		 *  The meta object of the class from which the given object
		 * class is supposed to derive.
		 * @return 1 if the given object's class derives from the class
		 * whose meta object is <tt>iMetaObject</tt> and 0 otherwise.
		 */
		virtual int __stdcall IsAKindOf(const CATSysTSMetaClass * iMetaObject) const;

		/**
		 * Returns the meta object for the parent class of the given object.
		 */
		virtual CATSysTSMetaClass * __stdcall GetMetaObjectOfBaseClass() const = 0;

		/**
		 * @nodoc  
		 */
        virtual CATSysTSMetaClassBase * ToMetaClassBase() = 0;
      	
	protected :

		//constructor and destructor
		CATSysTSMetaClass();
		virtual ~CATSysTSMetaClass();
};

/**
 * Class to use in the macro CATSysTSImplementClass as fourth parameter
 * when the class which uses this macro is not an extension.
 */
class CATSysTSNull {

   public :
		/**
		 * Returns the meta object associated with CATSysTSNull.
		 */
		static inline CATSysTSMetaClass * MetaObject();
};

inline CATSysTSMetaClass * CATSysTSNull::MetaObject() { return 0; }

#endif // CATSysTSMetaClass_h
