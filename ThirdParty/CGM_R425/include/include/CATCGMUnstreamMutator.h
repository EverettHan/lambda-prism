#ifndef CATCGMUnstreamMutator_h
#define CATCGMUnstreamMutator_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//  Transaction performante d'acces aux liens inverses topologiques
//==========================================================================
#include "ExportedByCATMathStream.h"
#include "CATCGMTransaction.h"
#include "CATMathInline.h"

class CATechAttribute;
 
//------------------------------------------------------------------
// Transaction performante d'acces aux liens inverses topologiques
//------------------------------------------------------------------
class ExportedByCATMathStream CATCGMUnstreamMutator : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static CATCGMUnstreamMutator *Create(CATechAttribute *iOptions);

  CATCGMNewClassArrayDeclare;   

  virtual void Clean();

  INLINE CATechAttribute  *GetOptions() const;


protected:
  CATCGMUnstreamMutator(CATechAttribute *iOptions);
  CATechAttribute    *_Options;
};
 
//------------------------------------------------------------------
// Encapsulation des macros de definition ..
//------------------------------------------------------------------
#define CATCGMUnstreamMutatorBegin(marqueur,iOptions)  \
  CATCGMUnstreamMutator *volatile marqueur = CATCGMUnstreamMutator::Create(iOptions); \
CATTry  \
{  

#define CATCGMUnstreamMutatorEnd(marqueur)  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
  CATRethrow; \
}  \
CATEndTry 


/** @nodoc  */
INLINE CATechAttribute  *CATCGMUnstreamMutator::GetOptions() const
{  return _Options; }

 

#endif

