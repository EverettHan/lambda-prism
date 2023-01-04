#ifndef CATCGMTouchedGarbageCollector_h
#define CATCGMTouchedGarbageCollector_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
/*
      CATCGMTouchedGarbageCollectorBegin(conchita,geometry) 
      {
          // ... Nombreux Touched dans la factory de l'Objet
      }
      CATCGMTouchedGarbageCollectorEnd(conchita);
*/
//
//==========================================================================
/**
 *        Identify a specific transaction 
 * allowing underneath (deep level) treatment to incorporate
 * specific temporary Data Structure more appropriate 
 * to a specific application
 *
 *  For Instance, a garbage collector for cleaning residient Touched Topology
 * for the dynamic drafting application ...
 *  
 *        In Case of multi-threaded application,
 * Call-back for end of a particuliar transaction is done
 * at the end of the last alive transaction
 * (transmition of callback can be done ...)
 */

#include "ExportedByCATTopologicalObjects.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CATCGMNewArray.h"
#include "CATCGMTransaction.h"
class CATICGMObject;
class CATCGMContainer;

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATCGMTouchedGarbageCollector : public CATCGMTransaction
{
public :
  
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static CATCGMTouchedGarbageCollector * Create(CATICGMObject *iCGMObject);
  CATCGMNewClassArrayDeclare;   
  
  //------------------------------------------------------------------
  // INTERNAL : Used to make sure that end of Transaction is done
  // in case of exception throw with longjmp ..
  //------------------------------------------------------------------
  virtual void Clean();
  
  
protected:
  CATCGMTouchedGarbageCollector(CATICGMObject *iCGMObject);
  
  CATCGMContainer *_Container;
};


#define CATCGMTouchedGarbageCollectorBegin(conchita,iCGMObject)  \
  CATCGMTouchedGarbageCollector *volatile conchita = CATCGMTouchedGarbageCollector::Create(iCGMObject); \
CATTry   \
{  

#define CATCGMTouchedGarbageCollectorEnd(conchita)  \
  if ( conchita ) { conchita->Clean(); delete conchita; conchita=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( conchita ) { conchita->Clean(); delete conchita; conchita=NULL; } \
  CATRethrow; \
}  \
CATEndTry 



#endif

