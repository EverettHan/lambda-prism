#ifndef CATReverseTopology_h
#define CATReverseTopology_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//  Transaction performante d'acces aux liens inverses topologiques
//==========================================================================
/*
    CATBody   *iBody;
    CATReverseTopologyBegin(marqueur,iBody) 
    {
       // ... 
    }
    CATReverseTopologyEnd(marqueur);
*/
//==========================================================================
// 
//  PERFO : Utilitaire pour les operateurs topologiques
//             qui veulent exploiter les liens inverses topologiques
//             sans avoir accrocher cette Topologie sous le Body
//             en cours de contruction intermediaire d'un CATBody
//
//==========================================================================
//  FONCTIONNALITES  : Les services d'analyse topologique
//    qui assouplissent leur condition d'emploi
//    pour obtenir ces liens inverses sont les suivants :
//
//      a) les methodes offertes sur CATTopObject (c'est a dire CATCell ou CATBody)
//    
//        a.1)   GetBoundedTopObjects
//
//        a.2)   IsBoundaryOfTopObject
//
//==========================================================================
//  RESTRICTIONS    : Contraintes imperatives a l'utilisation de cette plateforme :
//
//     1) On n'utilise que le Body specifie durant toute la transaction, 
//        Toute la topologie doit etre cree a partir du Body specifie
//        Une desactivation du Body provoquera une anomalie
//
//     2) Pas d'empilages de Transaction, seul l'operation qui genere
//         le Body indique est a meme dans son moteur d'identifier
//         la transation d'utilisation du Body
//
//     3) Attention aux objets intermediaires qui n'auraient pas ete nettoyes
//          par un Remove recursif
//
//==========================================================================
//
// Exemple d'analyse remontante sur la topologie
/*
      const  int    expectingBounded = 2;
      CATSide       boundedSide[expectingBounded];
      CATTopObject *boundedCells[expectingBounded];

      int nbComputedBounded = cxface->GetBoundedTopObjects(iBody, boundedCells,boundedSide,expectingBounded);
*/
//==========================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMTransaction.h"
#include "CATMathInline.h"

class CATBody;

//------------------------------------------------------------------
// Transaction performante d'acces aux liens inverses topologiques
//------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATReverseTopology : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static CATReverseTopology *Create(CATBody *iBody);

  CATCGMNewClassArrayDeclare;   

  virtual void Clean();
  INLINE CATBody  *GetBody() const;


protected:
  CATReverseTopology(CATBody *iBody);
  CATBody    *_Body;
};


//------------------------------------------------------------------
// Obtention du Body de contexte
//------------------------------------------------------------------
INLINE CATBody  *CATReverseTopology::GetBody() const
{
  return _Body ;
}

//------------------------------------------------------------------
// Encapsulation des macros de definition ..
//------------------------------------------------------------------
#define CATReverseTopologyBegin(marqueur,iBody)  \
  CATReverseTopology *volatile marqueur = CATReverseTopology::Create(iBody); \
CATTry  \
{  

#define CATReverseTopologyEnd(marqueur)  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
  CATRethrow; \
}  \
CATEndTry 


#endif

