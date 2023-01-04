#ifndef CATTopPolyMorphingContextFastRun_H
#define CATTopPolyMorphingContextFastRun_H
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
// 
//==========================================================================
// April. 2022  Creation                                              QF2
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATTopPolyMorphingContextFastRun : public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATTopPolyMorphingContextFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATTopPolyMorphingContextFastRun(); // -> delete can't be called
};

#endif /* CATTopPolyMorphingContextFastRun_h_ */
