#ifndef CATCGMVirtualItf_h
#define CATCGMVirtualItf_h

#include "CATMathematics.h"
#include "IUnknown.h"
#include "CATCGMNewArray.h"

class CATCGMItfInternalData;
class CATCGMItfMetaClass;

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * CGM interface root class.
 */
class ExportedByCATMathematics CATCGMVirtualItf: public IUnknown
{
  friend class CATCGMItfInternalData;
public:
  /** @nodoc  */
  CATCGMNewClassArrayDeclare;

  /**
   * Constructor
   */
  CATCGMVirtualItf();

  /**
   * @nodoc
   * Returns the meta class associated with the interface.<br>
   * Note that it's handled by the implementation in order not to expose more internal data.
   */
  virtual const CATCGMItfMetaClass &GetItfMetaClass() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATCGMVirtualItf();

  /**
   * @nodoc
   * Returns the internal data.
   */
  virtual CATCGMItfInternalData &GetInternalData() = 0;

private:
  CATCGMVirtualItf(const CATCGMVirtualItf &iObject); // Prohibited
  CATCGMVirtualItf &operator=(const CATCGMVirtualItf &iObject); // Prohibited
};

#endif
