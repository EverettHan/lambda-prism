#ifndef CATHOTMAILCGMR18SP4_H
#define CATHOTMAILCGMR18SP4_H
// COPYRIGHT DASSAULT SYSTEMES 2008
//=============================================================================
//
// _CATHotMailCGMR18SP4 : CGM Mail stack to bypass data transmission through methods for CGM hot fix R18SP4
//
//=============================================================================
// 11/02/08 NLD Creation
//=============================================================================
#include <CATMathematics.h>
#include <CATFedEx.h>


// static shared mail box
extern ExportedByCATMathematics CATFedEx _CATHotMailCGMR18SP4 ;

// mail identifiers (to be continued when needed)
// (and to be renamed if no care for build impact)
typedef enum
  {_CATHotMailCGMR18SP4_NoId=0,
   _CATHotMailCGMR18SP4_Id1, //NLD110208
   _CATHotMailCGMR18SP4_Id2, //NLD110208
   _CATHotMailCGMR18SP4_Id3, //NLD110208
   _CATHotMailCGMR18SP4_Id4, //NLD110208
   _CATHotMailCGMR18SP4_Id5, //NLD110208
   _CATHotMailCGMR18SP4_Id6, //NLD110208
   _CATHotMailCGMR18SP4_Id7, //NLD110208
   _CATHotMailCGMR18SP4_Id8, //NLD110208
   _CATHotMailCGMR18SP4_Id9 //NLD110208
  } _CATHotMailCGMR18SP4_Ident ;

#endif
