#ifndef CATWakeUpEnv_h
#define CATWakeUpEnv_h

// COPYRIGHT DASSAULT SYSTEMES 1999
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATBoolean.h"
#include "CATHashDico.h"
#include "ExportedByCATMathStream.h"

/**
 * Conditional management of Interactive WakeUp of Data.
 *   Prerequisite :  
 *     environement variable  : set CATWakeUp=GM
 *     runtime context        : InteractiveApplication
 *   Behavior Impact :
 *     for GM, In case of doubtfull data (external behavior) 
 */
class ExportedByCATMathStream CATWakeUpEnv 
{
public:
 
  /**
   * Check if enables.
   */
  static void * IsEnable(const char * iSpecificDomain);
 
  /**
   * Disable in case of specific conditions.
   */
  static void IrreversibleDisable(const char * iSpecificDomain);
 

private :
 
  /**
   * Data 
   */
  static CATBoolean     _IsInitialised;
  static CATHashDico *  _Enabled;
  static void           Initialise();
  static void        *  _DEFAULT; 

};
 
 

#endif

