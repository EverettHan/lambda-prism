/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
/* -*-c++-*- */
#ifndef _CATCGMReplay_GraphicalChangeSet_h
#define _CATCGMReplay_GraphicalChangeSet_h
/* -*-c++-*- */

#include "ExportedByCATTopologicalObjects.h"

// element class 
class CATCGMOperator;
class CATBody;
class CATechSet;
class CATechAttribute;

extern "C" 
{
  typedef void CATCGMReplay_GraphicalChangeSet( CATCGMOperator  * iOperator,
                                                CATBody         * iBodyResult,
                                                CATechSet       * iCompositeManagement, 
                                                CATechAttribute * iBootAttribute); 

}
  

#endif
