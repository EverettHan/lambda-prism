#ifndef CATR19CGMMail_H
#define CATR19CGMMail_H
/**
* @quickReview NLD 08:12:19
* @fullReview NLD CPL 08:02:05
*/
// COPYRIGHT DASSAULT SYSTEMES 2008
//=============================================================================
//
// _CATR19CGMMail : CGM Mail stack to bypass data transmission through methods not available before R19
//
//=============================================================================
// 04/02/08 NLD Creation
//              CATR19CGMMail_ScaleOptionForSolvePolynom
//              CATR19CGMMail_ScaleForMathematics
// 12/02/08 NLD CATR19CGMMail_ScaleOptionForSolvePolynom renomme CATR19CGMMail_ScaleOptionForSolveNewton
//              Ajout CATR19CGMMail_ScaleOptionForMinimizeNewton
// 12/02/08 NLD Ajout CATR19CGMMail_ScaleOptionForComputeOptimalImageXY
// 13/02/08 NLD Ajout CATR19CGMMail_ScaleOptionForComputeOptimalImageX
// 18/02/08 NLD Ajout CATR19CGMMail_ScaleOptionForIsMononotonePolynomX
// 19/12/08 NLD Ajout CATR19CGMMail_ConfigForMathematics
//=============================================================================
#include <CATMathematics.h>
#include <CATFedEx.h>


// static shared mail box
extern ExportedByCATMathematics CATFedEx _CATR19CGMMail ;

// mail identifiers (to be continued when needed)
typedef enum
  {
   CATR19CGMMail_ScaleOptionForSolveNewton=1, //NLD040208
   CATR19CGMMail_ScaleForMathematics,         //NLD070208
   CATR19CGMMail_ScaleOptionForMinimizeNewton, //NLD120208
   CATR19CGMMail_ScaleOptionForComputeOptimalImageXY, //NLD120208
   CATR19CGMMail_ScaleOptionForComputeOptimalImageX, //NLD130208
   CATR19CGMMail_ScaleOptionForIsMononotonePolynomX, //NLD180208
   CATR19CGMMail_ConfigForMathematics//NLD191208
  } CATR19CGMMail_Ident ;

#endif
