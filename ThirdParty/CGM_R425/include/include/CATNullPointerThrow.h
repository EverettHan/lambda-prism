#ifndef CATNullPointerThrow_H
#define CATNullPointerThrow_H
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 *  DEPRECATED, You must use CATThrowForNullPointer.h 
 *  Not Integrated in mkCheckSource ...
 */
#include "CATThrowForNullPointer.h"
#include "CATCGMBuildDebug.h"

#if defined ( CATCGMBuildDebug )


#define CATNullPointerThrow( pointer )  \
  if ( ((void *)pointer) == ((void *)NULL) ) { CATCGMThrowForNullPointer(__FILE__,__LINE__); return; }
#define CATNullPointerThrowReturnValue( pointer, ReturnValue )  \
  if ( ((void *)pointer) == ((void *)NULL) ) { CATCGMThrowForNullPointer(__FILE__,__LINE__); return ReturnValue; }
#define CATThrowOnNullPointer(ifile,iline) CATCGMThrowForNullPointer(ifile,iline)

#else

#define CATNullPointerThrow( pointer )  \
  if ( ((void *)pointer) == ((void *)NULL) ) { CATCGMThrowForNullPointer(NULL,0); return; }
#define CATNullPointerThrowReturnValue( pointer, ReturnValue )  \
  if ( ((void *)pointer) == ((void *)NULL) ) { CATCGMThrowForNullPointer(NULL,0); return ReturnValue; }
#define CATThrowOnNullPointer(ifile,iline) CATCGMThrowForNullPointer(NULL,0)

#endif

#endif





