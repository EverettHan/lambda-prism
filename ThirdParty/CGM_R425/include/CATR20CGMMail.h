#ifndef CATR20CGMMail_H
#define CATR20CGMMail_H
/**
* @quickReview NLD 08:12:19
* @fullReview NLD CPL 08:02:05
*/
// COPYRIGHT DASSAULT SYSTEMES 2008
//=============================================================================
//
// _CATR20CGMMail : CGM Mail stack to bypass data transmission through methods not available before R20
//
//=============================================================================
// 23/01/09 NLD Creation
//              CATR20CGMMail_ConfigForFunctionX
//              CATR20CGMMail_ConfigForComputeOptimalImageFunctionX
//=============================================================================
#include <CATMathematics.h>
#include <CATFedEx.h>


// static shared mail box
extern ExportedByCATMathematics CATFedEx _CATR20CGMMail ;

// mail identifiers (to be continued when needed)
typedef enum
  {
   CATR20CGMMail_ConfigForFunctionX=1,                   //NLD230109
   CATR20CGMMail_ConfigForComputeOptimalImageFunctionX   //NLD230109
  } CATR20CGMMail_Ident ;

#endif
