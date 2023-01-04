/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
//===========================================================================
//
// Implementation generique d'une hash table avec stockage
// d'une donnee associee compteur (avec gestion des adresses > 2 Go)
//  
//
// Mai. 2002   Creation                            HCN
//
//===========================================================================

#ifndef  CATCGMHashTableWithCounter_h
#define  CATCGMHashTableWithCounter_h

#include "CATCGMHashTableWithAssoc.h"
#include "CATMathematics.h"

class ExportedByCATMathematics CATCGMHashTableWithCounter : public CATCGMHashTableWithAssoc
{
public:

  CATCGMHashTableWithCounter(int iEstimatedSize = 0,
                             PFHASHKEYFUNCTION ipHashKeyFunction = NULL,
                             PFCOMPAREFUNCTION	ipCompareFunction = NULL);

  virtual ~CATCGMHashTableWithCounter();

  // Override
  int Insert(void* ipElem, void* ipAssoc);
  int InsertReturnPos(void* ipElem, void* ipAssoc);
};

#endif

