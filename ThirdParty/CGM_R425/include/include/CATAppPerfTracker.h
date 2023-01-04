/* -*-C++-*- */

#ifndef CATAppPerfTracker_H
#define CATAppPerfTracker_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier

DESCRIPTION  : class to analyse performance
               
=============================================================================
*/
// --------------------------------------------------------
//  SAMPLE OF CODE
// --------------------------------------------------------
//
// Sample  - 
// -----------------------------
//RunOperator()
//{
//  CATAPTStart("myOperator")
//
//  ...............
//
//  CATAPTEnd(TRUE);
//}
// --------------------------------------------------------

#include "CATPersistentCell.h"

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Beginning of the run
//ipName : operator name
ExportedByPersistentCell void CATAPTStart(const char * ipName);
//The end of the run
//iIsOK : is the operator successfull or not
ExportedByPersistentCell void CATAPTEnd(CATBoolean iIsOK);

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Give environment variable
ExportedByPersistentCell void CATAPTEnv(const char * ipName);
//Give a message
ExportedByPersistentCell void CATAPTMsg(const char * ipName);

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//To activate performance tracker
ExportedByPersistentCell void       CATAPTSetActivation(CATBoolean iActivation);
//To know if tracker has been activated
ExportedByPersistentCell CATBoolean CATAPTGetActivation();

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Set output (console or file)
ExportedByPersistentCell void       CATAPTSetConsole(CATBoolean iConsole);
//Get output (console or file mode)
ExportedByPersistentCell CATBoolean CATAPTGetConsole();

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Get current Level
ExportedByPersistentCell int        CATAPTGetLevel();

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Set depth
ExportedByPersistentCell void       CATAPTSetDepth(int iDepth);
//Get depth
ExportedByPersistentCell int        CATAPTGetDepth();


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// GetCurrentfTime
ExportedByPersistentCell void GetCPUTime(CATULONG32 & oCPUTime);
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//CheckMultirun
ExportedByPersistentCell CATBoolean CheckMultirun();

class CATAppPerfTracker
{
public:
  //@nocgmitf
  static void GetCurrentfTime(CATULONG32 & oCPUTime, CATULONG32 & oElapsedTime);
  //@nocgmitf
  static void InitOutput();
  //@nocgmitf
  static void InitNameList();
  //@nocgmitf
  static void InitCPUList();
  //@nocgmitf
  static void InitElapsedList();
  //@nocgmitf
  static void WriteInOutput();
  //@nocgmitf
  static void CleanVariables();
  //@nocgmitf
  static void DumpOther(CATULONG32 iElapsedTime, CATULONG32 iDurElapsedOther, CATULONG32 iCPUTime, CATULONG32 iDurOther, int iLevel, CATUnicodeString * iDebug);
  //@nocgmitf
  static void DumpTime(CATULONG32 iElapsedTime, CATULONG32 iDurElapsedOther, CATULONG32 iCPUTime, CATULONG32 iDurOther, CATBoolean iIsOK, const char * iName, int iLevel);
  //@nocgmitf
  static void DumpStandardEnv();
  //@nocgmitf
  static void DumpHeader();
#ifdef WIN32
  //@nocgmitf
  static CATLONG64 GetTicks();
  //@nocgmitf
  static double GetFreq();
#endif
};

#endif
