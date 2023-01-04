#ifndef CATCGMDelayingEquationsLifeCycle_h
#define CATCGMDelayingEquationsLifeCycle_h
/* -*-C++-*-*/
//========================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//  Dedie aux services d'analyses (CheckUp Analyseur des Extrapolations
//  Transaction pour eviter les multiples ouvertures/fermetures d'Equations sur la meme Courbe/Surface
//========================================================================================================
/*
    CATCGMDelayingEquationsLifeCycleBegin(marqueur,iEstimatedSize) 
    {
       // ... 
    }
    CATCGMDelayingEquationsLifeCycleEnd(marqueur);
*/
//==========================================================================
#include "CATGeometricObjects.h"
#include "CATCGMTransaction.h"

class CATCGMCountHashTable;
class CATSurface;
class CATCurve;

//------------------------------------------------------------------
// Transaction performante d'acces aux liens inverses topologiques
//------------------------------------------------------------------
class ExportedByCATGeometricObjects CATCGMDelayingEquationsLifeCycle : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static   CATCGMDelayingEquationsLifeCycle *Create(int iEstimatedSize = 0);
  virtual ~CATCGMDelayingEquationsLifeCycle();

  CATCGMNewClassArrayDeclare;   

  //------------------------------------------------------------------
  // INTERNAL : Used to make sure that end of Transaction is done
  //------------------------------------------------------------------
  virtual void Clean();

  //------------------------------------------------------------------
  // INTERNAL : Dedicated to GeometricObjectsCGM/NewTopologicalObjects
  //------------------------------------------------------------------
  void AddDelayingSurface(CATSurface *iSurface);
  void AddDelayingCurve(  CATCurve   *iCurve);


protected:
  CATCGMDelayingEquationsLifeCycle(int iEstimatedSize = 0);
  CATCGMCountHashTable  *_ToUnlock;
  int                    _EstimatedSize;
};


//------------------------------------------------------------------
// Encapsulation des macros de definition ..
//------------------------------------------------------------------
#define CATCGMDelayingEquationsLifeCycleBegin(marqueur,iEstimatedSize)  \
  CATCGMDelayingEquationsLifeCycle *volatile marqueur = CATCGMDelayingEquationsLifeCycle::Create(iEstimatedSize); \
CATTry  \
{  

#define CATCGMDelayingEquationsLifeCycleEnd(marqueur)  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
  CATRethrow; \
}  \
CATEndTry 


#endif

