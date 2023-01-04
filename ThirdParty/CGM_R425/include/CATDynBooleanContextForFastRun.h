#ifndef CATDynBooleanContextForFastRun_h
#define CATDynBooleanContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"
#include "CATDataType.h"

class CATCGMJournalList;

class ExportedByCATGMOperatorsInterfaces CATDynBooleanContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATDynBooleanContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATDynBooleanContextForFastRun(); // -> delete can't be called

};

#endif /* CATDynBooleanContextForFastRun_h_ */
