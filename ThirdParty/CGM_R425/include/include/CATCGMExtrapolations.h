#ifndef CATCGMExtrapolations_h
#define CATCGMExtrapolations_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// Gestion d'une transaction des objets extrapoles
//==========================================================================
//------------------------------------------------------------------
//  A) Transaction plus adequate des courbes/surfaces extrapolees
//------------------------------------------------------------------
//
//              CATCGMExtrapolationsBegin(session,TheOperator) 
//              {
//                  // ...  
//              }
//              CATCGMExtrapolationsEnd(session,TheFederators);
//
//==========================================================================
// 02/03/20 NLD Migration sur CATCatchSecured
//==========================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATListOfCATICGMObjects.h"

#include "CATErrorMacros.h"
#include "CATErrorMacrosCGM.h"

class CATTopOperator;

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATCGMExtrapolations 
{
public :
  //-------------------------------- 
  // life cycle
  //-------------------------------- 
  static       CATCGMExtrapolations *Create(CATTopOperator &TheOperator);
  virtual     ~CATCGMExtrapolations();
  
  //-------------------------------- 
  // Achevement 
  //-------------------------------- 
  virtual void FinishOKAY(CATLISTP(CATICGMObject) &TheFederators) = 0;
  virtual void FinishKO(CATError *iError) = 0;

protected:
               CATCGMExtrapolations();
};


//------------------------------------------------------------------------------
//  Macro d'acces a la geston d'une transaction sur les objets extrapoles
//------------------------------------------------------------------------------
// N.B CATCatchSecured en association avec declaration volatile de session; NLD020320
#define CATCGMExtrapolationsBegin(session,TheOperator)                                 \
CATCGMExtrapolations *volatile session = CATCGMExtrapolations::Create(TheOperator);    \
CATTrySecured                                                                          \
{


#define CATCGMExtrapolationsEnd(session,TheFederators)                                 \
  if ( session ) { session->FinishOKAY(TheFederators); delete session; session=NULL; } \
}                                                                                      \
CATCatchSecured(CATError, error)                                                       \
{                                                                                      \
  if ( session ) { session->FinishKO(error); delete session; session=NULL; }           \
  CATRethrow;                                                                          \
}                                                                                      \
CATEndTrySecured



#endif
