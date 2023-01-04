#ifndef CATAdvancedOperator_H
#define CATAdvancedOperator_H

#include "PersistentCell.h"
#include "CATDRepOperator.h"
#include "CATBoolean.h"

class CATCGMStream;
class CATlsoContext;
class CATPersistentOperator;
class CATAdvancedExtTopOperator;

/* 
------------------------------------------------------------------------------
--------------------------!!! CAA Interface !!!-------------------------------
------------------------------------------------------------------------------
Be very carreful, this has a CAA Interface created in 2013 by SolidWorks
 GMOperatorsInterfaces\PublicInterfaces\CATICGMAdvancedOperator.h
Don't forget : @nodoc @nocgmitf
------------------------------------------------------------------------------
*/


class ExportedByPersistentCell  CATAdvancedOperator : public CATDRepOperator
{
  CATCGMVirtualDeclareClass(CATAdvancedOperator);

public:

  /**
  * @nodoc @nocgmitf
  * Destructor
  */
  virtual ~CATAdvancedOperator();


  /** @nodoc @nocgmitf */
  virtual CATPersistentOperator * GetAsPersistentOperator() const;
  /** @nodoc @nocgmitf */
  virtual CATAdvancedOperator   * GetAsAdvancedOperator() const;
  
protected:

  /**
  * @nodoc @nocgmitf
  * Official Constructor 1
  */
  CATAdvancedOperator(CATGeoFactory * iFactory, CATTopData * iTopData, CATAdvancedExtTopOperator *iImpl);

  /** @nodoc @nocgmitf */
  CATAdvancedExtTopOperator * GetAdvancedOperatorImpl() const;

  // -----------------------------------------
  // RunOperator
  // -----------------------------------------
  /** @nodoc @nocgmitf */
  virtual int RunOperator();

  
  // for CGMReplay
  // @nocgmitf
  virtual void Dump(CATCGMOutput& os);
  
  // for CGMReplay Only
  // @nocgmitf
  virtual void DumpOutput(CATCGMOutput& os);

private :
    /** Forbiden call - copy contructor  **/
  // @nodoc @nocgmitf
  CATAdvancedOperator (const CATAdvancedOperator &);
  /** Forbidden call : Equal operator  **/
  // @nodoc @nocgmitf
  CATAdvancedOperator & operator=(const CATAdvancedOperator &);

};

#endif
