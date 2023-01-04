#ifndef CATIPGMHybRegularize_h_
#define CATIPGMHybRegularize_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybOperatorImp.h"
#include "CATCollec.h"

class CATExtHybRegularize;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybRegularize;

class ExportedByCATGMOperatorsInterfaces CATIPGMHybRegularize: public CATIPGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATIPGMHybRegularize();

  /** @nodoc */
  virtual int Run() = 0;

  /** @nodoc */
  virtual void SetCellsToRegularize(CATLISTP(CATCell) &iCellsToRegularize) = 0;

  /** @nodoc */
  virtual void SuppressOnlySmallClosedEdges() = 0;

  /** @nodoc  */
  virtual CATExtHybRegularize *GetHybRegularizeExtensible() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybRegularize(); // -> delete can't be called
};

#endif /* CATIPGMHybRegularize_h_ */
