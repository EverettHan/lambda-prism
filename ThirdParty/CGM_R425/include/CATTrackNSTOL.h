#ifndef CATTrackNSTOL_H
#define CATTrackNSTOL_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2007
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************
// 
// DESCRIPTION : track (transparent) des utilisations directes des tolerances sans scale
//
// 20/02/07 NLD Creation de FrFTrackNSTOL
// 29/03/07 NLD Generalisation, creation de CATTrackNSTOL
// 16/01/08 NLD Activation #define CATTrackNSTOLActivation
// 16/05/08 NLD Ajout CATHardTol()
//=============================================================================
// Methodologie d'utilisation: activer le #define qui suit
// et ne recompiler que les frameworks dans lesquels on veut faire du comptage
#define CATTrackNSTOLActivation "A n'activer que pour test; cout supplementaire du aux appels de fonctions"
//
#ifdef CATTrackNSTOLActivation
#include <YN000MAT.h> 

//
// General track function
// ----------------------
extern "C" const void ExportedByYN000MAT CATFunctionNSTOL(double iTol);

//
// CATEpsilon & family
// -------------------
extern "C" const double ExportedByYN000MAT CATFunctionEpsilon() ;
#define CATEpsilon CATFunctionEpsilon()
extern "C" const double ExportedByYN000MAT CATFunctionSqrtEpsilon() ;
#define CATSqrtEpsilon CATFunctionSqrtEpsilon()
extern "C" const double ExportedByYN000MAT CATFunctionSquareEpsilon() ;
#define CATSquareEpsilon CATFunctionSquareEpsilon()
//
// CATEpsg  & family
// -----------------
extern "C" const double ExportedByYN000MAT CATFunctionEpsg() ;
#define CATEpsg CATFunctionEpsg()
extern "C" const double ExportedByYN000MAT CATFunctionSqrtEpsg() ;
#define CATSqrtEpsg CATFunctionSqrtEpsg()
extern "C" const double ExportedByYN000MAT CATFunctionSquareEpsg() ;
#define CATSquareEpsg CATFunctionSquareEpsg()
//
// Hard tolerances
// ---------------
extern "C" const double ExportedByYN000MAT CATHardTol(double iTol) ;
//
// Summary for all tolerances
// --------------------------
extern "C" ExportedByYN000MAT int CATTrackNSTOLSummary(int iTrace=1) ;

#endif
#endif
