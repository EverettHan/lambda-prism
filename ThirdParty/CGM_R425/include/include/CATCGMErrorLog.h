#ifndef CATCGMErrorLog_h
#define CATCGMErrorLog_h
/* -*-C++-*-*/
//==========================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//
//==========================================================================
/**
 * Class allowing to log CGM Errors
 */


#include "CATCGMKernel.h"
class CATCGMOutput;
class CATError;


class ExportedByCATCGMKernel CATCGMErrorLog 
{
public :
  // static access 
  //-----------------------------------
  //  Get() returns NULL if not opened
  //-----------------------------------
  static void            Open();
  static void            Close();
  static CATCGMErrorLog* Get();

  void Log(const char* iOpName, CATError* iErr = 0);

  void Print(CATCGMOutput&);

protected :

  CATCGMErrorLog();
  virtual ~CATCGMErrorLog();

private :
  static CATCGMErrorLog *  _Log;
  void *                   _InternalData;  
};

#endif

