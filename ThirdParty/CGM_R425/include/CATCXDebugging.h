#ifndef CATCXDebugging_h
#define CATCXDebugging_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//      PCS integrated scalable analysis thanks to empty Batch (main executable) 
//      with first step of dedicated dynamic library loading
//   see CATGemODT sample ....
//==========================================================================

extern "C" { typedef int CATCXDebuggingMain(int argc, char ** argv); }  

#include "CATBoolean.h"
/**
* @nodoc
*/
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

extern "C" { typedef int CATCXDebugging(istream &inputText, ostream &outputText, ostream &errorText, CATBoolean iForMainOfODT); }  
   
#endif

