#ifndef _DSYSYSUTB_H
#define _DSYSYSUTB_H
/************************************************************************/
/* Documentation                                                        */
/************************************************************************/
/*
  NOTE: This header file is deprecated. You should now include the header
        file "UTB.h" for your unit test and use the new macro format
        "__UTB_xxx" instead of "__DSY_SYS_UTB_xxx". The behavior remain
         unchanged.
*/
/************************************************************************/
/* Defines                                                              */
/************************************************************************/

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "UTB.h"

/************************************************************************/
/* Macros definitions                                                   */
/************************************************************************/

#define ExportedByDSYSysUTB           ExportedByUTB

#define __DSY_SYS_UTB_MAIN_BEGIN      __UTB_MAIN_BEGIN
#define __DSY_SYS_UTB_MAIN_END        __UTB_MAIN_END

#define __DSY_SYS_UTB_ARGIV           __UTB_MAIN_ARGIV
#define __DSY_SYS_UTB_ARGC            __UTB_MAIN_ARGC
#define __DSY_SYS_UTB_ARGV            __UTB_MAIN_ARGV

#define __DSY_SYS_UTB_CHECK           __UTB_MAIN_CHECK
#define __DSY_SYS_UTB_CHECK_AND_GO    __UTB_MAIN_CHECK_AND_GO
#define __DSY_SYS_UTB_CHECK_TRUE      __UTB_MAIN_CHECK_TRUE
#define __DSY_SYS_UTB_CHECK_FALSE     __UTB_MAIN_CHECK_FALSE

#define __DSY_SYS_UTB_CHECK_IF        __UTB_MAIN_CHECK_IF
#define __DSY_SYS_UTB_CHECK_ELSE      __UTB_MAIN_CHECK_ELSE
#define __DSY_SYS_UTB_CHECK_ENDIF     __UTB_MAIN_CHECK_ENDIF

/* Deprecated */
#define __DSY_SYS_UTB_PRINT           __UTB_PRINT_INTERNAL

#endif  // _DSYSYSUTB_H
