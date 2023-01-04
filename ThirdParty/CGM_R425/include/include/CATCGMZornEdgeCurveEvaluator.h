#ifndef CATCGMZornEdgeCurveEvaluator_h
#define CATCGMZornEdgeCurveEvaluator_h
/* -*-C++-*-*/
//========================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//    Dedie aux rattrapages dans les services topologiques 
//       sur les recuperations-reutilisations d edgeCurve dans des contextes geometriques
//       IR    Profile (EdgeCurve) invalide de TabulatedCylinder 
//========================================================================================================
/*
    CATCGMZornEdgeCurveEvaluatorBegin(marqueur) 
    {
       // ... 
    }
    CATCGMZornEdgeCurveEvaluatorEnd(marqueur);
*/
//==========================================================================
#include "CATGeometricObjects.h"
#include "CATCGMTransaction.h"
#include "CATListOfCATGeometries.h"

class CATGeometry;

//------------------------------------------------------------------
// Transaction performante d'acces aux liens inverses topologiques
//------------------------------------------------------------------
class ExportedByCATGeometricObjects CATCGMZornEdgeCurveEvaluator : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static   CATCGMZornEdgeCurveEvaluator *Create();
  virtual ~CATCGMZornEdgeCurveEvaluator();

  CATCGMNewClassArrayDeclare;   

  //------------------------------------------------------------------
  // INTERNAL : Used to make sure that end of Transaction is done
  //------------------------------------------------------------------
  virtual void Clean();

  //------------------------------------------------------------------
  // INTERNAL : Dedicated to GeometricObjectsCGM/NewTopologicalObjects
  //------------------------------------------------------------------
  void AddSupport(CATGeometry *iSupport);
  void GetSupport(CATLISTP(CATGeometry) &oSupport);


protected:
  CATCGMZornEdgeCurveEvaluator();
  CATLISTP(CATGeometry) _Support;
};


//------------------------------------------------------------------
// Encapsulation des macros de definition ..
//------------------------------------------------------------------
#define CATCGMZornEdgeCurveEvaluatorBegin(marqueur)  \
  CATCGMZornEdgeCurveEvaluator *volatile marqueur = CATCGMZornEdgeCurveEvaluator::Create(); \
CATTry  \
{  

#define CATCGMZornEdgeCurveEvaluatorEnd(marqueur)  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
  CATRethrow; \
}  \
CATEndTry 


#endif

