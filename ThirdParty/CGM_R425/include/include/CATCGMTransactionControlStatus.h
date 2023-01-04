/**
* @COPYRIGHT DASSAULT SYSTEMES 2003
*/
/* -*-c++-*- */
//=============================================================================
// Aug. 03 FatEdgesAtEnd, NbFatEdges                                      HCN
// Dec. 03 Controle des NonPersistentUnusedObjects                        HCN
//=============================================================================

#ifndef CATCGMTransactionControlStatus_H
#define CATCGMTransactionControlStatus_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
#include "ExportedByGeometricObjects.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "CATMathInline.h"

//---------------------------------------------------------------------------------------------
// Description des champs d'activation :
//---------------------------------------------------------------------------------------------
class ExportedByGeometricObjects CATCGMTransactionControlStatus
{
public :

  //---------------------------------------------------------------------------------------------
  // Life Cycle
  //---------------------------------------------------------------------------------------------
  INLINE CATCGMTransactionControlStatus();
  INLINE ~CATCGMTransactionControlStatus();
  INLINE CATCGMTransactionControlStatus(const CATCGMTransactionControlStatus& iOneOf); 
  INLINE CATCGMTransactionControlStatus& operator =(const CATCGMTransactionControlStatus& iOneOf);
  
  //---------------------------------------------------------------------------------------------
  // Contents
  //---------------------------------------------------------------------------------------------
  unsigned int	VerboseControl        :  1;
  
  unsigned int	InputKnotsWeightAtEnd :  1;
  unsigned int	OuputKnotsWeightAtEnd :  1;
  unsigned int	GeometricalLeaks      :  1;
  unsigned int  FatEdgesAtEnd         :  1;
  unsigned int  UnusedObjectsAtEnd    :  1;
  
  unsigned int	RFU                   : 26;
  
  
  //---------------------------------------------------------------------------------------------
  // Controle du Nombre d'Arcs/Patchs Cumules des Courbes/Surfaces de la modelisation d'Input
  // Apres execution du scenario (contexte stabilisation des Extrapolation excessives)
  //---------------------------------------------------------------------------------------------
  int NbInputKnotstAtEnd;
  
  //---------------------------------------------------------------------------------------------
  // Controle du Nombre d'Arcs/Patchs Cumules des Courbes/Surfaces de la modelisation d'Output
  // (contexte stabilisation des Extrapolation excessives)
  //---------------------------------------------------------------------------------------------
  int NbOuputKnotsAtEnd;
  
  //---------------------------------------------------------------------------------------------
  // Controle du Nombre d'Objets geometriques  :
  //    generes au cours de la Transaction encore en vie dans la Factory geometrique
  //    ne participant pas directement ou indirectement a la modelisation finale
  //---------------------------------------------------------------------------------------------
  int NbGeometricalLeaks;

  //---------------------------------------------------------------------------------------------
  // Controle du Nombre d'edges dont l'edgecurve contient des curves inutiles
  //---------------------------------------------------------------------------------------------
  int NbFatEdges;

  //---------------------------------------------------------------------------------------------
  // Controle du Nombre de NonPersistentUnusedObjects
  //---------------------------------------------------------------------------------------------
  int NbUnusedObjects;

};



//------------------------------------------------------------------------
// LifeCycle 
//-----------------------------------------------------------------------
INLINE CATCGMTransactionControlStatus::CATCGMTransactionControlStatus()
{
  memset( (void *) this,  0 , sizeof(CATCGMTransactionControlStatus) );
}

INLINE CATCGMTransactionControlStatus::~CATCGMTransactionControlStatus()
{
}

INLINE CATCGMTransactionControlStatus::CATCGMTransactionControlStatus(const CATCGMTransactionControlStatus& tocopy)
{
  memcpy ( (void *) this, & tocopy, sizeof(CATCGMTransactionControlStatus) );
}

INLINE CATCGMTransactionControlStatus& CATCGMTransactionControlStatus::operator =(const CATCGMTransactionControlStatus& tocopy)
{
  memcpy ( (void *) this, & tocopy, sizeof(CATCGMTransactionControlStatus) );
  return *this;
}





#endif
