#ifndef CATCGMSelectSerialize_h
#define CATCGMSelectSerialize_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
/*
      CATCGMSelectSerializeBegin(conchita,geometry) 
      {
          // ... Nombreux Touched dans la factory de l'Objet
      }
      CATCGMSelectSerializeEnd(conchita);
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

#include "YP0LOGRP.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CATCGMNewArray.h"
#include "CATCGMTransaction.h"
#include "CATCGMStreamVersion.h"
#include "CATMathInline.h"

class CATICGMObject;
class CATCGMContainer;

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByYP0LOGRP CATCGMSelectSerialize : public CATCGMTransaction
{
public :
  
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static CATCGMSelectSerialize * Create(CATCGMStreamVersion iTargetVersion);
  CATCGMNewClassArrayDeclare;   
  
  INLINE CATCGMStreamVersion GetTargetVersion() const;

  //------------------------------------------------------------------
  // INTERNAL : Used to make sure that end of Transaction is done
  // in case of exception throw with longjmp ..
  //------------------------------------------------------------------
  virtual void Clean();
  
  
protected:
  CATCGMSelectSerialize(CATCGMStreamVersion iTargetVersion);
  CATCGMStreamVersion _TargetVersion;
};


#define CATCGMSelectSerializeBegin(conchita,iTargetVersion)  \
  CATCGMSelectSerialize *volatile conchita = CATCGMSelectSerialize::Create(iTargetVersion); \
CATTry   \
{  

#define CATCGMSelectSerializeEnd(conchita)  \
  if ( conchita ) { conchita->Clean(); delete conchita; conchita=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( conchita ) { conchita->Clean(); delete conchita; conchita=NULL; } \
  CATRethrow; \
}  \
CATEndTry 


/** @nodoc  */
INLINE CATCGMStreamVersion CATCGMSelectSerialize::GetTargetVersion() const
{  return _TargetVersion; }
 



#endif

