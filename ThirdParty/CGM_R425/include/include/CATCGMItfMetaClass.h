#ifndef CATCGMItfMetaClass_h
#define CATCGMItfMetaClass_h

#include "CATMathematics.h"
#include "IUnknown.h"
#include "CATCGMItfDestrBehavior.h"
#include "CATBoolean.h"

class CATCGMVirtual;
class CATCGMVirtualItf;
class CATCGMVirtualMetaClass;

/**
 * CGM interface meta class.
 * <b>Role:</b> This class links the interface and its interfaced class.
 */
class ExportedByCATMathematics CATCGMItfMetaClass
{
public:
  /**
   * Constructor
   * @param iIID
   *   The interface ID. Pay attention: a reference is kept on iIID so use only static variable.
   * @param ipParentItfMetaClass
   *   The parent interface's meta class.
   * @param iInterfacedClassMetaClass
   *   The interfaced class's dictionary.
   * @param iMakeRootItfFn
   *   The function that creates the root interface.
   * @param iMakeLinkedItfFn
   *   The function that creates a linked interface.
   */
  CATCGMItfMetaClass(
    const IID &iIID,
    const CATCGMItfMetaClass *ipParentItfMetaClass,
    const CATCGMVirtualMetaClass &iInterfacedClassMetaClass,
    CATCGMVirtualItf *(*iMakeRootItfFn)(CATCGMVirtual &iHandledObject, CATCGMItfDestrBehavior iItfDestrBehavior),
    CATCGMVirtualItf *(*iMakeLinkedItfFn)(CATCGMVirtualItf &iPreviousItf));

  ~CATCGMItfMetaClass();

  /**
   * Returns the interface's IID
   */
  const IID &GetIID() const;

  /**
   * Returns the parent interface's meta class.
   */
  const CATCGMItfMetaClass *GetParentItfMetaClass() const;

  /**
   * Returns the interface classed's meta class.
   */
  const CATCGMVirtualMetaClass &GetInterfacedClassMetaClass() const;

  /**
   * Makes a root interface.
   */
  CATCGMVirtualItf *MakeRootItf(CATCGMVirtual &iHandledObject, CATCGMItfDestrBehavior iItfDestrBehavior) const;

  /**
   * Makes a linked interface.
   */
  CATCGMVirtualItf *MakeLinkedItf(CATCGMVirtualItf &iPreviousItf) const;

  /**
   * Tells if the IID is the interface's IID or a parent interface's IID.
   * @param iIID
   *   The Id.
   * @return
   *   <tt>TRUE</tt> if the Id is the interface's IID or a parent interface's IID.
   */
  CATBoolean IsIIDOrParentItfIID(const IID &iIID) const;

  /**
   * @nodoc
   */
  void SetPreviousItem(const CATCGMItfMetaClass *ipPreviousItem);

  /**
   * Returns the previous item of the chained list.
   */
  const CATCGMItfMetaClass *GetPreviousItem() const;

  /**
   * Returns the next item of the chained list.
   */
  const CATCGMItfMetaClass *GetNextItem() const;

private:
  const IID *_pIID;
  const CATCGMItfMetaClass *_pParentItfMetaClass;
  const CATCGMVirtualMetaClass *_pInterfacedClassMetaClass;
  CATCGMVirtualItf *(*_pMakeRootItfFn)(CATCGMVirtual &iHandledObject, CATCGMItfDestrBehavior iItfDestrBehavior);
  CATCGMVirtualItf *(*_pMakeLinkedItfFn)(CATCGMVirtualItf &iPreviousItf);

  const CATCGMItfMetaClass *_pPreviousItem;
  const CATCGMItfMetaClass *_pNextItem;
};

#endif /* CATCGMItfMetaClass_h */
