/* -*-c++-*- */
#ifndef CATMacBuildCGM_CATCGMBOAObject_H
#define CATMacBuildCGM_CATCGMBOAObject_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// EMBEDDED dedicated to GeometricObjectsCGM\ProtectedInterfaces\CATMacBuildCGM
//
//=============================================================================
// Oct. 01   TIE BOA                                                 L. Rageul
//     
//=============================================================================
//    
// Notes :
//
//   Un CreateTIExxx cree le tie avec m_cRef=1 (compteur de ref System)
//   Les compteurs sur implementation (eventuellement extension) sont mis a jour
//    
//    
//    
//=============================================================================

#if defined ( CATCGMBOAObject ) 

#define CATMacBuildCGM( implementation , interfac ) 

#if defined ( CATCGMBOAObject ) 
#define TIECGM(XXX,YYY)   TIE_CGM_DEFINE(XXX,YYY)
#else
#define TIECGM(XXX,YYY)   TIE_##XXX(YYY)
#endif

#endif


#endif
