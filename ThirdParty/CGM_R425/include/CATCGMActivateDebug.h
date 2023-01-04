#ifndef CATCGMActivateDebug_H
#define CATCGMActivateDebug_H
// COPYRIGHT DASSAULT SYSTEMES  1999

#include "ExportedByCATMathStream.h"
#include "CATCGMNewArray.h"
#include "CATBaseUnknown.h" 

class CATCommand;
class CATTrace;
class CATActivateDebug;

//
// This class gives an access to interactive debug without needding to
// have a build-time pre-requisite on the Dialog and Visualization frameworks.
// It is a simple envelop of CATInteractiveDebug of the Debug Framework.
// 
// The interactive debug services are triggered if the two following conditions
// are fulfilled:
//    * the static variable InteractiveDebugMode is set to TRUE.
//    * the library of interactive debug is available. This library
//      is CAT3DControl, that insures the bridge to the real debug services.  
//
class ExportedByCATMathStream CATCGMActivateDebug
{
public:
  CATCGMActivateDebug(char* iCPGroupName); 
  virtual ~CATCGMActivateDebug(); 

  void SetDelActivateDebug(CATBoolean iDel);
  int CheckPoint(char *iCPName, CATCommand *iCurrentActiveCmd=NULL);

  void Show   (void* obj, int OnlyThisOne=0);
  void NoShow (void* obj);

  void PutColor(void* obj, int red,int green, int blue);

  static int SetDebugMode(int Mode);
  static int GetDebugMode();

  /** @nodoc */
  // CPT on May 7th 2012: no more CATCGMNewClassArrayDeclare;

private:
  static CATTrace   *_DebugMode;   // Variable allowing  or not the debug mode
  static int         _NumberOfDebug;
  CATActivateDebug  *_ActivateDebug;     
  char              *_GroupName;
  CATBoolean         _DelActivate;
};

#endif
