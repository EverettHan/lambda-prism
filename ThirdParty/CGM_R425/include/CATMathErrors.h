#ifndef _CATMATHERRORS_INCLUDE
#define _CATMATHERRORS_INCLUDE
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************


// COPYRIGHT DASSAULT SYSTEMES  1999
/* Generated from CATMathErrors.msg on Tue Sep 29 15:15:06 1998
 */
typedef enum {

              MInENulDeterminant = 0x00020001u,
       MInEBadTransformationType = 0x00020002u,
          MInEColinearDirections = 0x00020003u,
                    MInENulValue = 0x00020004u,
               MInESingularPoint = 0x00020005u,
            MInEInvalidDimension = 0x00020006u,
                MInEInvalidIndex = 0x00020007u,
               MInEInvalidGetUse = 0x00020008u,
         MInEInvalidFunctionCall = 0x00020009u,
        MInEInvalidStartingPoint = 0x0002000au,
               MInEInvalidDomain = 0x0002000bu,
                MInEInvalidPoint = 0x0002000cu,
       MInEIllConditionnedSystem = 0x0002000du,
             MInEIdenticalPoints = 0x0002000eu,

           MIntEGetLimitEmptyBox = 0x00020001u,
             MIntEGetAffineSpace = 0x00020002u,
               MIntEEigenVectors = 0x00020003u

} MathematicsErrors;

#endif
