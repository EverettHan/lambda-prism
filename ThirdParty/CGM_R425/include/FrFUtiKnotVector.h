// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// FrFUtiPoint :
// Declaration of utilities on Points used in the FreeFormOperators FW
//
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
// 09/97  Creation                                 RLA
// 09/98  Modif.  (Gestion des VN extrapoles)      NDN
//=============================================================================
#ifndef FrFUtiKnotVector_H 
#define FrFUtiKnotVector_H 

class CATKnotVector;
#include "YP00IMPL.h"
#include "CATDataType.h"


//-----------------------------------------------------------------
//calcul de la r_ieme valeur nodal (vn etendu ou se trouve le jpol 
//      r tel que vn(r)=<vn_nw(jpol)<vn(r+1)
// Attention tableaux commencant par l indice 1 
//-----------------------------------------------------------------
ExportedByYP00IMPL
CATLONG32 Calcul_r_pour_jpol(const CATLONG32 &ndeg, const CATLONG32 &nbsvn,
                        const CATLONG32 *mult,const CATLONG32 &jpole );
//----------------------------------------------
//calcul de la j_ieme valeur nodal (vn etendu ) 
//----------------------------------------------
ExportedByYP00IMPL
double Knot_etendu(const CATLONG32 &ndeg, const CATLONG32 &nbsvn,
                        const double *vn, const CATLONG32 *mult,const CATLONG32 &jpol );
//----------------------------------------------------------------------------
//calcul de r ( de vn etendu) correspondant a la i_noeud_cur valeur nodal simple
// i_noeud_cur <  nbsvn control fait par l utisateur
//----------------------------------------------------------------------------
ExportedByYP00IMPL
 CATLONG32 r_Knot_etendu(const CATLONG32 &i_noeud_cur, const CATLONG32 *mult ); 

/*
//----------------------------------------------------------------------------
//Ces deux methodes servent a retirer/remettre-en-place les arcs negatifs
//des vecteurs nodaux de surfaces extrapolees
//----------------------------------------------------------------------------
ExportedByYP00IMPL
 void UnShiftKnotVector(const CATKnotVector * OldKnotVector,
			CATKnotVector * KnotVectorToBeChanged);

ExportedByYP00IMPL      
 void ReShiftKnotVector(CATLONG32 Offset,CATKnotVector * KnotVectorToBeChanged);
*/

#endif


