#ifndef CATCGMThread_h
#define CATCGMThread_h
/* -*-C++-*-*/
//==========================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//
//==========================================================================
/**
 * Interface defining class for multi thread operations
 *
 *  Derive this class and write the Run method
 */


#include "ExportedByCATMathStream.h"

class ExportedByCATMathStream CATCGMThread
{
public :
  CATCGMThread();
  virtual ~CATCGMThread();

  virtual int Run() = 0;
};

#endif

