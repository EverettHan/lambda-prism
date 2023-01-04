#ifndef CATExtCloneExplicitAssoc_h_
#define CATExtCloneExplicitAssoc_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//    INTERDICTION D'INCLURE DANS HEADER CAA
//    HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//=============================================================================
  /**
    * -------------------------------------------------------------------------------------------------------
    *  TOPIC  :  Persistency Cache Tool for Seamless management of geometries from different CATGeoFactory
    * -------------------------------------------------------------------------------------------------------
 */
#include "CATCGMIndex.h"
#include "CATListOfInt.h"
#include "YP00IMPL.h"
#include "CATExtCloneManager.h"
#include "CATThrowForNullPointer.h"

class ExportedByYP00IMPL  CATExtCloneExplicitAssoc
{
public :

  CATExtCloneExplicitAssoc(CATExtCloneManager *iProprio) : _ForIndex(NULL), _Master(NULL)  
  { if ( !iProprio ) CATThrowForNullPointer();  _Master = iProprio;  }

  ~CATExtCloneExplicitAssoc() 
  { if ( _ForIndex ) { _ForIndex->Release(); _ForIndex= NULL; } }

  CATCGMNewClassArrayDeclare;

  //  Initial (First) Full define of list _ToClone&_WhereToPaste from AssocList
  void FullGenerationFromAssocList();

  // Then incremental Cache Management
  void UpdateVariationalCache(CATICGMObject* iIn ,  CATICGMObject* iOut);

  // Between extended Run (Recording management)
  void ClearAll();

  // INTERNAL
  INLINE CATCGMIndex  *GetIndex();

  // Index relative to internal Index 
  CATListOfInt   _ToClone;    
  CATListOfInt   _WhereToPaste;      

private:
  CATExtCloneManager *_Master;
  CATCGMIndex  * _ForIndex;
 };

 
//-----------------------------------------------------------------------------------------------------------
// GetIndex()
//-----------------------------------------------------------------------------------------------------------
INLINE CATCGMIndex  *  CATExtCloneExplicitAssoc::GetIndex()
{ return _ForIndex; }

#endif
