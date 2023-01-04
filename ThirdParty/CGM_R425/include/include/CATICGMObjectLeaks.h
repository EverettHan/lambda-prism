#ifndef CATICGMObjectLeaks_h
#define CATICGMObjectLeaks_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//  Voici un bon exemple d'utilisation
//  pour detecter les nouveaux objects inutiles
//==========================================================================
/*


    CATGeoFactory           *iFactory;
    CATLISTP(CATICGMObject)  newBuild,newLeaks;

    CATICGMObjectLeaksBegin(marqueur,factory) 
    {
       // ... Traitement d'un operateur
       CATBody *body = GetResult();
  
       newBuild.Append(body);
    }
    CATICGMObjectLeaksEnd(marqueur,newBuild,newLeaks);
    
    if (newLeaks.Size() > 0) // Detection de nouveaux objects inutiles dans la Factory
    {
    }


*/
//
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CATCGMNewArray.h"
#include "CATCGMTransaction.h"
#include "CATListOfCATICGMObjects.h"
class CATGeoFactory;

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATICGMObjectLeaks : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // CLIENT : life of one CATICGMObjectLeaks Object identify a transaction
  //------------------------------------------------------------------
  static CATICGMObjectLeaks * Create(CATGeoFactory *iFactory);

  CATCGMNewClassArrayDeclare;   

  //------------------------------------------------------------------
  // INTERNAL : Used to make sure that end of Transaction is done
  // in case of exception throw with longjmp ..
  //------------------------------------------------------------------
  void ComputeLeaks(const CATLISTP(CATICGMObject) &iNewBuild, CATLISTP(CATICGMObject) &ioNewLeaks);

  virtual void Clean();


protected:
  CATICGMObjectLeaks(CATGeoFactory *iFactory);

  CATGeoFactory           *_Factory;
  CATLISTP(CATICGMObject)  _PreviousFederators;
};


#define CATICGMObjectLeaksBegin(marqueur,factory)  \
  CATICGMObjectLeaks *volatile marqueur = CATICGMObjectLeaks::Create(factory); \
CATTry  \
{  

#define CATICGMObjectLeaksEnd(marqueur,newBuild,newLeaks)  \
  if ( marqueur ) { marqueur->ComputeLeaks(newBuild,newLeaks); marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
  CATRethrow; \
}  \
CATEndTry 


#endif

