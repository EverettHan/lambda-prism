#ifndef CATCXDebugReplay_H
#define CATCXDebugReplay_H
//-----------------------------------------------------------------------------
// Tiny interpreter of Debug Tools ..
//=============================================================================
// Nov. 03 CreateEnvironmentVariableForCell(...) devient
//         CreateEnvironmentVariableForEntity(...)                        HCN
// Feb. 04 Parametre iCopyPasteMode pour Datumiser(...)                   HCN
//=============================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATICGMStreamFactory.h"
#include "CATCGMOutput.h"
#include "CATBoolean.h"
#include "CATError.h"

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

 

#define CATCXDebugReplay_DumpBefore          0x00000001
#define CATCXDebugReplay_CheckInput          0x00000002
#define CATCXDebugReplay_VisuDataBefore      0x00000004
#define CATCXDebugReplay_Run                 0x00008000
#define CATCXDebugReplay_DumpAfterRun        0x80000010
#define CATCXDebugReplay_CheckOutput         0x80000020
#define CATCXDebugReplay_VisuDataAfter       0x80000040
#define CATCXDebugReplay_DumpReference       0x80000100
#define CATCXDebugReplay_ValidateReference   0x80000200
#define CATCXDebugReplay_ALL                 0xFFFFFFFF



///---------------------------------------------------------------------
///  ReplayFull : return number of anomalies detected
///---------------------------------------------------------------------  
class ExportedByCATTopologicalObjects CATCXDebugReplay 
{
public : 

  static int ReplayFull( CATCGMOutput &os, CATICGMStreamFactory *iReplay, 
                          HRESULT &ioRCRun,   const CATULONG32  ToReplay = CATCXDebugReplay_ALL );

private :
  static void DumpError(const char Context[], CATError* err, CATCGMOutput &os);

};
 

#endif
