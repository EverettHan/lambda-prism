
#ifndef CATDisco3DDefine_H
#define CATDisco3DDefine_H

#include "CATCGMOutput.h"

//#define DLR6__DUMP_EXPANDVOL_DEBUG

#define DISCO_SHELL_DEBUG

#define DISCO_SHELL_DUMP_DETAIL_MATTER_INSIDE
#define DISCO_SHELL_DUMP_DETAIL_IS_CONTAINED


/******* DEFINE for temporary behavior (to test operator step by step) ******/

//#define DEFINE_OLDALGO_FOR_COMPUTEAPPARTENANCE
//#define DEFINE_DISCO3D_VOLUMIC_CONNECTORS

#define SORT_CALLBACKS_INPUT_FOR_DUMP
//#define NCGM_DEBUG_DUMP_DOMAINS
//#define NCGM_DEBUG_EXPORT_RESULT_TOPO


/******* DEFINE for debug export ******/

//////////////////////////////////
//
// Macro to activate : DLR6__DISCO3D_DEBUG_BUILD_EXISTING_CELLS
// in files :
//
// - GMModelInterfaces\ProtectedInterfaces\CATPGMDisconnectGateway.h
// - GMModelInterfaces\ProtectedInterfaces\CATDisconnectEngine.h
//
//////////////////////////////////


/******* End - DEFINE for temporary behavior (to test operator step by step) ******/


#define PRINT_DEF(x) \
  cgmout << #x << cgmendl

#define PRINT_NO_DEF(x) \
  cgmout << "        // NO : " << #x << cgmendl

INLINE void PrintDisco3DDefines()
{
  cgmout << cgmendl << cgmendl;
  cgmout << "***********************************" << cgmendl;
  cgmout << "*****     LIST OF DEFINES     *****" << cgmendl;
  cgmout << "***********************************" << cgmendl;
  cgmout << cgmendl;

#ifdef ADD_MANUAL_CALL_COMPATIBLE
  PRINT_DEF(ADD_MANUAL_CALL_COMPATIBLE);
#else
  PRINT_NO_DEF(ADD_MANUAL_CALL_COMPATIBLE);
#endif;

}


#endif // CATDisco3DDefine_H
