#ifndef CATCGMVirtualMetaClass_h
#define CATCGMVirtualMetaClass_h

#include "CATMathematics.h"

class CATCGMItfMetaClass;

/** @CAA2Required */

/**
 * @nodoc
 * Description of a derived class of CATCGMVirtual.
 */
class ExportedByCATMathematics CATCGMVirtualMetaClass
{
  friend class CATCGMItfMetaClass;
public:
  /**
   * @nodoc
   * Constructor.
   * @param ipParentClassMetaClass
   *   The parent class' meta class.
   */
  CATCGMVirtualMetaClass(const CATCGMVirtualMetaClass *ipParentClassMetaClass);

  /**
   * @nodoc
   * Destructor.
   */
  ~CATCGMVirtualMetaClass();

  /**
   * @nodoc
   * Returns the parent class' meta class.
   */
  const CATCGMVirtualMetaClass *GetParentClassMetaClass() const;

  /**
   * @nodoc
   * Returns the first CGM interface's meta class.
   */
  const CATCGMItfMetaClass *GetFirstItfMetaClass() const;

protected:
  /**
   * @nodoc
   * Sets the first CGM interface's meta class.
   */
  void SetFirstItfMetaClass(const CATCGMItfMetaClass *ipFirstItfMetaClass);

private:
  CATCGMVirtualMetaClass(const CATCGMVirtualMetaClass &iParentClassMetaClass); // Prohibited
  CATCGMVirtualMetaClass &operator=(const CATCGMVirtualMetaClass &iParentClassMetaClass); // Prohibited

  const CATCGMVirtualMetaClass *_pParentClassMetaClass;
  const CATCGMItfMetaClass *_pFirstItfMetaClass;
};

#endif /* CATCGMVirtualMetaClass_h */
