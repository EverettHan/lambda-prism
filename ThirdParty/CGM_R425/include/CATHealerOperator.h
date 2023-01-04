//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2000
//
// DESCRIPTION : Reparation et nettoyage de bodys
// 
//-----------------------------------------------------------------------------
// Dec 2000   Creation                        I.Chauvigne, X.Dupont, E.Dupuis
//=============================================================================

#ifndef CATHealerOperator_h
#define CATHealerOperator_h

class CATGeoFactory;

class CATTopData;
class CATCGMJournalList;

class CATBody;
class CATShell;
class CATWire;

#include "BOOPER.h"
#include "CATTopologicalOperator.h"
#include "ListPOfCATBody.h"

class ExportedByBOOPER CATHealerOperator : public CATTopologicalOperator
{
  public:
  
   CATHealerOperator(CATGeoFactory* iFactory, CATTopData* iData, CATBody* iCreationBody);
   ~CATHealerOperator();

   //--------------------------------------------------------------------------
   //                           WireHealer
   //
   // SPEC : reparation de iWireToClean.
   //        Un wire necessite reparation si le Check d'auto-intersection de wire
   //        detecte une anomalie.
   //        oHealedBody est un body compose de n Wires valides ne s'auto-intersectant pas. 
   //--------------------------------------------------------------------------
   void WireHealer(CATWire * iWireToClean, CATBody * iWireBody, CATBody ** oHealedBody);
};

#endif
