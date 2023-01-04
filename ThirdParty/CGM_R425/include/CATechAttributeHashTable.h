/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  2005
//=============================================================================
// Feb. 05 Creatiom                                                       HCN
//=============================================================================
#ifndef CATechAttributeHashTable_H
#define CATechAttributeHashTable_H

#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"
#include "ExportedByCATTechTools.h"
#include "CATechSet.h"
 
class CATechAttribute;
class CATechAttributImpl; 

typedef		int	         (*PFAttributeCompareFunction) ( CATechAttribute *, CATechAttribute * );	
typedef		unsigned int (*PFAttributeHashKeyFunction) ( CATechAttribute * ) ;

ExportedByCATTechTools unsigned int HashKeyCATechAttribute(CATechAttribute* ipAttribute);
ExportedByCATTechTools int          CompareCATechAttribute(CATechAttribute* ipAttribute1, CATechAttribute* ipAttribute2);

class ExportedByCATTechTools  CATechAttributeHashTable : protected CATCGMHashTable
{
public:
  CATechAttributeHashTable (CATechSet   *iSet,
                            PFAttributeHashKeyFunction ipHashKeyFunction, 
                            PFAttributeCompareFunction ipCompareFunction, 
                            int iEstimatedSize = 0);
  ~CATechAttributeHashTable();

  CATCGMNewClassArrayDeclare;
  
  int              Insert(CATechAttribute* ipAttribute);
  CATechAttribute* KeyLocate(unsigned int iKey) const; 
  int              Remove(CATechAttribute* ipAttribute);

  void             RemoveAll();
 
private :
  CATechSet * _TheSet;
};

     

#endif 
