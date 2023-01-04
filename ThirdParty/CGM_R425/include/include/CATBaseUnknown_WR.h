#ifndef CATBaseUnknown_WR_h
#define CATBaseUnknown_WR_h
/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATIAV5Level.h"
#include "JS0CORBA.h"
#include "CATBaseUnknown_var.h"
class CATSysWeakRef;

class ExportedByJS0CORBA CATBaseUnknown_WR
{
public:
  CATBaseUnknown_WR();
  CATBaseUnknown_WR(const CATBaseUnknown_WR &);
  ~CATBaseUnknown_WR();

  const CATBaseUnknown_WR &operator=(const CATBaseUnknown_WR &);
  const CATBaseUnknown_WR &operator=(CATBaseUnknown*);

  operator CATBaseUnknown_var() const;
  /**
   * Return an addrefed component
   */
  CATBaseUnknown *GetComponent() const;

  int operator!() const;

  int operator==(CATBaseUnknown *obj) const;
  int operator!=(CATBaseUnknown *obj) const;

  int operator==(const CATBaseUnknown_WR & iObj) const;
  int operator!=(const CATBaseUnknown_WR & iObj) const;

private:
  CATSysWeakRef *_WeakRef;
};

#endif //CATBaseUnknown_WR_h
