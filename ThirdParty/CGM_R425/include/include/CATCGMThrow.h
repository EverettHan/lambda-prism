/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 2001
// Pour Debug des Levees d'exception dans le contexte du Framework System 
//      a) build en optimise
//      b) avec code Source inaccessible 
// 
// --> Point d'arret au Debugger "catcgmthrow"   (a definir comme "longjmp" sous Sun)
//
//==========================================================================
// 17/11/09 NLD Ajout CATCGMThrowCount
// 29/09/10 NLD Ajout CATCGMThrowCount_SecuredCatch et CATCGMThrowCount_IncSecuredCatch
// 02/03/21 NLD Ajout CATCGMThrowCount_UnSecuredCatch et CATCGMThrowCount_IncUnSecuredCatch
//              (pour comptage direct et non plus par différence)
//==========================================================================

#ifndef CATCGMThrow_H
#define CATCGMThrow_H

#include "CATMathematics.h"
#include "CATErrorMacros.h"
#include "CATCGMBuildDebug.h"

ExportedByCATMathematics CATError * CATCGMThrowFunction(CATError *iError, char *iFile, int iLine); 

#if defined ( CATCGMBuildDebug )
#define CATCGMThrow(iError) CATThrow( CATCGMThrowFunction(iError,__FILE__,__LINE__) )
#else
#define CATCGMThrow(iError) CATThrow( CATCGMThrowFunction(iError,NULL,0) )
#endif


//----------------------------------------------------------------------------------------------
// Comptage
//----------------------------------------------------------------------------------------------
// comptage du nombre de throw                            (CATCGMThrowCount_Throw)
// comptage du nombre de creations d'erreurs              (CATCGMThrowCount_Create)
// comptage du nombre de destructions d'erreurs           (CATCGMThrowCount_Release)
// comptage du nombre de creations de chainages d'erreurs (CATCGMThrowCount_CreateChain)
// comptage du nombre de catch securises                  (CATCGMThrowCount_SecuredCatch)
// comptage du nombre de catch non securises              (CATCGMThrowCount_UnSecuredCatch)
// autres fonctionnalites
// increment du nombre de catch securises                 (CATCGMThrowCount_IncSecuredCatch)
// increment du nombre de catch non securises             (CATCGMThrowCount_IncUnSecuredCatch)
//----------------------------------------------------------------------------------------------
typedef enum{CATCGMThrowCount_Throw            = 0,
             CATCGMThrowCount_Create           ,
             CATCGMThrowCount_Release          ,
             CATCGMThrowCount_CreateChain      ,
             CATCGMThrowCount_SecuredCatch     ,
             CATCGMThrowCount_IncSecuredCatch  ,
             CATCGMThrowCount_UnSecuredCatch   ,
             CATCGMThrowCount_IncUnSecuredCatch
            } CATCGMThrowCount_Type;
ExportedByCATMathematics int CATCGMThrowCount(CATCGMThrowCount_Type iMode=CATCGMThrowCount_Throw);


#endif

