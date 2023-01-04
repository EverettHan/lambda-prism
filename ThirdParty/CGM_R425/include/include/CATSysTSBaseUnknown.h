#ifndef CATSysTSBaseUnknown_h
#define CATSysTSBaseUnknown_h

// COPYRIGHT DASSAULT SYSTEMES 2004

#include "CATSysTSObjectModeler.h"
#include "IUnknown.h"
#include "CATBoolean.h"
#include "CATSysTSMetaClass.h"
#include "CATSmartMutex.h"

/**
 * GUID of the class CATSysTSBaseUnknown.
 */
extern ExportedByCATSysTSObjectModeler const GUID CLSID_CATSysTSBaseUnknown;

/**
 * IID of the interface CATSysTSBaseUnknown.
 */
#define IID_CATSysTSBaseUnknown CLSID_CATSysTSBaseUnknown

/**
 * Data for extension/TIE/implementation
 */
class CATSysTSChainExtension;
class CATSysTSBaseUnknown;
union CATSysTSTypeOfData
{
  CATSysTSChainExtension * ForImplementation;
  CATSysTSBaseUnknown    * ForExtension;
  CATSysTSBaseUnknown    * ForTIE;
};


/**
 * Base class for creating interfaces and for implementing interfaces in Thread Safe mode.
 * <b>Role</b>: CATSysTSBaseUnknown supplies the implementation for 
 * the IUnknown interface methods @href #QueryInterface, @href #AddRef and @href #Release.
 */
class ExportedByCATSysTSObjectModeler CATSysTSBaseUnknown : public IUnknown {
	public:

		/**
		 * Constructor.
		 * @param iFullyThreadSafe
		 * Specifies whether the instance is fully thread safe or not.
		 * Only fully thread safe CATSysTSBaseUnknown can be shared between different threads.
		 */
		CATSysTSBaseUnknown(CATBoolean iFullyThreadSafe);

		/**
		 * Retrieves a pointer to a given interface.
		 * @param iIID
		 *   The interface identifier for which a pointer is requested.
		 * @param oPPV
		 *   The address where the returned pointer to the interface is located.
		 * @return
		 *   An HRESULT value. 
		 *   <br><b>Legal values</b>:
		 *   <dl>
		 *     <dt>S_OK</dt>
		 *     <dd>The query succeeds.</dd>
		 *     <dt>E_NOINTERFACE </dt>
		 *     <dd>The interface does not exist.</dd>
		 *     <dt>E_FAIL </dt>
		 *     <dd>The object is not valid.</dd>
		 *     <dt>E_OUTOFMEMORY </dt>
		 *     <dd>One memory allocation fails</bb>
		 *     <dt>E_UNEXPECTED </dt>
		 *     <dd>The query fails for any other reason</dd>
		 *   </dl>
		 */
		virtual HRESULT __stdcall QueryInterface(const IID &iIID, void ** oPPV);
		/**
		 * Increments the reference count for the given interface. 
		 * @return The reference count value.
		 */
		virtual ULONG __stdcall AddRef();

		/**
		 * Decrements the reference count for the given interface. 
		 * @return The reference count value.
		 */
		virtual ULONG __stdcall Release();

		/**
		 * Returns a pointer to the class meta object.
		 * There is one meta object per class.
		 */
		virtual CATSysTSMetaClass * __stdcall GetMetaObject() const;

		/**
		 * Returns the class name for which the given object is an instance.
		 */
		const char * IsA() const;

		/**
		 * Determines whether the given object's class derives from a given class.
		 * @param iName
		 *   The class name from which the given object's class is supposed to derive.
		 * @return 0 if the given object's class doesn't derive from <tt>iName</tt>
		 * and a non null value otherwise.
		 * @return
		 * <br><b>Legal values</b>:
		 *   <dl>
		 *     <dt>0 </dt>
		 *        <dd>Current onject does not derive from iName.</dd>
		 *     <dt>1 </dt>
		 *        <dd>Otherwise.</dd>
		 *   </dl>
		 */
		int IsAKindOf(const char *iName) const;

		/**
		 * Returns whether the instance is fully thread safe or not.
		 * Only fully thread safe CATSysTSBaseUnknown can be shared between different threads.
		 */
		inline CATBoolean IsFullyThreadSafe();

		/**
		 * Returns a pointer to the class meta object.
		 */
		static  CATSysTSMetaClass * __stdcall MetaObject();

		/**
		 * Returns the class name for which the given object is an instance.
		 */
		static  const char *  __stdcall ClassName();

		/**
		 * Returns the class identifier for which the given object is an instance.
		 */
		static  const CLSID & __stdcall ClassId();

	protected:

		/**
		 * Destructor. 
		 */
		virtual ~CATSysTSBaseUnknown();

		/**
		 * Acquires a lock on the internal mutex
		 */
		void Lock();

		/**
		 * Releases a lock on the internal mutex
		 */
		void Unlock();

		/**
		 * Mutex of the instance. Used only for fully thead safe instances.
		 */
		CATSmartMutex _mutex;

		/**
		 * Reference counter.
		 */
		LONG m_cRef;
  
		/**
		 * @nodoc
		 */
		CATSysTSTypeOfData NecessaryData;

	private:

		/**
		 * Default constructor.
		 */
		CATSysTSBaseUnknown();

		/**
		 * Copy Constructor.
		 * @param iObj The CATSysTSBaseUnknown instance to copy
		 */
		CATSysTSBaseUnknown(const CATSysTSBaseUnknown &iObj);

		// meta class pointer
		static CATSysTSMetaClass *meta_object;

		friend class CATSysTSTIEInternal;
		friend class CATSysTSBOAInternal;
		
		// ++IK8 19:08:08 Poor man's way of tracking recursive "_mutex" lock count
		LONG _mutexLockCount;
		// --IK8 19:08:08
};

inline CATBoolean CATSysTSBaseUnknown::IsFullyThreadSafe() {
	return _mutex.IsCreated() ? TRUE : FALSE;	// Cf. risk of cast from int to CATBoolean
}

/**
 * @nodoc
 */
ExportedByCATSysTSObjectModeler int CATSysTSConvertStringToGUID(const char * str, GUID &clsid);

#include "CATSysTSMacForIUnknown.h"

#endif // CATSysTSBaseUnknown_h

