#ifndef CATCGMObjectBuilder_h
#define CATCGMObjectBuilder_h

#include "CATMathematics.h"
#include "CATBaseUnknown.h"

/**
 * Implementation to be extended by each framework in order to create implementations of CGM interfaces.
 */
class ExportedByCATMathematics CATCGMObjectBuilder: public CATBaseUnknown
{
  CATDeclareClass;
public:
  /**
   * Returns the only instance in the session.
   * @return
   *   The singleton. Pay attention: no <tt>AddRef</tt> is run.
   */
  static CATCGMObjectBuilder &GetSingleton();

protected:
  CATCGMObjectBuilder();
  virtual ~CATCGMObjectBuilder();

private:
  CATCGMObjectBuilder(const CATCGMObjectBuilder &iObject); // Prohibited
  CATCGMObjectBuilder &operator=(const CATCGMObjectBuilder &iObject); // Prohibited
};

#endif /* CATCGMObjectBuilder_h */
