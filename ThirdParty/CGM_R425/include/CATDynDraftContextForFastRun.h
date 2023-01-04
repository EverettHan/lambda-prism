#ifndef CATDynDraftContextForFastRun_h
#define CATDynDraftContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Jan. 10  Creation                                   JJ3
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATDynDraftContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATDynDraftContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATDynDraftContextForFastRun(); // -> delete can't be called
};

#endif /* CATDynDraftContextForFastRun_h_ */
