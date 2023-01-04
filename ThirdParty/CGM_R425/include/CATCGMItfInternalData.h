#ifndef CATCGMItfInternalData_h
#define CATCGMItfInternalData_h

#include "CATMathematics.h"
#include "IUnknown.h"
#include "CATBoolean.h"
#include "CATString.h"
#include "CATCGMItfDestrBehavior.h"
#include "CATThrowForNullPointer.h"
#include "CATMathInline.h"

class CATSysSimpleHashTable;
class CATCGMVirtual;
class CATCGMItfInternalData;
class CATCGMItfMetaClass;
class CATCGMVirtualItf;
class CATCGMVirtualMetaClass;

/**
 * Internal data for CGM virtual objects' interfaces.
 * <b>Role:</b> This object manages the interface it belongs to.<br>
 * The instance of the owning interface is the envelop. The instance of the internal CGM class is the letter.
 */
class ExportedByCATMathematics CATCGMItfInternalData
{
public:
  /**
   * Constructs an empty data.<br>
   * You must call @href #Initialize
   */
  CATCGMItfInternalData();

  /**
   * Destructor
   */
  ~CATCGMItfInternalData();

  /**
   * Destroys the object.
   * @param iOwningItf
   *   The interface that owns the data
   * @param opHandledObjectToDel
   *   If it's not <tt>NULL</tt>, the object to delete.
   */
  void Remove(CATCGMVirtualItf &iOwningItf, CATCGMVirtual *&opHandledObjectToDel);

  /**
   * Initializes the instance with a handled object.
   * @param iOwningItf
   *   The interface that owns the data
   * @param iHandledObject
   *   The object to be handled
   * @param iItfDestrBehavior
   *   <tt>TRUE</tt> if the handled object must be deleted with the current data.
   */
  void Initialize(CATCGMVirtualItf &iOwningItf, CATCGMVirtual &iHandledObject, CATCGMItfDestrBehavior iItfDestrBehavior);

  /**
   * Initializes the instance linked to another one.
   * @param iOwningItf
   *   The interface that owns the data
   * @param iPreviousItf
   *   The data to be linked with. An <tt>AddRef()</tt> is run on the previous data's owner.
   */
  void Initialize(CATCGMVirtualItf &iOwningItf, CATCGMVirtualItf &iPreviousItf);

  /**
   * Returns the handled object.
   */
  INLINE CATCGMVirtual &GetHandledObject() const;

  /**
   * Returns the handled object's meta class.
   */
  INLINE const CATCGMVirtualMetaClass &GetHandledObjectMetaClass() const;

  // Interface owner lifecycle management

  /**
   * Queries an interface to the interface that owns the data.
   * @param iOwningItf
   *   The interface that owns the data
   * @param iIID
   *   The queried interface Id.
   * @param *oPPV
   *   The output interface
   * @return
   *   The QueryInterface return code.
   */
  HRESULT OwnerQueryInterface(CATCGMVirtualItf &iOwningItf, const IID &iIID, void **oPPV);

  // Chained list management

  /**
   * Gets the previous interface of the chained list.
   */
  CATCGMVirtualItf *GetPreviousItf() const;

  /**
   * Gets the next interface of the chained list.
   */
  CATCGMVirtualItf *GetNextItf() const;

  /**
   * Returns the first interface associated with a handled object in the session.
   * If a problem of handled object/interface lifecycles is detected, the hash table is cleaned.
   */
  static CATCGMVirtualItf *GetFirstItf(const CATCGMVirtual &iHandledObject);

  /**
   * Returns the interface's meta class in order to make an interface for the object.
   * @param iInterfacedClassMetaClass
   *   The meta class of the class to be interfaced.
   * @param iIID
   *   The interface Id.
   */
  static const CATCGMItfMetaClass *GetItfMetaClass(const CATCGMVirtualMetaClass &iInterfacedClassMetaClass, const IID &iIID);

  // Services
  
  /**
   * Returns the internal data of an interface
   */
  static const CATCGMItfInternalData &GetInternalData(const CATCGMVirtualItf &iObject);

protected:
  /**
   * Sets the interface as the next one in the chained list.
   */
  void SetNextItf(CATCGMVirtualItf *ipNextItf);

  /**
   * Sets the interface as the previous one in the chained list.
   */
  void SetPreviousItf(CATCGMVirtualItf *ipPreviousItf);

  /**
   * Sets if the handled object must be deleted at end.
   */
  void SetDeleteHObjAtEnd(CATCGMItfDestrBehavior iItfDestrBehavior);

  /**
   * Returns if the handled object must be deleted at end.
   */
  CATBoolean DeleteHObjAtEnd() const;

private:
  CATCGMItfInternalData(const CATCGMItfInternalData &iObject); // Prohibited
  CATCGMItfInternalData &operator=(const CATCGMItfInternalData &iObject); // Prohibited

  // For CATSysSimpleHashTable

  /**
   * Returns the data's handled object or the criteria.
   */
  static const CATCGMVirtual &GetItfHObjOrCriteria(void *ipObj1);

  /**
   * Computes the hask key of the data by its handled object.
   */
  static unsigned int SimpleHashItfByHObj(void *ipObj1);

  /**
   * Compares two interfaces with their handled objects.
   */
  static int SimpleCompareItfByHObj(void *ipObj1, void *ipObj2);

  CATCGMVirtual *_pHandledObject;
  const CATCGMVirtualMetaClass *_pHandledObjectMetaClass;
  CATBoolean _DeleteHObjAtEnd;
  CATCGMVirtualItf *_pPreviousItf;
  CATCGMVirtualItf *_pNextItf;

  static CATSysSimpleHashTable *_pItfHTab;
  static const CATCGMVirtual *_pHObjCriteria;
};

INLINE CATCGMVirtual &CATCGMItfInternalData::GetHandledObject() const
{
  if (_pHandledObject == NULL)
    CATThrowForNullPointerReturnValue(*(CATCGMVirtual *)NULL);
  return *_pHandledObject;
}

INLINE const CATCGMVirtualMetaClass &CATCGMItfInternalData::GetHandledObjectMetaClass() const
{
  if (_pHandledObjectMetaClass == NULL)
    CATThrowForNullPointerReturnValue(*(const CATCGMVirtualMetaClass *)NULL);
  return *_pHandledObjectMetaClass;
}

#endif
