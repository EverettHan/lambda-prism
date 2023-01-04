/* -*-c++-*- */
#ifndef CATCGMDumpThrow_h
#define CATCGMDumpThrow_h
// COPYRIGHT DASSAULT SYSTEMES  1999
//  
#include "CATMathematics.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATError;

ExportedByCATMathematics void CATCGMDumpThrow(const char *loc, int line,  ostream* trueOutput, CATError *iError);

#endif

