#ifndef BOO_VERSIONNING_FUNCTION_H
#define BOO_VERSIONNING_FUNCTION_H

/**
* Tool to modify the value of a versioning flag even when:
* > CATDevelopmentStage is not set
* > the flag is not defined yet
*
* To use it: (exemple with flag CGM_Versionning_MyFlagName)
*
* On top of each cpp file using the flag, put:
*   #include "BOO_VERSIONNING_FUNCTION.h"
*   #ifndef CGM_Versionning_MyFlagName
*   #define CGM_Versionning_MyFlagName 32000
*   #endif
*   BOO_VERSIONNING_FUNCTION(MyFlagName);
* (the first 3 lines are useless if the flag is already defined)
*
* Inside code, test the flag in this way:
*   if (LevelToExecute >= BOO_Versionning_MyFlagName())
*
* Modify the value of the flag by setting:
*   set BOO_Versionning=MyFlagName=7500   <- the flag will have value 7500
*   set BOO_Versionning=MyFlagName=-1     <- the flag will have BSF value
*
* Several flags can be set at the same time:
*   set BOO_Versionning=FlagAlpha=7500,FlagBeta=-1,FlagGamma=32000
*
* In ODT shell, do not forget to concatenate with existing values:
*   export BOO_Versionning="FlagAlpha=7500,"$BOO_Versionning
*   export BOO_Versionning="FlagBeta=-1,"$BOO_Versionning
*   export BOO_Versionning="FlagGamma=32000,"$BOO_Versionning
* Please notice that the "$BOO_Versionning" part must come **AFTER** the locally defined flags:
* in this way the flags can be modified from outside.
* The reason is that if a key is defined more than once,
* each time with a different value, the last occurence is taken into account.
*
*/

#include "CATMathInline.h"
#include "ExportedByCATMathStream.h"

// -2 if key not defined, bsflevel if key=-1
ExportedByCATMathStream int Get_BOO_Versionning_CGMLevel(const char * iSpecificKey);

#define BOO_VERSIONNING_FUNCTION(VARNAME) \
static INLINE int BOO_Versionning_##VARNAME() \
{ \
  static int ForcedLevel = Get_BOO_Versionning_CGMLevel(#VARNAME); \
  return ((-2 == ForcedLevel) ? CGM_Versionning_##VARNAME : ForcedLevel); \
}

#endif
