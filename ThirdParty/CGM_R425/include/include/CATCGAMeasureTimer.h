#ifndef CATCGAMeasureTimer_H
#define CATCGAMeasureTimer_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//  small tools legacy from tessellation utilities
//    offered at lower level for architecture purpose
//  may be enhance package is available from System harware/operating system abstraction
//     so do not forget to contact single system image or PCS actors
//-------------------------------------------------------------------------------------------------
#include "CATCGATimer.h"
#include "CATMathInline.h"

class ExportedByCATMathematics CATCGAMeasureTimer : public CATCGATimer
{
public:
  INLINE CATCGAMeasureTimer()  : _NbErrors(0), CATCGATimer(TRUE) {};


  CATCGAMeasureTimer (const CATCGAMeasureTimer &);          
  CATCGAMeasureTimer& operator=(const CATCGAMeasureTimer&);  


  CATULONG64           _NbErrors;

};


#endif
